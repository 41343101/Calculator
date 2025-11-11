# Calculator

A simple Qt-based calculator application with a 4x5 button layout.

## Features

- Basic arithmetic operations: addition (+), subtraction (-), multiplication (*), division (/)
- Backspace functionality to delete the last entered digit
- Decimal point support for floating-point calculations
- Clean, grid-based UI layout

## Button Layout

```
[←] [/] [*] [-]
[7] [8] [9] [+]
[4] [5] [6] │ │
[1] [2] [3] [=]
[  0  ] [.]
```

Where:
- `←` is the backspace button
- `0` spans two columns
- `+` spans two rows (aligned with rows 1 and 2)
- `=` spans two rows (aligned with rows 3 and 4)

## Building

This project requires Qt 5 or Qt 6. To build:

```bash
cd Calculator
qmake Calculator.pro
make
```

## Running

After building, run the calculator:

```bash
./Calculator
```

## Implementation Details

The calculator uses:
- `QDialog` as the main window
- `QLineEdit` for the display (read-only)
- `QPushButton` for all calculator buttons
- `QGridLayout` for the button arrangement
- Qt signals and slots for event handling

The calculator maintains state using:
- `currentValue`: The accumulated result
- `pendingOperator`: The operation to be performed
- `waitingForOperand`: Flag indicating if waiting for next number input