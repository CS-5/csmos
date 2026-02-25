#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_DIR="$(dirname "$SCRIPT_DIR")"
VIAL_QMK_DIR="$PROJECT_DIR/.vial-qmk"
BUILD_DIR="$PROJECT_DIR/build"

if [ ! -d "$VIAL_QMK_DIR" ]; then
  echo "Error: .vial-qmk not found. Run scripts/setup.sh first." >&2
  exit 1
fi

mkdir -p "$BUILD_DIR"

# cd into vial-qmk so the QMK CLI detects it as the firmware directory.
# This is necessary because `qmk` checks CWD (priority 1) before the
# QMK_HOME env var (priority 3), and a global user.qmk_home config
# (priority 2) would otherwise override our env var.
cd "$VIAL_QMK_DIR"

echo "Building left half..."
qmk compile -kb cosmos/csmos -km default \
  -e MAKECMDGOALS=uf2-split-left \
  -e TARGET=csmos_left

echo "Building right half..."
qmk compile -kb cosmos/csmos -km default \
  -e MAKECMDGOALS=uf2-split-right \
  -e TARGET=csmos_right

# QMK copies outputs to both the qmk_firmware and userspace (project root) folders
mv "$PROJECT_DIR/csmos_left.uf2" "$BUILD_DIR/csmos-left.uf2"
mv "$PROJECT_DIR/csmos_right.uf2" "$BUILD_DIR/csmos-right.uf2"

echo "Build complete: $BUILD_DIR/csmos-left.uf2, $BUILD_DIR/csmos-right.uf2"