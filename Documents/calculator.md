# Calculator Guide

The calculator is integrated and can be accessed by toggling the layer key until you see the following on the OLED screen:

![CalculatorLayer](https://github.com/Cipulot/SheepyPad/blob/main/Documents/imgs/calculator_layer.jpg?raw=true)

From here the key matrix acts as the input method for the calculator, following this mapping:

![CalculatorLayout](https://github.com/Cipulot/SheepyPad/blob/main/Documents/imgs/calculator_layout.jpg?raw=true)

## Supported operands and operations

The calculator supports 2 operands , called `term_1` and `term_2` in the code (for reference). A series of checks is implemented so that the state of the calculator is always valid.

### 4 basic operations and signs

The input flow is as follows for the 4 basic operations:

1. user enters digits for `term_1`

    1.1 user presses `±` to change `term_1` sing

2. user selects an operation `+` , `-` , `*` or `/`

3. user enters digits for `term_2`

    3.1 user presses `±` to change `term_2` sing

4. user presses `=` to calculate the result

When the calculation result is displayed, the calculator will wait for the user to reset the state to the initial state via the `AC` key.

**Note:** if an operation is selected before any digit has being pressed the calculator treats `term_1` as a `0`. In this case when `*` or `/` is selected the return value will be `0` as the result. The indetermination case is also handled, returning `0`.

### Square Root

The `SQRT` function calculates the square root of the `term_1` operand. Therefore the `term_1` operand must be a positive number, otherwise the calculator will display `Imaginary Root!` as a result.

The input flow is as follows:

1. user enters digits for `term_1`

2. user presses `SQRT` to calculate the result

As for the 4 basic operations, when the calculation result is displayed, the calculator will wait for the user to reset the state to the initial state via the `AC` key.

#### **Notes:**

* The `SQRT` function is not supported for `term_2` operands. If you try to execute one of the 4 basic operations and then press `SQRT` this won't produce any output (the `SQRT` command is ignored).

* Again if no digits are entered for `term_1` the calculator will treat it as a `0` and return `0` as the result if `SQRT` is pressed.

    **Implementation of the `SQRT` function as above (`term1` → `operation` → `term__2` → `SQRT`) is in the work.**

## Implementation status

This table summarize the implementation status of the calculator.

| **Legend:**  | ✅ Supported | 🚧 Under Development | 💡 Planned |
|-|-|-|-|

|    Feature   |     Status    |
|:------------:|:-------------:|
|      `+`     |       ✅     |
|      `-`     |       ✅     |
|      `*`     |       ✅     |
|      `/`     |       ✅     |
|      `±`     |       ✅     |
|     `AC`     |       ✅     |
|    `SQRT`    |     ✅/🚧    |
|     `C`      |       💡      |
|    `.` aka decimal operands    |     🚧    |

![Calculator](https://github.com/Cipulot/SheepyPad/blob/main/Documents/imgs/calculator.jpg?raw=true)