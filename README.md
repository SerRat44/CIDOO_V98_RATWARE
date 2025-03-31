# CIDOO V98 RATWARE

## Table of Contents

- [CIDOO V98 RATWARE](#cidoo-v98-ratware)
  - [Table of Contents](#table-of-contents)
  - [Info](#info)
  - [Get Started](#get-started)
    - [Building](#building)
    - [Flashing](#flashing)
    - [VIA Support](#via-support)
  - [License](#license)

## Info

> [!CAUTION]
> W.I.P DO NOT USE!

Custom QMK firmware for the Cidoo V98 keyboard with VIA support.

## Get Started

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
