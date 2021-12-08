#pragma once
#ifndef __HARDWARE_H__
#define __HARDWARE_H__

#include <Arduino.h>
#include "Common.h"

class Adafruit_BMP3XX;
class Adafruit_MPU6050;
class Adafruit_GPS;
class String;

namespace Hardware
{
  extern Adafruit_BMP3XX bmp;
  extern Adafruit_MPU6050 mpu;
  extern Adafruit_GPS GPS;

  bool ready();
  void init();
  bool gps_fix();
  void read_gps(GPS_Data &data);
  void read_sensors(Sensor_Data &data);

  void write_radio(Downlink data);
  bool read_radio(String &data);
}
#endif
