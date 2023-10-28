#ifndef _APESP32PINS_H
#define _APESP32PINS_H

#include <Arduino.h>

// Software Serial pins config. Pins are GPIO numbers, not ESP32 module pin no's 
#define LED_PIN         GPIO_NUM_2

// The max no of bytes expected in a SeaTalk command 
#define MAX_BUF_SIZE    20

// Software Serial pins config Pins are GPIO numbers, not ESP32 module pin no's 
#define RX_IN           GPIO_NUM_25
#define RX_MON          GPIO_NUM_26
#define TX_OUT          GPIO_NUM_27

#define BEEPERPIN          GPIO_NUM_4
#define TFTBACKLIGHTPIN    GPIO_NUM_16

// TFT Pins are in platformio.ini

#endif // end _APESP32PINS_H