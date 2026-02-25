#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_DIR="$(dirname "$SCRIPT_DIR")"
VIAL_QMK_DIR="$PROJECT_DIR/.vial-qmk"

# Clone vial-qmk
if [ ! -d "$VIAL_QMK_DIR" ]; then
  echo "Cloning vial-qmk..."
  git clone --branch vial --depth 1 \
    https://github.com/vial-kb/vial-qmk.git "$VIAL_QMK_DIR"
  cd "$VIAL_QMK_DIR"
  make git-submodule
else
  echo "vial-qmk already cloned."
fi

# Symlink keyboard config
if [ ! -L "$VIAL_QMK_DIR/keyboards/cosmos" ]; then
  ln -sf "$PROJECT_DIR/keyboards/cosmos" "$VIAL_QMK_DIR/keyboards/cosmos"
  echo "Symlinked keyboards/cosmos."
else
  echo "Keyboard symlink already exists."
fi

# Add getreuer community modules
if [ ! -d "$VIAL_QMK_DIR/modules/getreuer" ]; then
  mkdir -p "$VIAL_QMK_DIR/modules"
  git clone --depth 1 \
    https://github.com/getreuer/qmk-modules.git "$VIAL_QMK_DIR/modules/getreuer"
  echo "Installed getreuer community modules."
else
  echo "getreuer modules already installed."
fi

echo "Setup complete."
