#include "Common.h"
#include "Hardware.h"
#include <TeensyThreads.h>
#include <ArduinoQueue.h>

ArduinoQueue<Downlink> packets(20);
Threads::Mutex mtx;
volatile bool sendTelemetry = false;

void radio_loop()
{
  while(1)
  {
    mtx.lock();
    while (!packets.isEmpty())
    {
      Hardware::write_radio(packets.dequeue());
    }
    mtx.unlock();

    String received;
    if (Hardware::read_radio(received))
    {
      for(unsigned int i = 0; i < received.length(); i++)
      {
        switch(received[i])
        {
          case '0':
            mtx.lock();
            if (!Hardware::ready())Hardware::init();
            sendTelemetry = true;
            mtx.unlock();
            break;
          case '1':
            mtx.lock();
            sendTelemetry = false;
            mtx.unlock();
            break;
        }
      }
    }
    delay(100);
  }
}

void setup() {
  // put your setup code here, to run once:
  XBEE_SERIAL.begin(9600);
  std::thread radio(radio_loop);
  radio.detach();
}

void loop() {
  if (!Hardware::ready() || !sendTelemetry)
  {
    delay(500);
    return;
  }
  
  unsigned long start = millis();

  Downlink packet;
  packet.milliseconds = start;
  packet.gps_fix = Hardware::gps_fix();
  Hardware::read_gps(packet.gps_data);
  Hardware::read_sensors(packet.sensor_data);

  //Hardware::write_radio(packet);
  mtx.lock();
  packets.enqueue(packet);
  mtx.unlock();

  if (TELEMETRY_DELAY > (millis() - start))
    delay(TELEMETRY_DELAY - (millis() - start));
}
