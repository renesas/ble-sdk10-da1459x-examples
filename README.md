# Smartbond SDK10 DA1459x Application Examples

This is the repository storing example for the [DA1459x family](https://www.renesas.com/us/en/products/wireless-connectivity/bluetooth-low-energy).

The available devices in the DA1459x family are:

- [DA14592](https://www.renesas.com/us/en/products/wireless-connectivity/bluetooth-low-energy)

For information about the DA1459x platform and how to bring up your development kit, please refer to the [Getting started User Manual](https://lpccs-docs.renesas.com/um-b-090-da1469x_getting_started/index.html)

## Example usage

This assume you went through the getting started and you have successfully built, loaded and ran a first application on the DA14592.

For additional examples:

- Clone this repository
- From the workspace you have setup go to **File->Import**
- Select **General -> Dialog SDK Projects** and click Next
- In the `Select root directory` input the path where you cloned this repository
- Select the example(s) you want to import and click finish.
- A (dialog) window pops up and choose the Toolchain version 7.x and the Target Device DA14592. 

You can now navigate and build the imported examples.

## Example compatibility

Not all the examples will run on the latest version of the SDK10, the tested version is indicated in the Readme. If you find an example that needs porting to the latest version please report it in the issues.

## Example overview

<!---
AUTOMATICALLY GENERATED CONTENT, DO NOT EDIT!
See .pre-commit-config.yaml for more info
@EXAMPLE_TABLE_BEGIN@
--->
<table><tr><th>Name</th><th>Boards</th><th>Description</th></tr><tr><td><a href="./connectivity/active_scanner_sample_code">active_scanner_sample_code</a></td><td valign="top"><a href="https://www.renesas.com/en/products/da14592"><img alt="DA14592" src="https://img.shields.io/badge/DA14592-slategray"/></a></td><td valign="top"><p>Example demonstrating setting up the Bluetooth controller in central role.
</p><p>Keywords: Central, BLE, CLI</p></td></tr><tr><td><a href="./helpers/armv8_fault_handling_example">armv8_fault_handling_example</a></td><td valign="top"><a href="https://www.renesas.com/en/products/da14592"><img alt="DA14592" src="https://img.shields.io/badge/DA14592-slategray"/></a></td><td valign="top"><p>Example showcasing how to configure custom exception handlers. Includes a
basic CLI interface for manually triggering various kinds of fault
conditions.
</p><p>Keywords: ARMv8, M33, CLI</p></td></tr><tr><td><a href="./helpers/bare_metal_hello_world">bare_metal_hello_world</a></td><td valign="top"><a href="https://www.renesas.com/en/products/da14592"><img alt="DA14592" src="https://img.shields.io/badge/DA14592-slategray"/></a></td><td valign="top"><p>Hello world without the FreeRTOS scheduler running.
</p><p>Keywords: watchdog, bare-metal</p></td></tr><tr><td><a href="./connectivity/ble_custom_service_example">ble_custom_service_example</a></td><td valign="top"><a href="https://www.renesas.com/en/products/da14592"><img alt="DA14592" src="https://img.shields.io/badge/DA14592-slategray"/></a></td><td valign="top"><p>Example showcasing two arbitrary service characteristic attributes using
the custom Bluetooth database.
</p><p>Keywords: BLE, attribute, service</p></td></tr><tr><td><a href="./helpers/DA1459x_LED_driver">blinky</a></td><td valign="top"><a href="https://www.renesas.com/en/products/da14592"><img alt="DA14592" src="https://img.shields.io/badge/DA14592-slategray"/></a></td><td valign="top"><p>Periodically blink LED1.
</p><p>Keywords: LED, sleep</p></td></tr><tr><td><a href="./features/cmsis_dsp_sample_code">cmsis_dsp_sample_code</a></td><td valign="top"><a href="https://www.renesas.com/en/products/da14592"><img alt="DA14592" src="https://img.shields.io/badge/DA14592-slategray"/></a></td><td valign="top"><p>The ARM CMSIS DSP library&#x27;s arm_sin_cos_example.
</p><p>Keywords: ARM, CMSIS, DSP</p></td></tr><tr><td><a href="./features/cmsis_nn_sample_code">cmsis_nn_sample_code</a></td><td valign="top"><a href="https://www.renesas.com/en/products/da14592"><img alt="DA14592" src="https://img.shields.io/badge/DA14592-slategray"/></a></td><td valign="top"><p>Four of the ARM CMSIS NN library&#x27;s tests
(fully_connected_int16_arm_fully_connected_s16,
fully_connected_int16_big_arm_fully_connected_s16,
int16xint8_arm_convolve_fast_s16, requantize_s64_arm_convolve_fast_s16).
</p><p>Keywords: ARM, CMSIS, NN, neural network</p></td></tr><tr><td><a href="./features/crypto_adapter_example">crypto_adapter_example</a></td><td valign="top"><a href="https://www.renesas.com/en/products/da14592"><img alt="DA14592" src="https://img.shields.io/badge/DA14592-slategray"/></a></td><td valign="top"><p>Sample code for using the hardware-accelerated crypto operations using the
crypto adapter API.
</p><p>Keywords: Cryptography, AES, HASH</p></td></tr><tr><td><a href="./features/da1459x_rtc_example">da1459x_rtc_example</a></td><td valign="top"><a href="https://www.renesas.com/en/products/da14592"><img alt="DA14592" src="https://img.shields.io/badge/DA14592-slategray"/></a></td><td valign="top"><p>Showcase of real-time clock timer events.
</p><p>Keywords: RTC, alarm timer</p></td></tr><tr><td><a href="./features/dsps_ble_central">dsps_ble_central</a></td><td valign="top"><a href="https://www.renesas.com/en/products/da14592"><img alt="DA14592" src="https://img.shields.io/badge/DA14592-slategray"/></a></td><td valign="top"><p>Emulated serial cable communication (scanner side).
</p><p>Keywords: Serial Port Service, GAP central</p></td></tr><tr><td><a href="./features/dsps_ble_peripheral">dsps_ble_peripheral</a></td><td valign="top"><a href="https://www.renesas.com/en/products/da14592"><img alt="DA14592" src="https://img.shields.io/badge/DA14592-slategray"/></a></td><td valign="top"><p>Emulated serial cable communication (advertiser side).
</p><p>Keywords: Serial Port Service, GAP advertiser</p></td></tr><tr><td><a href="./helpers/empty">empty</a></td><td valign="top"><a href="https://www.renesas.com/en/products/da14592"><img alt="DA14592" src="https://img.shields.io/badge/DA14592-slategray"/></a></td><td valign="top"><p>Empty project (starting point) for non-BLE applications.
</p></td></tr><tr><td><a href="./helpers/empty_ble">empty_ble</a></td><td valign="top"><a href="https://www.renesas.com/en/products/da14592"><img alt="DA14592" src="https://img.shields.io/badge/DA14592-slategray"/></a></td><td valign="top"><p>Empty project (starting point) including BLE sources / libraries.
</p></td></tr><tr><td><a href="./connectivity/glucose_sensor_sample_code">glucose_sensor_sample_code</a></td><td valign="top"><a href="https://www.renesas.com/en/products/da14592"><img alt="DA14592" src="https://img.shields.io/badge/DA14592-slategray"/></a></td><td valign="top"><p>Bluetooth service demonstrating Bluetooth Glucose Service (GLS) and Glucose
Profile (GLP).
</p><p>Keywords: BLE, GLS, GLP</p></td></tr><tr><td><a href="./interfaces/gpadc_adapter_example">gpadc_adapter_example</a></td><td valign="top"><a href="https://www.renesas.com/en/products/da14592"><img alt="DA14592" src="https://img.shields.io/badge/DA14592-slategray"/></a></td><td valign="top"><p>Application demonstrating using the general-purpose ADC peripheral with the
help of the GPADC adapter layer.
</p><p>Keywords: ADC</p></td></tr><tr><td><a href="./interfaces/gpio_handling_example">gpio_handling_example</a></td><td valign="top"><a href="https://www.renesas.com/en/products/da14592"><img alt="DA14592" src="https://img.shields.io/badge/DA14592-slategray"/></a></td><td valign="top"><p>This sample code demonstrates using GPIO pins that are handled directly by
developers (outside adapter context).
</p><p>Keywords: GPIO, PD_COM, sleep</p></td></tr><tr><td><a href="./interfaces/i2c_eeprom_example">i2c_eeprom_example</a></td><td valign="top"><a href="https://www.renesas.com/en/products/da14592"><img alt="DA14592" src="https://img.shields.io/badge/DA14592-slategray"/></a></td><td valign="top"><p>This example implements a simple read and write communication scenario over
the I2C interface with a MirkoE EEPROM Click ClickBoard.
</p><p>Keywords: I2C, EEPROM</p></td></tr><tr><td><a href="./interfaces/i2c_example">i2c_example</a></td><td valign="top"><a href="https://www.renesas.com/en/products/da14592"><img alt="DA14592" src="https://img.shields.io/badge/DA14592-slategray"/></a></td><td valign="top"><p>This example implements a simple read and write communication scenario over
the I2C interface with a MikroE Temp&amp;Hum 17 ClickBoard.
</p><p>Keywords: I2C, sensor</p></td></tr><tr><td><a href="./helpers/map_clocks_to_gpio">map_clocks_to_gpio</a></td><td valign="top"><a href="https://www.renesas.com/en/products/da14592"><img alt="DA14592" src="https://img.shields.io/badge/DA14592-slategray"/></a></td><td valign="top"><p>This sample code demonstrates mapping system clocks to GPIO, typically for
debugging purposes. The clocks that can be exported are XTAL32K, RC32K,
RCLP, XTAL32M, RC32M as well as DIVN.
</p><p>Keywords: GPIO, CLI, pin control</p></td></tr><tr><td><a href="./features/quadrature_decoder_sample_code">quadrature_decoder_sample_code</a></td><td valign="top"><a href="https://www.renesas.com/en/products/da14592"><img alt="DA14592" src="https://img.shields.io/badge/DA14592-slategray"/></a></td><td valign="top"><p>This sample code demonstrates using the quadrature decoder peripheral
supported by the DA1459x family of devices. The decoder can decode three
pairs of axes as illustrated below reporting step count and direction.
</p><p>Keywords: QDEC</p></td></tr><tr><td><a href="./interfaces/spi_example">spi_example</a></td><td valign="top"><a href="https://www.renesas.com/en/products/da14592"><img alt="DA14592" src="https://img.shields.io/badge/DA14592-slategray"/></a></td><td valign="top"><p>This application shows how to use the SPI adapter API.
</p><p>Keywords: SPI, adapter</p></td></tr><tr><td><a href="./interfaces/spi_write_read_example">spi_write_read_example</a></td><td valign="top"><a href="https://www.renesas.com/en/products/da14592"><img alt="DA14592" src="https://img.shields.io/badge/DA14592-slategray"/></a></td><td valign="top"><p>This example implements a simple write and read communication scenario over
the SPI interface with the SPI adapter layer using the LSM6DSL ClickBoard.
</p><p>Keywords: SPI, adapter</p></td></tr><tr><td><a href="./features/suoserial_sample_code">suoserial_sample_code</a></td><td valign="top"><a href="https://www.renesas.com/en/products/da14592"><img alt="DA14592" src="https://img.shields.io/badge/DA14592-slategray"/></a></td><td valign="top"><p>This example demonstrates Software Update over UART, namely SUOSERIAL.
</p><p>Keywords: SUOTA, UART, CLI</p></td></tr><tr><td><a href="./features/timers_sample_code">timer1_demonstration_sample_code</a></td><td valign="top"><a href="https://www.renesas.com/en/products/da14592"><img alt="DA14592" src="https://img.shields.io/badge/DA14592-slategray"/></a></td><td valign="top"><p>This example uses the first HW timer block instance (HW_TIMER) to generate
PWM pulses of 1kHz are on P0.12.
</p><p>Keywords: PWM, timer</p></td></tr><tr><td><a href="./interfaces/UART_adaptor_example">UART</a></td><td valign="top"><a href="https://www.renesas.com/en/products/da14592"><img alt="DA14592" src="https://img.shields.io/badge/DA14592-slategray"/></a></td><td valign="top"><p>This application demonstrates the use of 2 UARTs through the adapters
abstraction layer.
</p><p>Keywords: UART, adapter</p></td></tr></table>
<!---
@EXAMPLE_TABLE_END@
--->

