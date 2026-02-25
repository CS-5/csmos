# CSmos

QMK firmware for a 62-key split ergonomic keyboard built on the [Cosmos](https://ryanis.cool/cosmos) platform with Lemon Wired (RP2040) controllers and Pumpkin Patch PCBs. Uses [Vial](https://get.vial.today/) for runtime key remapping.

## Configuration Hierarchy

QMK uses multiple config files at two levels. Settings at the keymap level override the keyboard level.

### Keyboard Level (`keyboards/cosmos/csmos/`)

| File            | Purpose                                                                                                                                                                                                              |
| --------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `keyboard.json` | Primary hardware config: matrix pins, USB IDs, processor, split settings, enabled features, and physical key positions (x/y coordinates + matrix mapping). This is the "data-driven" config — QMK's modern approach. |
| `config.h`      | C `#define`s for settings that don't have JSON equivalents: USART serial config (`SERIAL_USART_FULL_DUPLEX`, TX/RX pins), split handedness (`EE_HANDS`), and newer QMK features (`SPECULATIVE_HOLD`).                |
| `rules.mk`      | Makefile variables for build flags. Currently empty since all features are set in `keyboard.json`.                                                                                                                   |

### Keymap Level (`keymaps/default/`)

| File          | Purpose                                                                                                                                                     |
| ------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `keymap.c`    | The actual key assignments — what each key does on each layer. This is the default keymap compiled into firmware (Vial overrides it at runtime via EEPROM). |
| `keymap.json` | Community module configuration. Lists which [QMK community modules](https://github.com/getreuer/qmk-modules) to include in the build.                       |
| `config.h`    | Vial-specific C defines: `VIAL_KEYBOARD_UID` and `VIAL_UNLOCK_COMBO_*`. These must be C preprocessor defines — no JSON equivalent.                          |
| `rules.mk`    | Build flags for Vial (`VIA_ENABLE`, `VIAL_ENABLE`, `LTO_ENABLE`). These are Vial-fork-specific and can't move to `keyboard.json`.                           |
| `vial.json`   | Visual layout definition consumed by the Vial desktop app. Tells Vial how to render the keyboard in its GUI.                                                |

### Why So Many Files?

`keyboard.json`, `config.h`, and `rules.mk` overlap in concept but not in practice:

- **`keyboard.json`** handles everything QMK's data-driven system supports (pins, USB, features, physical layout).
- **`config.h`** is required for settings that only exist as C `#define`s — especially USART serial configuration and features like `SPECULATIVE_HOLD` that haven't been added to the JSON schema yet.
- **`rules.mk`** is required for Vial-fork build flags that aren't part of QMK's feature system.

### The Three "Layouts"

The physical layout appears in three places, each serving a different consumer:

| File                        | What It Defines                        | Consumed By                                                        |
| --------------------------- | -------------------------------------- | ------------------------------------------------------------------ |
| `keyboard.json` → `layouts` | Physical key positions + matrix wiring | QMK compiler (maps `LAYOUT()` macro args to the electrical matrix) |
| `vial.json` → `layouts`     | Visual key positions                   | Vial GUI app (renders the keyboard on screen)                      |
| `keymap.c`                  | Logical key assignments                | QMK compiler (what each key does)                                  |

If the physical layout changes (keys added/removed, matrix rewired), both `keyboard.json` and `vial.json` must be updated. `keymap.c` only changes when key assignments change.

## Building

Firmware is built automatically via GitHub Actions on every push. Release artifacts (UF2 files) are published:

### Local Build

```sh
# One-time setup: clones vial-qmk, symlinks keyboard config, installs community modules
./scripts/setup.sh

# Build both halves
./scripts/build.sh
# → build/csmos-left.uf2, build/csmos-right.uf2
```

Requires the [QMK CLI](https://docs.qmk.fm/) (`qmk`). The setup script clones [vial-qmk](https://github.com/vial-kb/vial-qmk) to `.vial-qmk/` and installs [getreuer's community modules](https://github.com/getreuer/qmk-modules) to `.vial-qmk/modules/getreuer/`.

### Flashing

Double-tap the reset button on the controller to enter bootloader mode or hold the bootmagic key (lower left-most key), then copy the `.uf2` file to the mounted drive. Flash each half separately.

## Updating the Keymap

The default keymap in `keymap.c` is what the keyboard loads when EEPROM is empty (e.g., after a fresh flash). At runtime, Vial stores your remapped layout in EEPROM, overriding `keymap.c`.

To make a Vial layout the new compiled default:

1. Export your layout from Vial as a `.vil` file (save to `layout.vil` in the project root)
2. Run `python3 scripts/vil2c.py` to generate the new keymap
3. Replace `keyboards/cosmos/csmos/keymaps/default/keymap.c` with the output:
   ```sh
   python3 scripts/vil2c.py > keyboards/cosmos/csmos/keymaps/default/keymap.c
   ```
