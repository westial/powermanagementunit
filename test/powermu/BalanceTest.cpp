#include "CppUTest/TestHarness.h"
#include "PowerMU.h"
#include "device/SimpleDeviceSpy.h"
#include "powermu/GetLevelStub.h"
#include "sleepable/FailingSimpleSleepableStub.h"
#include "sleepable/SimpleSleepableStub.h"
#include "sleepable/AlreadyOffSimpleSleepableStub.h"

int count_asleep(SleepableBus *bus);
int count_awake(SleepableBus *bus);

int count_asleep(SleepableBus *bus) {
  unsigned int index;
  int asleep_count = 0;
  for (index = 0; index < SleepableBus_Length(bus); index++) {
    asleep_count += SleepableBus_Get(bus, index)->is_sleeping ? 1 : 0;
  }
  return asleep_count;
}

int count_awake(SleepableBus *bus) {
  unsigned int index;
  int awake_count = 0;
  for (index = 0; index < SleepableBus_Length(bus); index++) {
    awake_count += SleepableBus_Get(bus, index)->is_sleeping ? 0 : 1;
  }
  return awake_count;
}

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
  PowerReport result = PowerMU_Balance(&pmu);
  CHECK_EQUAL(-1, result.error);
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
  PowerReport result = PowerMU_Balance(&pmu);
  CHECK_EQUAL(0, result.asleep);
  CHECK_EQUAL(0, result.error);
}

TEST(Balance, MakeADeviceSleep) {
  stub_level_percentage = 31;
  Sleepable device = SimpleSleepable_Create(
      50,
      SimpleDeviceSpy_Sleep,
      SimpleDeviceSpy_WakeUp);
  PowerMU_Register(&pmu, device);
  PowerReport result = PowerMU_Balance(&pmu);
  CHECK_EQUAL(1, result.asleep);
}

TEST(Balance, ErrorOnMakingADeviceSleep) {
  stub_level_percentage = 31;
  Sleepable device = FailingSimpleSleepable_Create(
      50,
      SimpleDeviceSpy_Sleep,
      SimpleDeviceSpy_WakeUp);
  PowerMU_Register(&pmu, device);
  PowerReport result = PowerMU_Balance(&pmu);
  CHECK_EQUAL(1, result.error);
  CHECK_EQUAL(0, result.asleep);
  CHECK_EQUAL(0, result.awake);
}

TEST(Balance, WakeUpADevice) {
  stub_level_percentage = 55;
  Sleepable device = SimpleSleepable_Create(
      50,
      SimpleDeviceSpy_Sleep,
      SimpleDeviceSpy_WakeUp);
  PowerMU_Register(&pmu, device);
  device->is_sleeping = 1;
  PowerReport result = PowerMU_Balance(&pmu);
  CHECK_EQUAL(0, result.asleep);
  CHECK_EQUAL(1, result.awake);
  int sleeping = count_asleep(&pmu.sleepables);
  CHECK_EQUAL(0, sleeping);
}

TEST(Balance, ErrorOnWakingUpADevice) {
  stub_level_percentage = 60;
  Sleepable device = FailingSimpleSleepable_Create(
      50,
      SimpleDeviceSpy_Sleep,
      SimpleDeviceSpy_WakeUp);
  PowerMU_Register(&pmu, device);
  device->is_sleeping = 1;
  PowerReport result = PowerMU_Balance(&pmu);
  CHECK_EQUAL(1, result.error);
  CHECK_EQUAL(0, result.asleep);
  CHECK_EQUAL(0, result.awake);
}

