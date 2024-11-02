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
#include <LittleFS.h>

#include <ControlConstants.hpp>
#include <ControlSettings.hpp>
#include <MinTimes.hpp>
#include <NumberFormats.hpp>
#include <TempControl.hpp>

test(config_controlConstants) {
  // Testing constructor and default values
  ControlConstants cc;
  assertEqual(cc.tempSettingMin, intToTemp(1));
  assertEqual(cc.tempSettingMax, intToTemp(30));
  assertEqual(cc.Kp, intToTempDiff(5));
  assertEqual(cc.Ki, intToTempDiff(1) / 4);
  assertEqual(cc.Kd, intToTempDiff(-3) / 2);
  assertEqual(cc.iMaxError, intToTempDiff(5) / 10);
  assertEqual(cc.idleRangeHigh, intToTempDiff(1));
  assertEqual(cc.idleRangeLow, intToTempDiff(-1));
  assertEqual(cc.heatingTargetUpper, intToTempDiff(3) / 10);
  assertEqual(cc.heatingTargetLower, intToTempDiff(-2) / 10);
  assertEqual(cc.coolingTargetUpper, intToTempDiff(2) / 10);
  assertEqual(cc.coolingTargetLower, intToTempDiff(-3) / 10);
  assertEqual(cc.maxHeatTimeForEstimate, 600);
  assertEqual(cc.maxCoolTimeForEstimate, 1200);
  assertEqual(cc.fridgeFastFilter, 1);
  assertEqual(cc.fridgeSlowFilter, 4);
  assertEqual(cc.fridgeSlopeFilter, 3);
  assertEqual(cc.beerFastFilter, 3);
  assertEqual(cc.beerSlowFilter, 4);
  assertEqual(cc.beerSlopeFilter, 4);
  assertEqual(cc.pidMax, intToTempDiff(10));
  assertEqual(cc.tempFormat, 'C');

  // Testing IO
  LittleFS.remove("/controlConstants.json");
  assertEqual(cc.save(), true);
  cc.tempSettingMin = cc.tempSettingMax = cc.Kp = cc.Ki = cc.Kd = cc.iMaxError =
      cc.idleRangeHigh = cc.idleRangeLow = cc.heatingTargetUpper =
          cc.heatingTargetLower = cc.coolingTargetUpper =
              cc.coolingTargetLower = cc.maxHeatTimeForEstimate =
                  cc.maxCoolTimeForEstimate = cc.fridgeFastFilter =
                      cc.fridgeSlowFilter = cc.fridgeSlopeFilter =
                          cc.beerFastFilter = cc.beerSlowFilter = cc.pidMax = -1;
  cc.tempFormat = ' ';
  assertEqual(LittleFS.exists("/controlConstants.json"), true);
  assertEqual(cc.load(), true);
  assertEqual(cc.tempSettingMin, intToTemp(1));
  assertEqual(cc.tempSettingMax, intToTemp(30));
  assertEqual(cc.Kp, intToTempDiff(5));
  assertEqual(cc.Ki, intToTempDiff(1) / 4);
  assertEqual(cc.Kd, intToTempDiff(-3) / 2);
  assertEqual(cc.iMaxError, intToTempDiff(5) / 10);
  assertEqual(cc.idleRangeHigh, intToTempDiff(1));
  assertEqual(cc.idleRangeLow, intToTempDiff(-1));
  assertEqual(cc.heatingTargetUpper, intToTempDiff(3) / 10);
  assertEqual(cc.heatingTargetLower, intToTempDiff(-2) / 10);
  assertEqual(cc.coolingTargetUpper, intToTempDiff(2) / 10);
  assertEqual(cc.coolingTargetLower, intToTempDiff(-3) / 10);
  assertEqual(cc.maxHeatTimeForEstimate, 600);
  assertEqual(cc.maxCoolTimeForEstimate, 1200);
  assertEqual(cc.fridgeFastFilter, 1);
  assertEqual(cc.fridgeSlowFilter, 4);
  assertEqual(cc.fridgeSlopeFilter, 3);
  assertEqual(cc.beerFastFilter, 3);
  assertEqual(cc.beerSlowFilter, 4);
  assertEqual(cc.beerSlopeFilter, 4);
  assertEqual(cc.pidMax, intToTempDiff(10));
  assertEqual(cc.tempFormat, 'C');
}

test(config_controlSettings) {
  // Testing constructor and default values
  ControlSettings cs;
  assertEqual(cs.beerSetting, intToTemp(20));
  assertEqual(cs.fridgeSetting, intToTemp(20));
  assertEqual(cs.heatEstimator, intToTempDiff(2) / 10);
  assertEqual(cs.coolEstimator, intToTempDiff(5));
  assertEqual(cs.mode, ControllerMode::off);

  // Testing IO
  LittleFS.remove("/controlSettings.json");
  assertEqual(cs.save(), true);
  cs.beerSetting = cs.fridgeSetting = cs.heatEstimator = cs.coolEstimator = 0;
  cs.mode = ' ';
  assertEqual(LittleFS.exists("/controlSettings.json"), true);
  assertEqual(cs.load(), true);
  assertEqual(cs.beerSetting, intToTemp(20));
  assertEqual(cs.fridgeSetting, intToTemp(20));
  assertEqual(cs.heatEstimator, intToTempDiff(2) / 10);
  assertEqual(cs.coolEstimator, intToTempDiff(5));
  assertEqual(cs.mode, ControllerMode::off);
}

