#pragma once
#ifndef __HARDWARE_H__
#define __HARDWARE_H__

#include <Arduino.h>
#include "Common.h"

// We're declaring some classes that we'll use later for the hardware
class Adafruit_BMP3XX;
class Adafruit_MPU6050;
class Adafruit_GPS;
class String;

// We're declaring some global objects of the classes just previously declared, we're also declaring some methods that we're going to be using later,
// along with a few arguments that will be used in some of those methods
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
