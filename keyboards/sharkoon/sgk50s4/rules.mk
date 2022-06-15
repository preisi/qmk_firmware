SRC = ../../../drivers/led/sn32/matrix_sn32f26x.c

# MCU name
MCU = SN32F268F
EEPROM_DRIVER = transient

# Build Options
#   comment out to disable the options.
#
LTO_ENABLE = no
BACKLIGHT_ENABLE = no
MAGIC_ENABLE = yes
MAGIC_KEYCODE_ENABLE = yes
BOOTMAGIC_ENABLE = yes  # Virtual DIP switch configuration
MOUSEKEY_ENABLE = no    # Mouse keys
EXTRAKEY_ENABLE = yes   # Audio control and System control
CONSOLE_ENABLE = no     # Console for debug
COMMAND_ENABLE = no     # Commands for debug and configuration
SLEEP_LED_ENABLE = no   # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes       # USB Nkey Rollover
AUDIO_ENABLE = no
RGBLIGHT_ENABLE = no
SERIAL_LINK_ENABLE = no
WAIT_FOR_USB = no
CUSTOM_MATRIX = yes

# Custom RGB matrix handling
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = SN32F26x

# Reduce code size
USE_PROCESS_STACKSIZE = 0x1E0
USE_EXCEPTIONS_STACKSIZE = 0xF0
