#pragma once

#define VIAL_KEYBOARD_UID {0x0B, 0xEF, 0x40, 0x1F, 0x94, 0x21, 0xD3, 0x71}

// Unlock combo: ESC (left, matrix 3,0) + rightmost key (right, matrix 10,6)
// These are physically on opposite halves of the split keyboard.
#define VIAL_UNLOCK_COMBO_ROWS {3, 10}
#define VIAL_UNLOCK_COMBO_COLS {0, 6}
