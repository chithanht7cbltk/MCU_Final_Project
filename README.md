# STM32 Traffic Light Controller

Embedded traffic light control system implemented on STM32 using C.  
The system demonstrates core embedded concepts such as **finite state machines, software timers, button debouncing, and peripheral interfacing**.

The traffic light timing can be configured through push buttons and is displayed on an LCD screen.

---

## Hardware Setup

- STM32 microcontroller board
- 12 LEDs representing two traffic lanes
- 3 push buttons
- 16x2 LCD with I2C interface
- Breadboard and discrete components

System status and timing information are displayed on the LCD.

---

## System Features

### Automatic Mode

The system simulates a two-lane traffic intersection.

Each lane contains:

- Red
- Yellow
- Green

Default timing configuration:

- Red: 5 seconds
- Green: 3 seconds
- Yellow: 2 seconds

The lights operate sequentially between the two lanes according to the configured timing.

---

### Setting Mode

Three push buttons are used to configure the system:

Button functions:

- **MODE button**  
  Select which light timing to configure (Red / Yellow / Green)

- **TIME button**  
  Increase the time value for the selected light

- **EXIT button**  
  Exit setting mode and return to automatic operation

All buttons implement:

- software **debouncing**
- **long press handling**

---

## Embedded Concepts Demonstrated

This project demonstrates several important embedded system techniques:

- Finite State Machine (FSM) design
- Software timer implementation
- Button debouncing
- Cooperative task scheduling
- Peripheral communication (LCD via I2C)
- Modular embedded C architecture

---

## Software Architecture

Main modules:
