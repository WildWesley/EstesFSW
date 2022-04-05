#pragma once
#ifndef __COMMON_H__
#define __COMMON_H__

#include <Arduino.h>
#define XBEE_SERIAL Serial1

// We're setting the delay between each telemetry pull in ms, the pin to be used for the voltage connection, the pin to be used for the gps, and the sea level altitude for calculations
// of flight altitude.
const unsigned long TELEMETRY_DELAY = 500;
const byte VOLTAGE_PIN = 14;
const byte GPS_FIX_PIN = 12;
const float SEA_LEVEL = 1014.6f;

// Declaring all the variables that we want to retrieve from the GPS
struct GPS_Data // 13 bytes
{
  float latitude; // 4 bytes
  float longitude; // 4 bytes
  float altitude; // 4 bytes
  byte sats; // 1 byte
};

// Declaring all of the variables that we want to pull from all of our sensors
struct Sensor_Data // 36 bytes
{
  float vbat; // 4 bytes
  float altitude; // 4 bytes
  float temperature; // 4 bytes
  float gyro[3]; // 12 bytes
  float acceleration[3]; // 12 bytes
};

// We're creating our objects from our aforementioned classes, while also declaring two new variables:
//  - milliseconds will keep the mission time
//  - gps_fix will say whether or not the GPS can come up with a position from the satellites detected
struct Downlink // 54 bytes
{
  unsigned long milliseconds; //4 bytes
  bool gps_fix; //1 byte 
  GPS_Data gps_data; // 13 bytes 
  Sensor_Data sensor_data; // 36 bytes
};
#endif
