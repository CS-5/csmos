#include QMK_KEYBOARD_H

#ifdef CHORDAL_HOLD
// Handedness for Chordal Hold's opposite-hands rule. This is a split keyboard
// whose left half is matrix rows 0-6 and right half is rows 7-13, so the row
// index alone determines the hand.
char chordal_hold_handedness(keypos_t key) {
    return key.row < 7 ? 'L' : 'R';
}
#endif
