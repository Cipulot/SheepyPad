# SheepyPad

![SheepyPad](https://github.com/Cipulot/SheepyPad/blob/main/Documents/imgs/front.jpg?raw=true)

SheepyPad is an ISO Enter shaped macropad easy to build and customize.

Main features included:

- 5x4 key matrix (both 3-pin and 5-pin supported)
- 128x32 OLED display for status indication
- Rotary encoder for media control
- Integrated 2 operand calculator with basic math operations (+, -, *, /, sqrt)
- VIA and QMK compatibility
- 6 addressable RGB LEDs for underglow

## Guides

### QMK

This board fully supports QMK, refer to the [official docs](https://beta.docs.qmk.fm/).

### VIA

If you wanna use VIA follow the instructions [here](https://github.com/Cipulot/SheepyPad/blob/main/Documents/via.md).

### Calculator

SheepyPad implements a simple calculator that you can use to perform basic math operations. Follow the [Calculator Guide](https://github.com/Cipulot/SheepyPad/blob/main/Documents/calculator.md) to get started.

### PCB

Follow the [PCB Assembly Instructions](https://github.com/Cipulot/SheepyPad/blob/main/Documents/pcb_assembly.md) to build the PCB and test it out.

## Repo structure

- `Docs` contains all documentation and images for the project.
- `Firmware` contains both the source and precompiled binaries.
- `Hardware` contains the KiCad design files for the keyboard, fabrication files (in the [Gerbers](https://github.com/Cipulot/SheepyPad/blob/main/Hardware/Gerbers) folder).
- `Mechanicals` contains STEP file of the PCB and components, plate and case files.

## Project status

Project is currently in development. V1 boards have been produced and tested successfully. V2 boards are in the works and will add/change currently available features (both hardware and firmware wise).

Software is in constant change and being updated on my qmk_firmware fork available [here](https://github.com/Cipulot/qmk_firmware). You can find a basic default code example (with precompiled binaries) in this repo too if you want to quickly get it up and running.
