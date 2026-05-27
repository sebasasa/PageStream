# PageStream
### A HAL for Arduino and U8G2lib, test your interface ACCURATELY right on your computer, without even changing the code.

PageStream is a lightweight, high-fidelity simulator for Arduino projects using the U8g2 library in page-buffered mode. It allows you to develop and debug your display logic on your computer using SFML, ensuring that what you see in the simulator is exactly what you get on the real hardware.

## Features
- **Binary Compatibility**: Write pure Arduino code in `.ino` format.
- **U8g2 Emulation**: Supports core U8g2 methods like `drawPixel`, `drawStr`, `firstPage`, and `nextPage`.
- **Hardware Mocking**: Simulated `analogRead`, `digitalRead`, `millis`, and `Serial`.
- **Interactive**: Real-time mouse and keyboard input mapped to Arduino pins.

## Structure
- `sketch/`: Your Arduino code (`main.ino`).
- `simulator/`: The SFML engine that runs the simulation.
- `include/`: Hardware abstraction layers (`Arduino.h`, `U8g2lib.h`).

## Getting Started
1. Install SFML.
2. Run `make`.
3. Execute `./u8g2_sim`.

---
*Created with Gemini CLI.*
