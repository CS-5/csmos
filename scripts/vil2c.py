#!/usr/bin/env python3
"""Convert a Vial .vil layout to keymap.c for this keyboard.

Reads the .vil file (matrix-ordered keycodes) and keyboard.json
(LAYOUT argument order) to produce a correctly ordered keymap.c.

Usage:
    python3 scripts/vil2c.py [layout.vil]
    python3 scripts/vil2c.py layout.vil > keyboards/cosmos/csmos/keymaps/default/keymap.c
"""

import json
import sys
from pathlib import Path

SCRIPT_DIR = Path(__file__).resolve().parent
PROJECT_DIR = SCRIPT_DIR.parent
KEYBOARD_JSON = PROJECT_DIR / "keyboards/cosmos/csmos/keyboard.json"

# Visual row definitions: (total_keys, n_left, left_col_start, right_col_start, label)
# Column starts are 0-indexed within each half (0 = outermost)
ROW_DEFS = [
    (12, 6, 0, 0, None),  # label is generated dynamically
    (12, 6, 0, 0, None),
    (12, 6, 0, 0, None),
    (12, 6, 0, 0, None),
    (4, 2, 2, 2, "5th column bottom"),
    (6, 3, 3, 0, "thumb top"),
    (4, 2, 4, 0, "thumb bottom"),
]

# Vial verbose keycode -> QMK short form
ALIASES = {
    "KC_LCTRL": "KC_LCTL", "KC_RCTRL": "KC_RCTL",
    "KC_LSHIFT": "KC_LSFT", "KC_RSHIFT": "KC_RSFT",
    "KC_BSPACE": "KC_BSPC", "KC_SPACE": "KC_SPC",
    "KC_ESCAPE": "KC_ESC", "KC_ENTER": "KC_ENT",
    "KC_SCOLON": "KC_SCLN", "KC_GRAVE": "KC_GRV",
    "KC_LBRACKET": "KC_LBRC", "KC_RBRACKET": "KC_RBRC",
    "KC_BSLASH": "KC_BSLS", "KC_COMMA": "KC_COMM",
    "KC_QUOTE": "KC_QUOT", "KC_EQUAL": "KC_EQL",
    "KC_MINUS": "KC_MINS", "KC_SLASH": "KC_SLSH",
    "KC_CAPSLOCK": "KC_CAPS", "KC_DELETE": "KC_DEL",
    "KC_INSERT": "KC_INS", "KC_PGDOWN": "KC_PGDN",
    "KC_PSCREEN": "KC_PSCR", "KC_SCROLLLOCK": "KC_SCRL",
    "KC_NUMLOCK": "KC_NUM", "KC_APPLICATION": "KC_APP",
    "KC_TRNS": "_______", "KC_NO": "XXXXXXX",
}

COL_W = 9        # column width: "KC_XXX, " padded
BASE_INDENT = 8
# Right section starts at this position (left 6 cols + 1 empty col gap)
RIGHT_START = BASE_INDENT + 6 * COL_W + COL_W  # 8 + 54 + 9 = 71


def normalize(kc):
    if kc == -1 or kc is None:
        return None
    return ALIASES.get(kc, kc)


def get_layout_order(kb_json_path):
    with open(kb_json_path) as f:
        kb = json.load(f)
    return [
        (e["matrix"][0], e["matrix"][1])
        for e in kb["layouts"]["LAYOUT"]["layout"]
    ]


def extract_layer(vil_layer, layout_order):
    return [normalize(vil_layer[r][c]) for r, c in layout_order]


def is_all_transparent(keys):
    return all(k == "_______" for k in keys)


def fmt(kc, last=False):
    if last:
        return kc
    return f"{kc},".ljust(COL_W)


def format_layer(keys, layer_idx, is_last_layer):
    lines = [f"    [{layer_idx}] = LAYOUT("]
    pos = 0

    for gi, (count, n_left, lcol, rcol, label) in enumerate(ROW_DEFS):
        n_right = count - n_left
        lk = keys[pos:pos + n_left]
        rk = keys[pos + n_left:pos + count]
        pos += count

        # Direction label for first row, aligned to columns
        if gi == 0:
            left_end = BASE_INDENT + 6 * COL_W   # 62
            right_end = RIGHT_START + 6 * COL_W   # 125
            outer_l = "outer --->"
            inner_l = "<--- inner"
            inner_r = "inner --->"
            outer_r = "<--- outer"
            lbl = [" "] * right_end
            # outer ---> at left edge
            for i, c in enumerate(outer_l):
                lbl[BASE_INDENT + i] = c
            # <--- inner right-aligned to left section end
            for i, c in enumerate(inner_l):
                lbl[left_end - len(inner_l) + i] = c
            # inner ---> at right section start
            for i, c in enumerate(inner_r):
                lbl[RIGHT_START + i] = c
            # <--- outer right-aligned to right section end
            for i, c in enumerate(outer_r):
                lbl[right_end - len(outer_r) + i] = c
            lines.append(f"    //  {''.join(lbl).strip()}")
        elif label:
            lines.append(f"    //  {label}")

        # Left half
        left_indent = " " * (BASE_INDENT + lcol * COL_W)
        left_str = "".join(fmt(k) for k in lk)
        left_end = BASE_INDENT + lcol * COL_W + n_left * COL_W

        # Right half: align to column within right section
        right_pos = RIGHT_START + rcol * COL_W
        gap = " " * (right_pos - left_end)

        is_last_row = gi == len(ROW_DEFS) - 1
        right_parts = []
        for i, k in enumerate(rk):
            last = is_last_row and is_last_layer and i == n_right - 1
            right_parts.append(fmt(k, last=last))
        right_str = "".join(right_parts)

        lines.append(f"{left_indent}{left_str}{gap}{right_str}")

    lines.append(f"    ){',' if not is_last_layer else ''}")
    lines.append("")
    return "\n".join(lines)


def main():
    vil_path = Path(sys.argv[1]) if len(sys.argv) > 1 else PROJECT_DIR / "layout.vil"

    if not vil_path.exists():
        print(f"Error: {vil_path} not found", file=sys.stderr)
        sys.exit(1)
    if not KEYBOARD_JSON.exists():
        print(f"Error: {KEYBOARD_JSON} not found", file=sys.stderr)
        sys.exit(1)

    with open(vil_path) as f:
        vil = json.load(f)

    layout_order = get_layout_order(KEYBOARD_JSON)

    # Extract layers, skip fully transparent ones (except layer 0)
    layers = []
    for i, layer_data in enumerate(vil["layout"]):
        keys = extract_layer(layer_data, layout_order)
        if i == 0 or not is_all_transparent(keys):
            layers.append((i, keys))

    # Output
    print("#include QMK_KEYBOARD_H")
    print()
    print("const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {")
    print()

    for idx, (layer_num, keys) in enumerate(layers):
        is_last = idx == len(layers) - 1
        print(format_layer(keys, layer_num, is_last))

    print("};")


if __name__ == "__main__":
    main()
