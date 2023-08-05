#ifndef _APESP32PINS_H
#define _APESP32PINS_H

#include <Arduino.h>

// Software Serial pins config (oh and the LED pin) Pins are GPIO numbers, not ESP32 module pin no's 
#define RX_LED          32
#define TX_LED          33
#define LED_PIN         2

// The max no of bytes expected in a SeaTalk command 
#define MAX_BUF_SIZE    20

// Software Serial pins config Pins are GPIO numbers, not ESP32 module pin no's 
#define RX_IN           25
#define RX_MON          26
#define TX_OUT          27

#endif // end _APESP32PINS_H