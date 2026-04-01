| Supported Targets | ESP32-P4 | ESP32-S3 |
| ----------------- | -------- | -------- |

# Customizable ESP32 Boardcomputer

This project implements a custom-built boardcomputer for classic vehicles like the BMW E36. Instead of the standard BMW boardcomputer (which only displays average fuel consumption or broken light bulbs), or multifunctional clocks (date, time, temperature), this system provides a complete display of current engine parameters.

**Main Features:**
- Display of oil temperature, oil pressure, battery voltage, and time/temperature
- Four round TFT displays for separate gauges
- Adjustable number and type of displays
- Fully customizable design via LVGL

The E36 version uses four displays, each with its own gauge. All parameters are configurable.

## Hardware Overview

The project is based on a powerful ESP32-P4 that controls all peripherals.

**Components used for the E36 boardcomputer:**
- **ESP32-P4 WT9932P4-TINY** - Main processor
- **4x 1.28 Inch Round TFT LCD Display (240x240 RGB) with GC9A01 Driver** ([Link to AliExpress](https://de.aliexpress.com/item/1005009364283361.html))
- **Custom PCB** to connect the displays and peripherals with the ESP (in the `hardware/` directory)
- **5V Buzzer** for warnings when outside temperature is below 3°C
- **2x Buttons** for time adjustment
- **12V to 5V Converter** for power supply
- **BMW Oil Temperature and Pressure Sensor (Hella 6PP 010 378-201)** - PWM signal from engine
- or using analog **VDO sensors** for oil pressure and temperature

The datasheets for the used components can be found in the `datasheets/` directory.

## Software

- **FreeRTOS Tasks** for scheduling different operations
- **LVGL** for designing the gauges
- **ADC Sampling** of sensor values or alternatively **PWM Sampling** of oil pressure and oil temperature based on VDO sensor characteristics; PWM sampling is based on Hella Sensor 6PP 010 378-201
- **Modular Architecture** with separate directories for calculation, logging, LVGL-UI, and peripherals

## How to Flash the Project

1. **Requirements:**
   - ESP-IDF installed (version according to SDK configuration)
   - USB cable for the ESP32-P4

2. **Compile the project:**
   ```
   idf.py build
   ```

3. **Flash:**
   ```
   idf.py flash
   ```

4. **Start monitor:**
   ```
   idf.py monitor
   ```

For detailed instructions see the official ESP-IDF guides.

## Project Structure

```
├── CMakeLists.txt              # Main build configuration
├── sdkconfig                   # ESP-IDF configuration
├── main/                       # Main source code
│   ├── CMakeLists.txt
│   ├── main.c                  # Main entry point
│   ├── individual_config.h     # Configuration defines
│   ├── calculation/            # Calculation modules
│   ├── logging/                # Logging functions
│   ├── lvgl/                   # LVGL-UI and graphics
│   └── peripherie/             # Peripheral drivers (buzzer, buttons, etc.)
├── hardware/                   # PCB design and hardware files
├── datasheets/                 # Datasheets of components
├── fonts/                      # Fonts
├── png/                        # Images and icons
├── managed_components/         # ESP-IDF components
└── README.md                   # This file
```

## Troubleshooting

* **Flashing errors:**
  - Check the USB connection: run `idf.py -p PORT monitor` and restart the board to see logs.
  - Baud rate too high: reduce the baud rate in `menuconfig` and try again.

* **Display problems:**
  - Check SPI pins in `individual_config.h`
  - Ensure power supply (12V to 5V converter)

