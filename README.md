# CSKB

QMK firmware for a 62-key split ergonomic keyboard built on the [Cosmos](https://ryanis.cool/cosmos) platform with Lemon Wired (RP2040) controllers and Pumpkin Patch PCBs.

## Building

Firmware is built automatically via GitHub Actions on every push. Release artifacts (UF2 files) are published:

| Target | Description |
|--------|-------------|
| `cskb_left` | Left half |
| `cskb_right` | Right half |

The keymap uses [VIA](https://www.caniusevia.com/) for runtime key remapping.

### Local Build

Requires a working [QMK](https://docs.qmk.fm/) toolchain.

```sh
# One-time setup: symlink into QMK tree
mkdir -p ~/qmk_firmware/keyboards/cosmos
ln -s /path/to/keyboard/firmware ~/qmk_firmware/keyboards/cosmos/cskb

# Build (example: left half)
qmk compile -kb cosmos/cskb -km via
```

### Flashing

Double-tap the reset button on the controller to enter bootloader mode, then copy the `.uf2` file to the mounted drive. Flash each half separately.
