#include "SleepableBus.h"
#include "CppUTest/TestHarness.h"
#include "Sleepable.h"

TEST_GROUP(SleepableBus){

    void setup() override{
    }
};

TEST(SleepableBus, AddASleepable) {
  SleepableBus bus = Sleepable_Create(10);
  Sleepable device = nullptr;
  int result = SleepableBus_Add(&bus, device);
  CHECK_EQUAL(1, result);
  CHECK_EQUAL(1, SleepableBus_Length(&bus));
}

TEST(SleepableBus, AddMultipleSleepable) {
  SleepableBus bus = Sleepable_Create(10);
  SleepableStruct example = {
      .vtable = nullptr,
      .power_threshold = 100,
      .is_sleeping = 0
  };
  Sleepable device1 = nullptr;
  Sleepable device2 = &example;
  Sleepable device3 = nullptr;
  int result = SleepableBus_Add(&bus, device1);
  CHECK_EQUAL(1, result);
  result = SleepableBus_Add(&bus, device2);
  CHECK_EQUAL(1, result);
  result = SleepableBus_Add(&bus, device3);
  CHECK_EQUAL(1, result);
  CHECK_EQUAL(3, SleepableBus_Length(&bus));
  CHECK_EQUAL(device2, SleepableBus_Get(&bus, 1));
  CHECK_FALSE(device2 == SleepableBus_Get(&bus, 0));
  CHECK_FALSE(device2 == SleepableBus_Get(&bus, 2));
}

TEST(SleepableBus, DoNotAllowTrespassingMaximumLength) {
  SleepableBus bus = Sleepable_Create(3);
  Sleepable device1 = nullptr;
  Sleepable device2 = nullptr;
  Sleepable device3 = nullptr;
  Sleepable device4 = nullptr;
  int result = SleepableBus_Add(&bus, device1);
  CHECK_EQUAL(1, result);
  result = SleepableBus_Add(&bus, device2);
  CHECK_EQUAL(1, result);
  result = SleepableBus_Add(&bus, device3);
  CHECK_EQUAL(1, result);
  result = SleepableBus_Add(&bus, device4);
  CHECK_EQUAL(0, result);
  CHECK_EQUAL(3, SleepableBus_Length(&bus));
}

TEST(SleepableBus, UnlinkSleepables) {
  SleepableBus bus = Sleepable_Create(1);
  Sleepable device = nullptr;
  SleepableBus_Add(&bus, device);
  SleepableBus_Destroy(&bus);
  CHECK_EQUAL(0, SleepableBus_Length(&bus));
}

TEST(SleepableBus, ReturnFalseOnGettingADeviceOutOfBounds) {
  SleepableBus bus = Sleepable_Create(1);
  Sleepable device1 = nullptr;
  Sleepable device2 = nullptr;
  SleepableBus_Add(&bus, device1);
  SleepableBus_Add(&bus, device2);
  Sleepable result = SleepableBus_Get(&bus, 2);
  CHECK_EQUAL(0, result);
}