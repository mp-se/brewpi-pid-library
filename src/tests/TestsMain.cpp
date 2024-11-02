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
#include <Arduino.h>
#include <LittleFS.h>
#include <log.hpp>

using aunit::Printer;
using aunit::TestRunner;
using aunit::Verbosity;

SerialDebug mySerial;

void setup() {
  Log.info("BrewPi Control Library - Unit Test Build");
  LittleFS.begin(true);
  delay(2000);
  Printer::setPrinter(&Serial);
  TestRunner::setVerbosity(Verbosity::kAll);
  TestRunner::exclude("actuator_*");
  TestRunner::exclude("config_*");
  TestRunner::exclude("sensor_*");
  TestRunner::exclude("control_*");
  // TestRunner::exclude("hardware_*");
}

void loop() {
  TestRunner::run();
  delay(10);
}

/*
  // Boolean
  assertEqual(a, b)
  assertNotEqual(a, b)
  assertLess(a, b)
  assertMore(a, b)
  assertLessOrEqual(a, b)
  assertMoreOrEqual(a, b)

  // String
  assertStringCaseEqual(a, b)
  assertStringCaseNotEqual(a, b)
  assertNear(a, b, error)
  assertNotNear(a, b, error)
  checkTestDone(name)
  checkTestNotDone(name)
  checkTestPass(name)
  checkTestNotPass(name)
  checkTestFail(name)
  checkTestNotFail(name)
  checkTestSkip(name)
  checkTestNotSkip(name)
  checkTestExpire(name) [*]
  checkTestNotExpire(name) [*]
  assertTestDone(name)
  assertTestNotDone(name)
  assertTestPass(name)
  assertTestNotPass(name)
  assertTestFail(name)
  assertTestNotFail(name)
  assertTestSkip(name)
  assertTestNotSkip(name)
  assertTestExpire(name) [*]
  assertTestNotExpire(name) [*]
*/

#endif // UNIT_TESTS

// EOF
