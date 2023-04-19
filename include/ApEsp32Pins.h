#ifndef _APESP32PINS_H
#define _APESP32PINS_H

#include <Arduino.h>

// Software Serial pins config (oh and the LED pin) Pins are GPIO numbers, not ESP32 module pin no's 
#define RX_LED          32
#define TX_LED          33
#define LED_PIN         2

// Pin numbers for buttons
//#define BTN_UP          22
#define BTN_SELECT      4
#define BTN_DOWN        16
#define BTN_DEBOUNCE_MS 50

// Software Serial pins config Pins are GPIO numbers, not ESP32 module pin no's 
#define MAX_BUF_SIZE    20
#define RX_IN           25
#define RX_MON          26
#define TX_OUT          27

#endif // end _APESP32PINS_H