BOOTLOADER = qmk-hid
BOOTLOADER_SIZE = 512
PROGRAM_CMD = $(HID_BOOTLOADER_CLI) -mmcu=$(MCU) -w -v $(BUILD_DIR)/$(TARGET).hex
SRC += misc_utils.c

UNICODE_ENABLE = yes
TAP_DANCE_ENABLE = yes
OLED_ENABLE = yes
ENCODER_ENABLE = yes       # Enables the use of one or more encoders
RGBLIGHT_ENABLE = no      # Enable keyboard RGB underglow
RGB_MATRIX_ENABLE = yes
RAW_ENABLE = yes

CONSOLE_ENABLE = no        # Console for debug