test(config_minTimes) {
  // Testing constructor
  MinTimes mt;
  assertEqual(mt.settingsChoice, MIN_TIMES_DEFAULT);
  assertEqual(mt.MIN_COOL_OFF_TIME, 300);
  assertEqual(mt.MIN_HEAT_OFF_TIME, 300);
  assertEqual(mt.MIN_COOL_ON_TIME, 180);
  assertEqual(mt.MIN_HEAT_ON_TIME, 180);
  assertEqual(mt.MIN_COOL_OFF_TIME_FRIDGE_CONSTANT, 600);
  assertEqual(mt.MIN_SWITCH_TIME, 600);
  assertEqual(mt.COOL_PEAK_DETECT_TIME, 1800);
  assertEqual(mt.HEAT_PEAK_DETECT_TIME, 900);

  // Testing setDefault
  mt.MIN_COOL_OFF_TIME = mt.MIN_HEAT_OFF_TIME = mt.MIN_COOL_ON_TIME =
      mt.MIN_HEAT_ON_TIME = mt.MIN_COOL_OFF_TIME_FRIDGE_CONSTANT =
          mt.MIN_SWITCH_TIME = mt.COOL_PEAK_DETECT_TIME =
              mt.HEAT_PEAK_DETECT_TIME = 0;
  mt.setDefaults();
  assertEqual(mt.settingsChoice, MIN_TIMES_DEFAULT);
  assertEqual(mt.MIN_COOL_OFF_TIME, 300);
  assertEqual(mt.MIN_HEAT_OFF_TIME, 300);
  assertEqual(mt.MIN_COOL_ON_TIME, 180);
  assertEqual(mt.MIN_HEAT_ON_TIME, 180);
  assertEqual(mt.MIN_COOL_OFF_TIME_FRIDGE_CONSTANT, 600);
  assertEqual(mt.MIN_SWITCH_TIME, 600);
  assertEqual(mt.COOL_PEAK_DETECT_TIME, 1800);
  assertEqual(mt.HEAT_PEAK_DETECT_TIME, 900);

  // Testing IO
  LittleFS.remove("/customMinTimes.json");
  assertEqual(mt.save(), true);
  assertEqual(LittleFS.exists("/customMinTimes.json"), true);
  mt.settingsChoice = MIN_TIMES_CUSTOM;
  mt.MIN_COOL_OFF_TIME = mt.MIN_HEAT_OFF_TIME = mt.MIN_COOL_ON_TIME =
      mt.MIN_HEAT_ON_TIME = mt.MIN_COOL_OFF_TIME_FRIDGE_CONSTANT =
          mt.MIN_SWITCH_TIME = mt.COOL_PEAK_DETECT_TIME =
              mt.HEAT_PEAK_DETECT_TIME = 0;
  assertEqual(mt.load(), true);
  assertEqual(mt.settingsChoice, MIN_TIMES_DEFAULT);
  assertEqual(mt.MIN_COOL_OFF_TIME, 300);
  assertEqual(mt.MIN_HEAT_OFF_TIME, 300);
  assertEqual(mt.MIN_COOL_ON_TIME, 180);
  assertEqual(mt.MIN_HEAT_ON_TIME, 180);
  assertEqual(mt.MIN_COOL_OFF_TIME_FRIDGE_CONSTANT, 600);
  assertEqual(mt.MIN_SWITCH_TIME, 600);
  assertEqual(mt.COOL_PEAK_DETECT_TIME, 1800);
  assertEqual(mt.HEAT_PEAK_DETECT_TIME, 900);

  // Testing LOW DELAY
  mt.MIN_COOL_OFF_TIME = mt.MIN_HEAT_OFF_TIME = mt.MIN_COOL_ON_TIME =
      mt.MIN_HEAT_ON_TIME = mt.MIN_COOL_OFF_TIME_FRIDGE_CONSTANT =
          mt.MIN_SWITCH_TIME = mt.COOL_PEAK_DETECT_TIME =
              mt.HEAT_PEAK_DETECT_TIME = 0;
  mt.setDefaults(MIN_TIMES_LOW_DELAY);
  assertEqual(mt.settingsChoice, MIN_TIMES_LOW_DELAY);
  assertEqual(mt.MIN_COOL_OFF_TIME, 60);
  assertEqual(mt.MIN_HEAT_OFF_TIME, 300);
  assertEqual(mt.MIN_COOL_ON_TIME, 20);
  assertEqual(mt.MIN_HEAT_ON_TIME, 180);
  assertEqual(mt.MIN_COOL_OFF_TIME_FRIDGE_CONSTANT, 60);
  assertEqual(mt.MIN_SWITCH_TIME, 600);
  assertEqual(mt.COOL_PEAK_DETECT_TIME, 1800);
  assertEqual(mt.HEAT_PEAK_DETECT_TIME, 900);
}

#endif // UNIT_TESTS

// EOF
