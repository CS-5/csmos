#pragma once

#define VIAL_KEYBOARD_UID {0x0B, 0xEF, 0x40, 0x1F, 0x94, 0x21, 0xD3, 0x71}

// Unlock combo: top-left key (left, matrix 3,0) + top-right key (right, matrix 10,5)
// These are physically on opposite halves of the split keyboard.
#define VIAL_UNLOCK_COMBO_ROWS {3, 10}
#define VIAL_UNLOCK_COMBO_COLS {0, 5}

// Vial dynamic combos. COMBO_ENABLE turns on QMK's combo engine, but vial.c only
// provides the dynamic key_combos[] storage under VIAL_COMBO_ENABLE, so both this
// and an entry count are required or the build fails with an undefined key_combos.
// Guarded with ifndef so they never redefine a value the build already set.
#ifndef VIAL_COMBO_ENABLE
#define VIAL_COMBO_ENABLE
#endif
#ifndef VIAL_COMBO_ENTRIES
#define VIAL_COMBO_ENTRIES 16
#endif
