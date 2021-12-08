#include "CppUTest/TestHarness.h"
#include "PowerMU.h"
#include "powermu/GetLevelStub.h"
#include <device/SimpleDeviceSpy.h>
#include <sleepable/SimpleSleepableStub.h>

TEST_GROUP(Balance){

    void setup() override{

    }

    void teardown() override{}};

TEST(Balance, EmptySleepableBusError) {
  stub_level_percentage = 5;
  PercentRange range = Percent_Create(0, 100);
  PowerMU pmu = PowerMU_Create((const void *) get_stub_level_percentage, &range);
  int result = PowerMU_Balance(&pmu);
  CHECK_EQUAL(-1, result);
}

TEST(Balance, RegisterADevice) {
  stub_level_percentage = 100;
  PercentRange range = Percent_Create(0, 100);
  PowerMU pmu = PowerMU_Create((const void *) get_stub_level_percentage, &range);
  Sleepable device = nullptr;
  int added = PowerMU_Register(&pmu, device);
  CHECK_EQUAL(1, added);
  CHECK_EQUAL(1, pmu.sleepables.length);
}

TEST(Balance, NoBalanceDueToAGoodPowerLevel) {
  stub_level_percentage = 65;
  PercentRange range = Percent_Create(0, 100);
  PowerMU pmu = PowerMU_Create((const void *) get_stub_level_percentage, &range);
  Sleepable device = SimpleSleepable_Create(50, SimpleDeviceSpy_Sleep);
  PowerMU_Register(&pmu, device);
  int result = PowerMU_Balance(&pmu);
  CHECK_EQUAL(0, result);
}

TEST(Balance, MakeADeviceSleep) {
  stub_level_percentage = 31;
  PercentRange range = Percent_Create(0, 100);
  PowerMU pmu = PowerMU_Create((const void *) get_stub_level_percentage, &range);
  Sleepable device = SimpleSleepable_Create(50, SimpleDeviceSpy_Sleep);
  PowerMU_Register(&pmu, device);
  int result = PowerMU_Balance(&pmu);
  CHECK_EQUAL(1, result);
}
