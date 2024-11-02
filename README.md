# BrewPI Library

An library containing the BrewPi PID controller for ESP8266, ESP32. This project is based on BrewPi / BrewPi-esp2866 projects on github. I needed a PID controller for one of my projects and since I have been using brewpi-esp8266 for many years I know its a stable and reliable PID controller. 

* https://github.com/BrewPi/firmware
* https://github.com/thorrak/brewpi-esp8266

This is only contains the core classes of the BrewPi project, I have stripped down the code to the bare minium to contain the Actuators, Sensors and Controller for managing one chamber with 2 Sensors and Cooler & Heater control. 

I have done quite a lot of refactoring of the code to ensure that the interface for the Controller is simple as well as adding some unit tests for the supporting classes.

## Main Classes

These are the main classes in this library:

* **ActuatorDigitalPin**; Controls an output pin.
* **ActuatorValue**; Default actuator when not used.
* **ActuatorAutoOff**; Turns of another actuator when time expires.

* **TempSensorOneWire**: For DS18B20 sensor
* **TempSensorDisconnected**; For unused sensor.

* **TempControl**; Main PID controller

Other classes are supporting the PID controller.

## Example code

Initialize temp controller with default values for timers

```  
tempControl.init(MIN_TIMES_DEFAULT);
```  

Code to show what senors are attached to OneWire bus

```  
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
```  

Attach a fridge temp sensor to controller, change the ID's that match your sensors.

```  
DeviceAddress daFridge, daBeer;
parseBytes(daFridge, "28A35179972103CD", sizeof(daFridge)); 
oneWireFridge = new OneWireTempSensor(&oneWire, daFridge, 0);
fridgeSensor = new TempSensor(TEMP_SENSOR_TYPE_FRIDGE, oneWireFridge);
fridgeSensor->init();
tempControl.setFridgeSensor(fridgeSensor);

parseBytes(daBeer, "2817557997210309", sizeof(daBeer));  // Wokwi sensor
oneWireBeer = new OneWireTempSensor(&oneWire, daBeer, 0);
beerSensor = new TempSensor(TEMP_SENSOR_TYPE_BEER, oneWireBeer);
beerSensor->init();
tempControl.setBeerSensor(beerSensor);
```  

Create pin actuators and attach to controller

```  
actuatorCooling = new DigitalPinActuator(Config::Pins::coolingPin, false);
actuatorHeating = new DigitalPinActuator(Config::Pins::heatingPin, false);

tempControl.setCoolActuator(actuatorCooling);
tempControl.setHeatActuator(actuatorHeating);
```  

Set mode and target temperature

```  
tempControl.setMode(ControllerMode::fridgeConstant);
tempControl.setFridgeTargetTemperature(10.1);
```  

Loop code and examples on how to read state from the controller

```  
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
```  
