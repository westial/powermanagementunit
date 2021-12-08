#include "CppUTest/TestHarness.h"
#include "PowerMU.h"
#include "device/SimpleDeviceSpy.h"
#include "powermu/GetLevelStub.h"
#include "sleepable/SimpleSleepableStub.h"

PowerMU pmu;

TEST_GROUP(Balance){

    void setup() override{
        PercentRange range = Percent_Create(0, 100);
pmu = PowerMU_Create((const void *) get_stub_level_percentage, &range);
}

void teardown() override {
  PowerMU_Destroy(&pmu);
}
}
;

TEST(Balance, EmptySleepableBusError) {
  stub_level_percentage = 5;
  int result = PowerMU_Balance(&pmu);
  CHECK_EQUAL(-1, result);
}

TEST(Balance, RegisterADevice) {
  stub_level_percentage = 100;
  Sleepable device = nullptr;
  int added = PowerMU_Register(&pmu, device);
  CHECK_EQUAL(1, added);
  CHECK_EQUAL(1, pmu.sleepables.length);
}

TEST(Balance, NoBalanceDueToAGoodPowerLevel) {
  stub_level_percentage = 65;
  Sleepable device = SimpleSleepable_Create(
      50,
      SimpleDeviceSpy_Sleep,
      SimpleDeviceSpy_WakeUp);
  PowerMU_Register(&pmu, device);
  int result = PowerMU_Balance(&pmu);
  CHECK_EQUAL(0, result);
}

TEST(Balance, MakeADeviceSleep) {
  stub_level_percentage = 31;
  Sleepable device = SimpleSleepable_Create(
      50,
      SimpleDeviceSpy_Sleep,
      SimpleDeviceSpy_WakeUp);
  PowerMU_Register(&pmu, device);
  int result = PowerMU_Balance(&pmu);
  CHECK_EQUAL(1, result);
}

TEST(Balance, MakeTwoDevicesSleep) {
  stub_level_percentage = 31;
  Sleepable device1 = SimpleSleepable_Create(
      50,
      SimpleDeviceSpy_Sleep,
      SimpleDeviceSpy_WakeUp);
  Sleepable device2 = SimpleSleepable_Create(
      50,
      SimpleDeviceSpy_Sleep,
      SimpleDeviceSpy_WakeUp);
  PowerMU_Register(&pmu, device1);
  PowerMU_Register(&pmu, device2);
  int result = PowerMU_Balance(&pmu);
  CHECK_EQUAL(2, result);
}

TEST(Balance, MakeTwoDevicesSleepOfThree) {
  stub_level_percentage = 31;
  Sleepable device1 = SimpleSleepable_Create(
      50,
      SimpleDeviceSpy_Sleep,
      SimpleDeviceSpy_WakeUp);
  Sleepable device2 = SimpleSleepable_Create(
      50,
      SimpleDeviceSpy_Sleep,
      SimpleDeviceSpy_WakeUp);
  Sleepable device3 = SimpleSleepable_Create(
      30,
      SimpleDeviceSpy_Sleep,
      SimpleDeviceSpy_WakeUp);
  PowerMU_Register(&pmu, device1);
  PowerMU_Register(&pmu, device2);
  PowerMU_Register(&pmu, device3);
  int result = PowerMU_Balance(&pmu);
  CHECK_EQUAL(2, result);
}
