STM32F401RE ADC Bare-Metal Implementation

Overview
This project demonstrates how to use the Analog-to-Digital Converter (ADC) on the STM32F401RE Nucleo board using pure register-level programming with CMSIS.
No HAL drivers, no CubeMX code generation, and no external libraries were used.
The program reads analog voltage values from a potentiometer connected to pin PA0, converts them into 12‑bit digital values (0–4095), calculates the voltage, and sends both the raw ADC value and voltage reading to the PC over UART2.

Features
* Bare-metal ADC configuration in single conversion mode
* UART2 communication via the Nucleo’s virtual COM port
* Integer-based voltage calculation (avoids floating-point printing issues)
* Tested with both fixed voltages and a potentiometer
* Clean, minimal code structure for easy understanding

Hardware Requirements
* STM32 Nucleo-F401RE board
* Potentiometer (0–3.3 V output range)
* USB cable (for power, programming, and serial communication)
* Jumper wires

Connections
PA0  -> Potentiometer output

Software Requirements
* STM32CubeIDE or Keil uVision5
* ARM CMSIS headers for STM32F4
* Serial monitor such as PuTTY or Arduino Serial Monitor

Code Description
The program is divided into three main parts:

1. UART2\_Init
   Configures PA2 and PA3 for USART2 at 115200 baud. This allows the board to send ADC results to a PC via USB.

2. ADC1\_Init
   Configures PA0 in analog mode and sets up ADC1 to perform single conversions. The ADC is enabled, and the input channel is set to channel 0.

3. ADC1\_Read
   Starts a single ADC conversion, waits for it to complete, and returns the 12-bit result.

In the main loop, the ADC value is read, converted to millivolts, and then formatted into a string showing both the raw ADC value and the calculated voltage. This string is sent to the PC via UART. A small delay is added to make the output readable.

How to Build and Run
1. Clone this repository or download it as a ZIP file.
2. Open the project in STM32CubeIDE or Keil uVision5.
3. Build the project and flash it to the Nucleo-F401RE.
4. Open a serial monitor on your PC, set it to 115200 baud.
5. Rotate the potentiometer and observe the changing ADC values and voltages.

Sample Output
ADC Test with Voltage
ADC:    0  Voltage: 0.000 V
ADC: 2047  Voltage: 1.650 V
ADC: 4095  Voltage: 3.300 V

Learning Outcome
By completing this project, you will understand how to configure and use the STM32F4’s ADC at the register level, how to send ADC readings over UART, and how to work without high-level abstraction layers like HAL.
You will also learn the benefits of integer-based calculations in embedded systems and the importance of testing peripherals one at a time before integration.

