# CIDOO V98 RATWARE

> [!CAUTION]
> W.I.P DO NOT USE!

Custom QMK firmware for the Cidoo V98 keyboard with VIA support.

- [CIDOO V98 RATWARE](#cidoo-v98-ratware)
  - [Building The Firmware](#building-the-firmware)
  - [Flashing Instructions](#flashing-instructions)
  - [License](#license)

## Building The Firmware

1. Set up the QMK enviroment by following the [QMK setup guide](https://docs.qmk.fm/newbs_getting_started)
2. Clone this repository or copy the files to your QMK directory under `keyboards/cidoo/v98`
3. Compile the firmware:

```
qmk compile -kb cidoo/v98 -km default
```

## Flashing Instructions

1. Enter bootloader mode by holding the top left key (usually ESC) while plugging in the keyboard
2. Flash the compiled firmware:

```
qmk flash -kb cidoo/v98 -km default
```

## License

This firmware is released under the MIT License.
