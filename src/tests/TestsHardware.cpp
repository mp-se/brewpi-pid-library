/*
MIT License

Copyright (c) 2024 Magnus

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */
#if defined(UNIT_TESTS)

#include <AUnit.h>

#include <ActuatorAutoOff.hpp>
#include <ActuatorDigitalPin.hpp>
#include <ActuatorValue.hpp>
#include <Config.hpp>
#include <DallasTemperature.h>
#include <OneWire.h>
#include <NumberFormats.hpp>
#include <TempSensor.hpp>
#include <TempSensorOneWire.hpp>

test(hardware_digitalPin) {
  DigitalPinActuator cooling(Config::Pins::coolingPin, false);
  DigitalPinActuator heating(Config::Pins::heatingPin, false);

  // Toggle pins to check hardware build
  // for(int i = 0; i < 2; i++) {
  //   cooling.setActive(true);
  //   delay(1000);
  //   cooling.setActive(false);
  //   heating.setActive(true);
  //   delay(1000);
  //   heating.setActive(false);
  //   delay(1000);
  // }

  assertEqual(1, 1);
}

test(hardware_ds18b20) {
  OneWire ow;
  ow.begin(Config::Pins::oneWirePin);
  DallasTemperature dt(&ow);
  dt.begin();
  DeviceAddress da;

  // We should find one sensor or we cannot continue with testing... We need the
  // adress to test Sensor
  int max = dt.getDS18Count();
  Log.info(F("Found %d ds18 sensors" CR), max);

  for(int i = 0; i < max; i++) {
    dt.getAddress(&da[0], i);
    char buf[17];
    printBytes(da, 8, buf);
  
    OneWireTempSensor ows(&ow, da, 0);
    ows.init();
    Log.info(F("Sensor %s, Temp=%F" CR), buf, tempToDouble(ows.read(), 2));
  }

  assertEqual(1, 1);
}

#endif // UNIT_TESTS

// EOF
