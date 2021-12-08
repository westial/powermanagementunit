#include "CppUTest/TestHarness.h"
#include "Sleepable.h"
#include "WakeUp.h"
#include "device/SimpleDeviceSpy.h"
#include "sleepable/SimpleSleepableStub.h"
#include "device/NotSoSimpleDeviceSpy.h"
#include "sleepable/NotSoSimpleSleepableStub.h"

TEST_GROUP(WakeUp){

    void setup() override{
        simple_device_wake_up_counter = 0;
        not_so_simple_device_wake_up_counter = 0;
    }
};

TEST(WakeUp, WakeUpASimpleDevice) {
  Sleepable instance = SimpleSleepable_Create(
      0,
      SimpleDeviceSpy_Sleep,
      SimpleDeviceSpy_WakeUp);
  instance->is_sleeping = 1;
  int result = WakeUp(instance);
  CHECK_EQUAL(1, result);
  CHECK_EQUAL(0, instance->is_sleeping);
  CHECK_EQUAL(1, simple_device_wake_up_counter);
}

TEST(WakeUp, DoNotWakeUpAnAlreadyAwakeDevice) {
  Sleepable instance = SimpleSleepable_Create(
      0,
      SimpleDeviceSpy_Sleep,
      SimpleDeviceSpy_WakeUp);
  int result = WakeUp(instance);
  CHECK_EQUAL(1, result);
  CHECK_EQUAL(0, simple_device_wake_up_counter);
}

TEST(WakeUp, WakeUpANotSoSimpleDevice) {
  char input[] = "what's up!";
  Sleepable instance = NotSoSimpleSleepable_Create(
      100,
      NotSoSimpleDeviceSpy_Sleep,
      NotSoSimpleDeviceSpy_WakeUp,
      input,
      sizeof(input));
  instance->is_sleeping = 1;
  int result = WakeUp(instance);
  CHECK_EQUAL(1, result);
  CHECK_EQUAL(0, instance->is_sleeping);
  CHECK_EQUAL(1, not_so_simple_device_wake_up_counter);
}