
#ifndef _SEATALK_H
#define _SEATALK_H

#include <Arduino.h>
#include <SoftwareSerial.h>

// The queue sitting between the read seatalk task and the html webserver (called by client to get ST data for display)
extern QueueHandle_t queue;

// Seatalk param declarations
extern float rsa, stw, sog, xte, aws, dpt, dtw, vlw;    // rudder angle, speed through water, speed over ground, cross track error
                                                 // apparent wind speed, depth, dist to waypt, trip distance
extern uint16_t hdg, cts, cog, awa, btw;    // heading, course to steer, course over ground, apparent wind angle, bearing to waypt
extern uint8_t apMode;                      // autopilot mode
extern bool xteValid, btwValid;             // cross track error valid
extern int wts;                             // wind angle to steer
extern int dir;                             // direction to steer
extern uint8_t apAlarm;
extern uint8_t newCmd;

extern SoftwareSerial mySerial;

void Seatalk_Init(); 

#endif // end _SEATALK_H