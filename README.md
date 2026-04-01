| Supported Targets | ESP32-P4 | ESP32-S3 |
| ----------------- | -------- | -------- |

# Customizable ESP32 Bordcomputer

Dieses Projekt implementiert einen maßgeschneiderten Bordcomputer für klassische Fahrzeuge wie den BMW E36. Anstatt der standardmäßigen BMW-Bordcomputer (die nur Durchschnittsverbrauch oder defekte Glühlampen anzeigen), oder multifunktionaler Uhren (Datum, Uhrzeit, Temperatur), bietet dieses System eine vollständige Anzeige der aktuellen Motorparameter.

**Hauptfunktionen:**
- Anzeige von Öltemperatur, Öldruck, Bordspannung und Uhrzeit/Temperatur
- Vier runde TFT-Displays für separate Messinstrumente
- Anpassbare Anzahl und Typ der Displays
- Vollständig anpassbares Design über LVGL

Die E36-Version verwendet vier Displays, jedes mit einem eigenen Messinstrument. Alle Parameter sind konfigurierbar.

## Hardware-Übersicht

Das Projekt basiert auf einem leistungsstarken ESP32-P4, der alle Peripheriegeräte steuert.

**Verwendete Komponenten für den E36-Bordcomputer:**
- **ESP32-P4 WT9932P4-TINY** - Hauptprozessor
- **4x 1.28 Zoll Rundes TFT LCD Display (240x240 RGB) mit GC9A01 Treiber** ([Link zu AliExpress](https://de.aliexpress.com/item/1005009364283361.html))
- **Angepasste PCB** zur Verbindung der Displays und Peripherie mit dem ESP (im `hardware/` Verzeichnis)
- **5V Buzzer** zur Warnung bei Außentemperaturen unter 3°C
- **2x Tasten** zur Zeiteinstellung
- **12V zu 5V Wandler** für Stromversorgung
- **BMW Öltemperatur- und Druck-Sensor (Hella 6PP 010 378-201)** - PWM-Signal vom Motor

Die Datenblätter der verwendeten Komponenten finden sich im `datasheets/` Verzeichnis.

## Software

- **FreeRTOS Tasks** zur Planung der verschiedenen Operationen
- **LVGL** für die Gestaltung der Messinstrumente
- **PWM-Abtastung** der Sensoren
- **Modulare Architektur** mit separaten Verzeichnissen für Berechnung, Logging, LVGL-UI und Peripherie

## Wie man das Projekt flashen kann

1. **Voraussetzungen:**
   - ESP-IDF installiert (Version entsprechend der SDK-Konfiguration)
   - USB-Kabel für den ESP32-P4

2. **Projekt kompilieren:**
   ```
   idf.py build
   ```

3. **Flashen:**
   ```
   idf.py flash
   ```

4. **Monitor starten:**
   ```
   idf.py monitor
   ```

Für detaillierte Anleitungen siehe die offiziellen ESP-IDF Guides.

## Projektstruktur

```
├── CMakeLists.txt              # Haupt-Build-Konfiguration
├── sdkconfig                   # ESP-IDF Konfiguration
├── main/                       # Hauptquellcode
│   ├── CMakeLists.txt
│   ├── main.c                  # Haupteinstiegspunkt
│   ├── individual_config.h     # Konfigurationsdefines
│   ├── calculation/            # Berechnungsmodule
│   ├── logging/                # Logging-Funktionen
│   ├── lvgl/                   # LVGL-UI und Grafiken
│   └── peripherie/             # Peripherie-Treiber (Buzzer, Buttons, etc.)
├── hardware/                   # PCB-Design und Hardware-Dateien
├── datasheets/                 # Datenblätter der Komponenten
├── fonts/                      # Schriftarten
├── png/                        # Bilder und Icons
├── managed_components/         # ESP-IDF Komponenten
└── README.md                   # Diese Datei
```

## Troubleshooting

* **Flash-Fehler:**
  - Überprüfe die USB-Verbindung: `idf.py -p PORT monitor` ausführen und das Board neu starten, um Logs zu sehen.
  - Baudrate zu hoch: In `menuconfig` die Baudrate reduzieren und erneut versuchen.

* **Anzeigeprobleme:**
  - SPI-Pins in `individual_config.h` überprüfen
  - Stromversorgung sicherstellen (12V zu 5V Wandler)

## Technischer Support und Feedback

Bei Fragen oder Problemen bitte ein Issue im Repository erstellen oder den Code kommentieren.

Please use the following feedback channels:

* For technical queries, go to the [esp32.com](https://esp32.com/) forum
* For a feature request or bug report, create a [GitHub issue](https://github.com/espressif/esp-idf/issues)

We will get back to you as soon as possible.
