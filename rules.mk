# MCU name
MCU = STM32F103

# Bootloader selection
BOOTLOADER = stm32duino

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # USB Nkey Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = yes       # Enable keyboard RGB underglow
RGBLIGHT_DRIVER = WS2812    # RGB Driver selection
WS2812_DRIVER = pwm         # Driver for WS2812 RGB LEDs
AUDIO_ENABLE = no           # Audio output
ENCODER_ENABLE = yes        # Enable encoder support
ENCODER_MAP_ENABLE = yes    # Enable keycode mapping for encoder
ENCODERS_SWITCH_ENABLE = yes # Enable encoder click button

# Additional features
TAP_DANCE_ENABLE = no
COMBO_ENABLE = no

# Bluetooth options
BLUETOOTH_ENABLE = yes      # Enable Bluetooth
BLUETOOTH_DRIVER = bluefruit_le  # Select the Bluetooth driver
BATTERY_ENABLE = yes        # Battery status monitoring
SLEEP_LED_ENABLE = yes      # Breathe LED while USB suspended

# VIA options
VIA_ENABLE = yes            # Enable VIA support
LTO_ENABLE = yes            # Link Time Optimization (reduces firmware size)

# CPU options for STM32F103
ARMV7_EXCEPTION_VECTORS = yes  # STM32F103 uses ARMv7
USE_CHIBIOS = yes              # Use ChibiOS for STM32
BOARD = STM32_F103_STM32DUINO  # Board definition

# ChibiOS optimizations
SERIAL_DRIVER = usart       # Use USART for serial
CONSOLE_DRIVER = none       # Disable console to save space
QMK_SETTINGS = no           # Disable QMK settings to save space
EEPROM_DRIVER = i2c         # Use I2C EEPROM
DEBOUNCE_TYPE = sym_eager_pk  # Efficient debounce algorithm

# Build optimization
VPATH += keyboards/gboards   # Additional search path (for shared code)
OPT = s                     # Optimize for size
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE # Enable sleep during idle (power saving)

# Enable idle sleep mode when USB suspended
OPT_DEFS += -DUSB_SUSPEND_WAKEUP_DELAY=200

# Bluetooth power saving features
OPT_DEFS += -DBLUETOOTH_POWER_SAVE
OPT_DEFS += -DBATTERY_ENABLE

# Debug options - comment out for production build
# These slow down the keyboard and use more space
#OPT_DEFS += -DDEBUG_MATRIX
#OPT_DEFS += -DDEBUG_BLUETOOTH