#include "includes.h"

/*
Best Practices für saubere Werte
Glättungskondensator: Schalte einen kleinen Kondensator (z.B. 0,1 µF) zwischen den ADC-Pin und GND, um elektrisches Rauschen zu minimieren.
Kurze Leitungen: Halte die analogen Zuleitungen so kurz wie möglich und verlege sie nicht direkt neben digitalen Leitungen mit hoher Schaltfrequenz (wie PWM). 


ADC1_CH0: GPIO 32 -> ADC_AMBI_PIN
ADC1_CH1: GPIO 33 -> ADC_VOLT_PIN
ADC1_CH2: GPIO 34 -> ADC_OUT_TEMP_PIN


*/


/* Spannungsteiler Voltage

Wir wollen 
25V auf maximal 3,0V am ADC-Pin reduzieren (Puffer bis 3,3 V einplanen).
R1 (oben): 10k
R2 (unten): 1.5k - Z-Diode parallel zu R2; Kondensator (100nF) parallel zu R2

Da du mit 20 V arbeitest, empfehle ich dringend eine Z-Diode (3,3 V) parallel zu R2 (Kathode an den ADC-Pin, Anode an GND). Sollte 
R2 jemals den Kontakt verlieren oder die Eingangsspannung massiv steigen, begrenzt die Diode die Spannung am ESP32 auf 3,3 V.

 -> Berechnung: Spannung_Real = Spannung_ADC_mV * (11.5 / 1.5) / 1000.0;

 -> 25V -> ca 2.67V
 -> 14.4V -> ca 1.54V
*/

adc_oneshot_unit_handle_t adc1_handle;
adc_oneshot_unit_init_cfg_t init_config1 = { .unit_id = ADC_UNIT_1 };
adc_oneshot_new_unit(&init_config1, &adc1_handle);

adc_oneshot_chan_cfg_t config = {
    .bitwidth = ADC_BITWIDTH_DEFAULT,
    .atten = ADC_ATTEN_DB_12, // WICHTIG: 12dB für Bereich bis ~3.1V
};
adc_oneshot_config_channel(adc1_handle, ADC_CHANNEL_0, &config);

// In der Loop:
int raw;
adc_oneshot_read(adc1_handle, ADC_CHANNEL_0, &raw);
// Umrechnung: Spannung_Real = (Spannung_ADC * (R1 + R2)) / R2



/* Dimmer

R1 (oben): 10k
R2 (unten): 2.2k - Z-Diode parallel zu R2; Kondensator (100nF) parallel zu R2

Max: 10.74V ->1.94V
Min: 2.29V -> 0.41V
Aus: 0V -> 0V 

-> ToDo: Hysterese für die Beleuchtungsumsetzung
-> ToDo: Konvertierung des Eingangs zu PWM signal am Display
*/

// Mapping im ESP-IDF Code (Grobentwurf)
uint32_t adc_mv = 0;
adc_oneshot_read(adc_handle, CHANNEL_DIMMER, &adc_mv);

float v_in = (float)adc_mv * (12.2f / 2.2f) / 1000.0f; // Rückrechnung auf Bordspannung

int display_pwm = 0;
if (v_in < 1.0f) {
    display_pwm = 255; // Volle Helligkeit am Tag (Licht aus)
} else {
    // Nachtmodus: Dimmen basierend auf Instrumentenbeleuchtung
    // v_in 2.29V -> Dunkel | v_in 10.74V -> Hell (aber gedimmt für Nacht)
    display_pwm = map(v_in, 2.29, 10.74, 50, 200); 
}


/* Außentemperatur
Hardware: 
    -> Sensor: Zwischen ADC-Pin und GND (GND am besten direkt mit ESP verbinden).
    -> Referenz: 4.7k !Präzisionswiderstand! max 1% (eventuell ein NTC 4.7k bei 25°C in E36 verbaut)
        -> verbaut: zwischen 3.3V und ADC Pin
    -> Kondensator: 100 nF (zwischen ADC-Pin und GND).
-> Kennlinie des Sensors (eventuell -> Prüfen!)
    -> -20°C -> ca 28k  -> 2.82V am ADC
    -> 0°C   -> ca 13k  -> 2.41V am ADC
    -> 25°C  -> ca 4.7k -> 1.65V am ADC
    -> 50°C  -> ca 1.8k -> 0.91V am ADC
*/


#define SERIES_RESISTOR 4700.0f // Dein 4,7k Widerstand
#define NOMINAL_RESISTANCE 4700.0f
#define NOMINAL_TEMPERATURE 25.0f
#define B_COEFFICIENT 3950.0f // Typischer B-Wert für KFZ-NTCs

float get_outside_temp(uint32_t adc_mv) {
    if (adc_mv == 0 || adc_mv >= 3300) return -99.0f; // Fehler (Kurzschluss/Bruch)

    // 1. Widerstand des NTC berechnen
    float voltage = (float)adc_mv / 1000.0f;
    float resistance = SERIES_RESISTOR / ( (3.3f / voltage) - 1.0f );

    // 2. Steinhart-Hart Näherung
    float steinhart;
    steinhart = resistance / NOMINAL_RESISTANCE;     // (R/Ro)
    steinhart = log(steinhart);                      // ln(R/Ro)
    steinhart /= B_COEFFICIENT;                      // 1/B * ln(R/Ro)
    steinhart += 1.0f / (NOMINAL_TEMPERATURE + 273.15f); // + (1/To)
    steinhart = 1.0f / steinhart;                    // Invertieren
    steinhart -= 273.15f;                            // In Celsius umwandeln

    return steinhart;
}