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
#if !defined(UNIT_TESTS)

#include <Arduino.h>
#include <DallasTemperature.h>
#include <LittleFS.h>
#include <OneWire.h>

#include <ActuatorDigitalPin.hpp>
#include <Config.hpp>
#include <NumberFormats.hpp>
#include <TempControl.hpp>
#include <TempSensorOneWire.hpp>
#include <looptimer.hpp>

SerialDebug mySerial;
LoopTimer loopTimer(3000);
OneWire oneWire;

DigitalPinActuator *actuatorCooling;
DigitalPinActuator *actuatorHeating;
OneWireTempSensor *oneWireFridge;
OneWireTempSensor *oneWireBeer;
TempSensor *fridgeSensor;
TempSensor *beerSensor;

void setup() {
  Log.notice(F("BrewPi Control Library - Example" CR));
  LittleFS.begin(true);
  delay(2000);

  // Initialize temp controller with default values
  tempControl.init(MIN_TIMES_DEFAULT);

  oneWire.begin(Config::Pins::oneWirePin);
  DallasTemperature tempSensor(&oneWire);
  tempSensor.begin();

  for (int i = 0; i < tempSensor.getDS18Count(); i++) {
    char buf[17];
    DeviceAddress da;
    tempSensor.getAddress(&da[0], i);
    printBytes(da, 8, buf);
    Log.info(F("BREW: Found DS18B20 sensor at %s" CR), buf);
  }

  // Create the temperature sensors
  DeviceAddress daFridge, daBeer;
  parseBytes(daFridge, "28A35179972103CD",
             sizeof(daFridge));
  oneWireFridge = new OneWireTempSensor(&oneWire, daFridge, 0);
  fridgeSensor = new TempSensor(TEMP_SENSOR_TYPE_FRIDGE, oneWireFridge);
  fridgeSensor->init();
  tempControl.setFridgeSensor(fridgeSensor);

  parseBytes(daBeer, "2817557997210309", sizeof(daBeer));  
  oneWireBeer = new OneWireTempSensor(&oneWire, daBeer, 0);
  beerSensor = new TempSensor(TEMP_SENSOR_TYPE_BEER, oneWireBeer);
  beerSensor->init();
  tempControl.setBeerSensor(beerSensor);

  // Create the actuators
  actuatorCooling = new DigitalPinActuator(Config::Pins::coolingPin, false);
  actuatorHeating = new DigitalPinActuator(Config::Pins::heatingPin, false);

  tempControl.setCoolingActuator(actuatorCooling);
  tempControl.setHeatingActuator(actuatorHeating);

  tempControl.setMode(ControllerMode::fridgeConstant);
  tempControl.setFridgeTargetTemperature(10.1);
}

void loop() {
  if (loopTimer.hasExipred()) {
    loopTimer.reset();
    const char *stateBefore = tempControl.getStateAsString();

    tempControl.loop();

    const char *stateAfter = tempControl.getStateAsString();
    double fridgeTemp = tempControl.getFridgeTemperature();
    double beerTemp = tempControl.getFridgeTemperature();
    char mode = tempControl.getMode();
    int waitTime = tempControl.getWaitTime();

    Log.notice(F("BREW: Mode=%c, State=%s->%s, WaitTime=%d, FridgeTemp=%F, "
                 "BeerTemp=%F" CR),
               mode, stateBefore, stateAfter, waitTime, fridgeTemp, beerTemp);
  }
}

#endif  // UNIT_TESTS

// EOF
