# Cidoo v98 Firmware

> [!CAUTION]
> W.I.P DO NOT USE!

## Table of Contents

- [Cidoo v98 Firmware](#cidoo-v98-firmware)
  - [Table of Contents](#table-of-contents)
  - [Overview](#overview)
  - [Getting Started](#getting-started)
    - [Building](#building)
    - [Flashing](#flashing)
    - [VIA Support](#via-support)
  - [License](#license)

## Overview

Custom QMK firmware for the Cidoo v98 keyboard with VIA support.

## Getting Started

### Building

1. Set up the QMK enviroment by following the [QMK setup guide](https://docs.qmk.fm/newbs_getting_started)
2. Clone this repository or copy the files to your QMK directory under `keyboards/cidoo/v98`
3. Compile the firmware:

```
qmk compile -kb cidoo/v98 -km default
```

### Flashing

1. Enter bootloader mode by holding the top left key (usually ESC) while plugging in the keyboard
2. Flash the compiled firmware:

```
qmk flash -kb cidoo/v98 -km default
```

### VIA Support

1. Use VIA on the [web](https://www.usevia.app/) or download the [client](https://github.com/the-via/releases/releases)
2. Configure your keyboards keymapings and RGB settings

## License

This firmware is released under the MIT License.