TEST(Balance, MakeSleepAndThenWakeUpADevice) {
  stub_level_percentage = 31;
  Sleepable device = SimpleSleepable_Create(
      50,
      SimpleDeviceSpy_Sleep,
      SimpleDeviceSpy_WakeUp);
  PowerMU_Register(&pmu, device);
  device->is_sleeping = 1;
  PowerReport result = PowerMU_Balance(&pmu);
  CHECK_EQUAL(1, result.asleep);
  CHECK_EQUAL(0, result.awake);
  stub_level_percentage = 55;
  result = PowerMU_Balance(&pmu);
  CHECK_EQUAL(0, result.asleep);
  CHECK_EQUAL(1, result.awake);
  int absolute_asleep = count_asleep(&pmu.sleepables);
  int absolute_awake = count_awake(&pmu.sleepables);
  CHECK_EQUAL(absolute_asleep, result.asleep);
  CHECK_EQUAL(absolute_awake, result.awake);
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
  PowerReport result = PowerMU_Balance(&pmu);
  CHECK_EQUAL(2, result.asleep);
  CHECK_EQUAL(0, result.awake);
  int absolute_asleep = count_asleep(&pmu.sleepables);
  int absolute_awake = count_awake(&pmu.sleepables);
  CHECK_EQUAL(absolute_asleep, result.asleep);
  CHECK_EQUAL(absolute_awake, result.awake);
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
  PowerReport result = PowerMU_Balance(&pmu);
  int absolute_asleep = count_asleep(&pmu.sleepables);
  int absolute_awake = count_awake(&pmu.sleepables);
  CHECK_EQUAL(2, absolute_asleep);
  CHECK_EQUAL(1, absolute_awake);
  CHECK_EQUAL(2, result.asleep);
  CHECK_EQUAL(1, result.awake);
}

TEST(Balance, MakeOneDeviceSleepAndFailAnother) {
  stub_level_percentage = 31;
  Sleepable device1 = SimpleSleepable_Create(
      50,
      SimpleDeviceSpy_Sleep,
      SimpleDeviceSpy_WakeUp);
  Sleepable device2 = FailingSimpleSleepable_Create(
      50,
      SimpleDeviceSpy_Sleep,
      SimpleDeviceSpy_WakeUp);
  PowerMU_Register(&pmu, device1);
  PowerMU_Register(&pmu, device2);
  PowerReport result = PowerMU_Balance(&pmu);
  CHECK_EQUAL(1, result.asleep);
  int absolute_asleep = count_asleep(&pmu.sleepables);
  CHECK_EQUAL(absolute_asleep, result.asleep);
  CHECK_EQUAL(1, result.error);
}

TEST(Balance, WakeUpOneDeviceAndFailAnother) {
  stub_level_percentage = 75;
  Sleepable device1 = AlreadyOffSimpleSleepable_Create(
      50,
      SimpleDeviceSpy_Sleep,
      SimpleDeviceSpy_WakeUp);
  Sleepable device2 = FailingSimpleSleepable_Create(
      50,
      SimpleDeviceSpy_Sleep,
      SimpleDeviceSpy_WakeUp);
  PowerMU_Register(&pmu, device1);
  PowerMU_Register(&pmu, device2);
  device2->is_sleeping = 1;
  PowerReport result = PowerMU_Balance(&pmu);
  CHECK_EQUAL(1, result.awake);
  int absolute_awake = count_awake(&pmu.sleepables);
  CHECK_EQUAL(absolute_awake, result.awake);
  CHECK_EQUAL(1, result.error);
}

TEST(Balance, WakeUpOneDeviceFailWakingUpAnotherMakeAnotherSleepAndFailTheLastSleep) {
  stub_level_percentage = 31;
  Sleepable device1 = SimpleSleepable_Create(
      50,
      SimpleDeviceSpy_Sleep,
      SimpleDeviceSpy_WakeUp);
  Sleepable device2 = FailingSimpleSleepable_Create(
      50,
      SimpleDeviceSpy_Sleep,
      SimpleDeviceSpy_WakeUp);
  Sleepable device3 = SimpleSleepable_Create(
      30,
      SimpleDeviceSpy_Sleep,
      SimpleDeviceSpy_WakeUp);
  Sleepable device4 = FailingSimpleSleepable_Create(
      30,
      SimpleDeviceSpy_Sleep,
      SimpleDeviceSpy_WakeUp);
  PowerMU_Register(&pmu, device1);
  PowerMU_Register(&pmu, device2);
  PowerMU_Register(&pmu, device3);
  PowerMU_Register(&pmu, device4);
  device3->is_sleeping = 1;
  device4->is_sleeping = 1;
  PowerReport result = PowerMU_Balance(&pmu);
  int absolute_asleep = count_asleep(&pmu.sleepables);
  int absolute_awake = count_awake(&pmu.sleepables);
  CHECK_EQUAL(2, absolute_asleep);
  CHECK_EQUAL(2, absolute_awake);
  CHECK_EQUAL(absolute_asleep - 1, result.asleep);
  CHECK_EQUAL(absolute_awake - 1, result.awake);
  CHECK_EQUAL(2, result.error);
  CHECK_EQUAL(
      absolute_asleep + absolute_awake,
      result.asleep + result.awake + result.error
      );
}
