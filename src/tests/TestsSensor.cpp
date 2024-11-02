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
#include <DallasTemperature.h>
#include <OneWire.h>

#include <Config.hpp>
#include <NumberFormats.hpp>
#include <TempSensor.hpp>
#include <TempSensorBasic.hpp>
#include <TempSensorDisconnected.hpp>
#include <TempSensorOneWire.hpp>

test(sensor_basic) {
  TempSensor t(TEMP_SENSOR_TYPE_FRIDGE);

  assertEqual(t.hasSlowFilter(), true);
  assertEqual(t.hasFastFilter(), true);
  assertEqual(t.hasSlopeFilter(), true);
  assertEqual(t.isConnected(), false);
}

test(sensor_disconnected) {
  DisconnectedTempSensor dt;

  assertEqual(dt.isConnected(), false);
  assertEqual(dt.init(), false);
  assertEqual(dt.read(), TEMP_SENSOR_DISCONNECTED);
}

test(sensor_onewire) {
  OneWire ow;
  ow.begin(Config::Pins::oneWirePin);
  DallasTemperature dt(&ow);
  dt.begin();
  DeviceAddress da;

  // We should find one sensor or we cannot continue with testing... We need the
  // adress to test Sensor
  assertEqual(dt.getDS18Count(), 1);
  dt.getAddress(&da[0], 0);

  char buf[17];
  printBytes(da, 8, buf);
  // Serial.println(buf);

  OneWireTempSensor ows(&ow, da, 0);
  assertEqual(ows.init(), true);
  assertEqual(ows.isConnected(), true);
  assertNotEqual(tempToDouble(ows.read(), 2), -10.1);
}

#endif // UNIT_TESTS

// EOF
