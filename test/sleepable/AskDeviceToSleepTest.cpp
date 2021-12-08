#include "AskToSleep.h"
#include "CppUTest/TestHarness.h"
#include "Sleepable.h"
#include "device/NotSoSimpleDeviceSpy.h"
#include "device/SimpleDeviceSpy.h"
#include "sleepable/AlreadyOffSimpleSleepableStub.h"
#include "sleepable/NotSoSimpleSleepableStub.h"
#include "sleepable/SimpleSleepableStub.h"
#include "sleepable/FailingSimpleSleepableStub.h"

TEST_GROUP(AskToSleep){

    void setup() override{
        simple_device_sleep_counter = 0;
        not_so_simple_device_sleep_counter = 0;
    }
};

TEST(AskToSleep, BypassPowerCheck) {
  Sleepable instance = SimpleSleepable_Create(
      0,
      SimpleDeviceSpy_Sleep,
      SimpleDeviceSpy_WakeUp);
  CHECK_FALSE(AskToSleep(instance, 0));
  CHECK_FALSE(AskToSleep(instance, 50));
  CHECK_FALSE(AskToSleep(instance, 100));
  CHECK_EQUAL(0, instance->is_sleeping);
}

TEST(AskToSleep, ReturnNoNeedToSleep) {
  Sleepable instance = SimpleSleepable_Create(
      50,
      SimpleDeviceSpy_Sleep,
      SimpleDeviceSpy_WakeUp);
  CHECK_FALSE(AskToSleep(instance, 50));
  CHECK_FALSE(AskToSleep(instance, 51));
  CHECK_EQUAL(0, instance->is_sleeping);
}

TEST(AskToSleep, MakeSimpleDeviceSleep) {
  Sleepable instance = SimpleSleepable_Create(
      100,
      SimpleDeviceSpy_Sleep,
      SimpleDeviceSpy_WakeUp);
  CHECK_TRUE(AskToSleep(instance, 99));
  CHECK_EQUAL(1, simple_device_sleep_counter);
}

TEST(AskToSleep, MakeSleepADeviceWitATwoArgsAndReturningAValueCallback) {
  char input[] = "what's up!";
  Sleepable instance = NotSoSimpleSleepable_Create(
      100,
      NotSoSimpleDeviceSpy_Sleep,
      NotSoSimpleDeviceSpy_WakeUp,
      input,
      sizeof(input));
  int result = AskToSleep(instance, 99);
  CHECK_TRUE(result);
  CHECK_EQUAL(1, not_so_simple_device_sleep_counter);
  STRCMP_EQUAL("what's up!", not_so_simple_device_content_param_spy);
  CHECK_EQUAL(1, instance->is_sleeping);
}

TEST(AskToSleep, MakeSleepTwoDevicesWitATwoArgsAndReturningAValueCallback) {
  char input1[] = "what's up with her!";
  char input2[] = "what's up with him!";
  Sleepable instance1 = NotSoSimpleSleepable_Create(
      80,
      NotSoSimpleDeviceSpy_Sleep,
      NotSoSimpleDeviceSpy_WakeUp,
      input1,
      sizeof(input1));
  Sleepable instance2 = NotSoSimpleSleepable_Create(
      80,
      NotSoSimpleDeviceSpy_Sleep,
      NotSoSimpleDeviceSpy_WakeUp,
      input2,
      sizeof(input2));
  CHECK_TRUE(AskToSleep(instance1, 79));
  CHECK_EQUAL(1, instance1->is_sleeping);
  CHECK_EQUAL(1, not_so_simple_device_sleep_counter);
  STRCMP_EQUAL("what's up with her!", not_so_simple_device_content_param_spy);
  CHECK_TRUE(AskToSleep(instance2, 79));
  CHECK_EQUAL(1, instance2->is_sleeping);
  CHECK_EQUAL(2, not_so_simple_device_sleep_counter);
  STRCMP_EQUAL("what's up with him!", not_so_simple_device_content_param_spy);
  CHECK_FALSE(AskToSleep(instance1, 99));
  CHECK_EQUAL(2, not_so_simple_device_sleep_counter);
  STRCMP_EQUAL("what's up with him!", not_so_simple_device_content_param_spy);
}

TEST(AskToSleep, DoNotMakeItSleepIfItIsAlreadySleeping) {
  Sleepable instance = AlreadyOffSimpleSleepable_Create(50, SimpleDeviceSpy_Sleep);
  int result = AskToSleep(instance, 10);
  CHECK_TRUE(result);
  CHECK_EQUAL(0, simple_device_sleep_counter);
  CHECK_EQUAL(1, instance->is_sleeping);
}

TEST(AskToSleep, ErrorOnMakingADeviceSleep) {
  Sleepable instance = FailingSimpleSleepable_Create(50, SimpleDeviceSpy_Sleep);
  int result = AskToSleep(instance, 10);
  CHECK_EQUAL(-1, result);
  CHECK_EQUAL(0, instance->is_sleeping);
}