# Generic STM32 Peripheral Drivers

[![Language: C](https://img.shields.io/badge/language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Platform: STM32](https://img.shields.io/badge/platform-STM32-orange.svg)](https://www.st.com/en/microcontrollers-microprocessors/stm32-32-bit-arm-cortex-mcus.html)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](#license)
<img src="https://img.shields.io/badge/board-Nucleo--F401RE-blue.svg">

A collection of generic, low-level STM32 peripheral drivers written in C from scratch. The project is designed to make bare-metal embedded development easier to study and understand by accessing hardware registers directly through CMSIS headers, without depending on STM32 HAL, CubeMX-generated code, or other vendor abstraction layers.

This repository is intended for embedded engineers, firmware developers, and students who want to learn how Cortex-M peripherals work at the register level and build a reusable foundation for STM32 projects.

## Features

- **FPU driver** — Enables and configures floating-point support on Cortex-M devices that include a Floating Point Unit.
- **UART driver** — Provides low-level serial communication configuration and data transfer.
- **Timebase driver** — Uses SysTick to provide a system time base for delays, periodic timing, and time measurement.
- **GPIO driver** — Configures digital input/output pins and controls their logic state.
- **ADC driver** — Configures analog-to-digital conversion and reads analog input values.

## Repository Structure

```text
Generic-Drivers-/
├── 0_test/                      # Test and sandbox project for experimenting with drivers
├── 1_system_drivers-fpu/        # Floating Point Unit driver
├── 2_system_drivers-uart/       # Universal Asynchronous Receiver/Transmitter driver
├── 3_system_drivers-timebase/   # SysTick-based system timebase driver
├── 4_system_drivers-gpio/       # General-Purpose Input/Output driver
├── 5_system_drivers-adc/        # Analog-to-Digital Converter driver
├── chip_headers/
│   └── CMSIS/                   # ARM CMSIS and STM32 device header files
└── .gitignore                   # Git ignore rules
```

The numbered driver directories provide a simple ordering for the system-level components and make it straightforward to add additional drivers as the project grows.

## Driver Overview

### FPU Driver

The Floating Point Unit (FPU) accelerates single-precision floating-point calculations on supported Cortex-M processors, such as Cortex-M4 devices with hardware floating-point support. The FPU driver enables the required coprocessor access and prepares the processor to execute floating-point instructions. It uses the processor's system control registers directly and does not rely on STM32 HAL initialization code.

### UART Driver

A Universal Asynchronous Receiver/Transmitter (UART) provides asynchronous serial communication between the microcontroller and external devices, development tools, or another controller. The UART driver is intended to handle low-level peripheral setup—such as clocking, baud-rate configuration, frame format, and enable controls—and to provide basic transmit and receive operations. Register-level implementation keeps the communication path explicit and makes the driver suitable for learning, debugging, and lightweight firmware projects.

### Timebase Driver

The timebase driver uses the Cortex-M SysTick peripheral to generate a regular system tick. This provides the timing foundation needed for millisecond delays, periodic tasks, timeout handling, and elapsed-time measurement. The implementation is designed to expose the core timing mechanism directly, rather than hiding it behind an RTOS or vendor-specific delay API.

### GPIO Driver

General-Purpose Input/Output (GPIO) pins are used to connect firmware to digital signals such as LEDs, buttons, control lines, and peripheral alternate functions. The GPIO driver provides the low-level configuration needed to select pin modes and control or inspect pin states. Direct register access keeps mode, output type, speed, pull configuration, and pin state behavior visible to the developer.

### ADC Driver

An Analog-to-Digital Converter (ADC) converts an analog voltage into a digital value that firmware can process. The ADC driver provides the register-level setup required to configure conversion behavior and read converted samples from analog channels. This approach is useful for applications such as sensor acquisition, voltage monitoring, and embedded control where understanding sampling and conversion configuration is important.

## Getting Started

### 1. Clone the repository

```bash
git clone https://github.com/yougiyo/Generic-Drivers-.git
cd Generic-Drivers-
```

### 2. Choose a build environment

You can integrate the drivers into either of the following workflows:

- **GNU Arm Embedded Toolchain** using `arm-none-eabi-gcc`, a linker script, startup code, and a Makefile or equivalent build system.
- **STM32CubeIDE** by adding the relevant driver source and header directories to an STM32 project. CubeIDE can be used as an editor and build environment without requiring the drivers themselves to depend on STM32 HAL or CubeMX-generated peripheral code.

A typical bare-metal toolchain also includes:

- `arm-none-eabi-gcc`
- `arm-none-eabi-ld` or GCC linker support
- `arm-none-eabi-objcopy`
- `arm-none-eabi-size`
- A debugger/programmer such as ST-LINK

### 3. Integrate a driver

1. Select the driver directory needed by your application.
2. Add its `.c` files to your build.
3. Add the corresponding driver directory and `chip_headers/CMSIS` to the compiler include paths.
4. Select the CMSIS device header that matches your STM32 part.
5. Configure the MCU clock and peripheral assumptions required by the driver.
6. Call the driver's initialization function early in `main()` before using the peripheral.

For example, a project may include driver sources and headers with compiler options similar to:

```bash
arm-none-eabi-gcc \
  -I./chip_headers/CMSIS \
  -I./1_system_drivers-fpu \
  -I./2_system_drivers-uart \
  -I./3_system_drivers-timebase \
  -I./4_system_drivers-gpio \
  -I./5_system_drivers-adc \
  ...
```

The exact source files, startup code, linker script, device macro, clock configuration, and compiler flags depend on the target STM32 family and board.

## Dependencies

The repository includes the CMSIS headers required for processor and device register definitions:

```text
chip_headers/CMSIS/
```

No STM32 HAL or CubeMX-generated peripheral driver is required by the design of this library. You must still provide the device-specific startup code, linker script, system clock configuration, and programming/debugging setup for your target board.

## Target Hardware

Developed and tested on the STM32 Nucleo-F401RE board (STM32F401RE, ARM Cortex-M4 with FPU, up to 84 MHz, 512 KB Flash, 96 KB SRAM)

### Tested On
| Board | MCU | Core | Max Clock | Flash | RAM |
|-------|-----|------|-----------|-------|-----|
| STM32 Nucleo-F401RE | STM32F401RE | Cortex-M4 + FPU | 84 MHz | 512 KB | 96 KB |

## Design Philosophy

- Keep the implementation close to the hardware.
- Prefer clear register-level code over opaque abstractions.
- Avoid mandatory dependencies on STM32 HAL and CubeMX.
- Make peripheral initialization and configuration visible to the application developer.
- Provide a useful starting point for learning and extending bare-metal firmware.

## Contributing

Contributions are welcome. To add a new driver:

1. Create a new directory using the numbered convention, for example `6_system_drivers-spi/`.
2. Keep the implementation self-contained with clear header and source files.
3. Use CMSIS/device registers directly where appropriate.
4. Document initialization requirements, supported devices, and example usage.
5. Add a small test or sandbox example under `0_test/` when practical.
6. Update this README with the new driver and its directory.
7. Open a pull request describing the peripheral, supported target devices, and validation performed.

## License

This project is licensed under the **MIT License**. See the [LICENSE](LICENSE) file for details.

## Status

All 5 drivers implemented and validated on the STM32 Nucleo-F401RE (STM32F401RE). Suitable as a starting point for other STM32F4 family devices.
