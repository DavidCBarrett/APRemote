#pragma once

#include <Arduino.h>

//
// Uses Arduino LEDC PWM functions to set the TFT backlight brightness.
// note the TFT was getting random phantom pressess ... seems to be PWM
//interferance with the touchscreen. Need to try  decoupling 5V powerline (inc TFT power)
// from the buzzer and TFT backlight PWM signals.
//
class TFTBacklight
{
private:
    // setting PWM properties
    int tftBacklightPin;
    const int ledChannel = 1;
    const int freq = 3000;
    const int resolution = 8;

public:
    TFTBacklight(int _tftBacklightPin) {
      tftBacklightPin = _tftBacklightPin;
    }

    // The ESP32 pin used to drive the TFT backlight pin
     void Setup() {
        // configure LED PWM functionalitites
        ledcSetup(ledChannel, freq, resolution);
        // attach the channel to the GPIO to be controlled
        ledcAttachPin(tftBacklightPin, ledChannel);
    }

    void SetBacklightBrightness(u_int8_t Brightness){
        ledcWrite(ledChannel, Brightness);
    }
};