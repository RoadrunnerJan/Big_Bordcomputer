| Supported Targets | ESP32-P4 | ESP32-S3 |
| ----------------- | -------- | -------- |

# Customizable ESP32 Bordcomputer

The intention of this project is to build a customizable Bordcomputer for old vehicles like the BMW E36. Normaly this car could have a boardcomputer providing by BMW which shows something like the average gasoline consumption or broke light bulbs. Another option is a multifunctional clock which shows the date, time and temperature. There is no possibility to show the current oil temperature or pressure.

The aim of this project is to replace the standard bordcomputer by an own build computer which shows the actual oil temperature, pressure, voltage and the clock/termperature.

The version for the E36 is build with four displays. Each shows an own gauge for the measurements. The number of gauges is adjustable. The amount or type of display can get adjusted. The design can get adjusted, too.

# Overall Hardware:

The project uses a fast ESP32P4 which is connected to all the periphers.
The following elements are used for the E36 boardcomputer:
- ESP32P4 - WT9932P4-TINY
- 4x 1.28 Inch Round TFT LCD Display Module (240x240 RGB) with GC9A01 Driver (https://de.aliexpress.com/item/1005009364283361.html?spm=a2g0o.order_list.order_list_main.10.2d425c5foxNjLr&gatewayAdapt=glo2deu)
- Customized PCB Board to connect the Displays and the other periphery with the ESP (Uploaded in hardware directory of this project)
- 5V buzzer to idenicate the outdoor temperature under 3°C
- 2x buttons for changing the current time
- 12v to 5v converter
- BMW oil temperature and pressure sensor using a pwm signal to send the sensor values (Hella 6PP 010 378-201) - connected to the engine

The datasheets of the used elements are provided in the directory datasheet

# Software

- FreeRTOS tasks to schedule the different operations
- LVGL designs for the gauges
- PWM reading of the sensor

## How to flash











## ESP Help
Follow detailed instructions provided specifically for this example.

Select the instructions depending on Espressif chip installed on your development board:

- [ESP32 Getting Started Guide](https://docs.espressif.com/projects/esp-idf/en/stable/get-started/index.html)
- [ESP32-S2 Getting Started Guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s2/get-started/index.html)


## Example folder contents

The project **hello_world** contains one source file in C language [hello_world_main.c](main/hello_world_main.c). The file is located in folder [main](main).

ESP-IDF projects are built using CMake. The project build configuration is contained in `CMakeLists.txt` files that provide set of directives and instructions describing the project's source files and targets (executable, library, or both).

Below is short explanation of remaining files in the project folder.

```
├── CMakeLists.txt
├── pytest_hello_world.py      Python script used for automated testing
├── main
│   ├── CMakeLists.txt
│   └── hello_world_main.c
└── README.md                  This is the file you are currently reading
```

For more information on structure and contents of ESP-IDF projects, please refer to Section [Build System](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/build-system.html) of the ESP-IDF Programming Guide.

## Troubleshooting

* Program upload failure

    * Hardware connection is not correct: run `idf.py -p PORT monitor`, and reboot your board to see if there are any output logs.
    * The baud rate for downloading is too high: lower your baud rate in the `menuconfig` menu, and try again.

## Technical support and feedback

Please use the following feedback channels:

* For technical queries, go to the [esp32.com](https://esp32.com/) forum
* For a feature request or bug report, create a [GitHub issue](https://github.com/espressif/esp-idf/issues)

We will get back to you as soon as possible.
