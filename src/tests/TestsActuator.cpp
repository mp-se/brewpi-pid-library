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

test(actuator_digitalPin) {
  DigitalPinActuator actPin(Config::Pins::coolingPin, false);

  assertEqual(actPin.isActive(), false);
  actPin.setActive(true);
  assertEqual(actPin.isActive(), true);

  DigitalPinActuator actPin2(Config::Pins::heatingPin, true);
}

test(actuator_autoOff) {
  DigitalPinActuator actPin(26, false);
  AutoOffActuator actTimer(2, &actPin);

  assertEqual(actPin.isActive(), false);
  assertEqual(actTimer.isActive(), false);

  actTimer.setActive(true);
  assertEqual(actPin.isActive(), true);
  assertEqual(actTimer.isActive(), true);

  while (actTimer.isActive()) {
    actTimer.update();
  }

  assertEqual(actPin.isActive(), false);
  assertEqual(actTimer.isActive(), false);
}

test(actuator_value) {
  ValueActuator actValue;
  assertEqual(actValue.isActive(), false);

  actValue.setActive(true);
  assertEqual(actValue.isActive(), true);

  ValueActuator actValue2(true);
  assertEqual(actValue2.isActive(), true);

  actValue2.setActive(true);
  assertEqual(actValue2.isActive(), true);
}

#endif // UNIT_TESTS

// EOF
