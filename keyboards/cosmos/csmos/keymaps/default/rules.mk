VIA_ENABLE = yes
VIAL_ENABLE = yes
LTO_ENABLE = yes
OS_DETECTION_ENABLE = yes

# Maybe
# AUTO_SHIFT_ENABLE = yes

# Workaround: when keymap.json exists in the QMK userspace, the build system
# skips the keymap.c search and never sets OTHER_KEYMAP_C. This ensures
# keymap.c is still included alongside the generated keymap from keymap.json.
ifndef OTHER_KEYMAP_C
  _KM_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
  ifneq ("$(wildcard $(_KM_DIR)keymap.c)","")
    OPT_DEFS += -DOTHER_KEYMAP_C=\"$(_KM_DIR)keymap.c\"
  endif
endif
