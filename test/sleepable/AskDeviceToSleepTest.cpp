#include "AskToSleep.h"
#include "CppUTest/TestHarness.h"
#include "Sleepable.h"
#include "device/SimpleDeviceSpy.h"
#include "sleepable/SimpleSleepableStub.h"
#include <device/NotSoSimpleDeviceSpy.h>
#include "sleepable/NotSoSimpleSleepableStub.h"

int simple_device_sleep_counter;
int not_so_simple_device_sleep_counter;
char not_so_simple_device_content_param_spy[INPUT_LENGTH];

TEST_GROUP(AskToSleep){

    void setup() override{
        simple_device_sleep_counter = 0;
        SimpleSleepable_InstallInterface();
        not_so_simple_device_sleep_counter = 0;
        NotSoSimpleSleepable_InstallInterface();
    }
};

TEST(AskToSleep, BypassPowerCheck) {
  Sleepable instance = SimpleSleepable_Create(0, SimpleDeviceSpy_Sleep);
  CHECK_FALSE(AskToSleep(instance, 0));
  CHECK_FALSE(AskToSleep(instance, 50));
  CHECK_FALSE(AskToSleep(instance, 100));
}

TEST(AskToSleep, ReturnNoNeedToSleep) {
  Sleepable instance = SimpleSleepable_Create(50, SimpleDeviceSpy_Sleep);
  CHECK_FALSE(AskToSleep(instance, 50));
  CHECK_FALSE(AskToSleep(instance, 51));
}

TEST(AskToSleep, MakeSimpleDeviceSleep) {
  Sleepable instance = SimpleSleepable_Create(100, SimpleDeviceSpy_Sleep);
  CHECK_TRUE(AskToSleep(instance, 99));
  CHECK_EQUAL(1, simple_device_sleep_counter);
}

TEST(AskToSleep, MakeSleepADeviceWitATwoArgsAndReturningAValueCallback) {
  char input[] = "what's up!";
  Sleepable instance = NotSoSimpleSleepable_Create(
      100,
      NotSoSimpleDeviceSpy_Sleep,
      input,
      sizeof(input)
      );
  int result = AskToSleep(instance, 99);
  CHECK_TRUE(result);
  CHECK_EQUAL(1, not_so_simple_device_sleep_counter);
  STRCMP_EQUAL("what's up!", not_so_simple_device_content_param_spy);
}

TEST(AskToSleep, MakeSleepTwoDevicesWitATwoArgsAndReturningAValueCallback) {
  char input1[] = "what's up with her!";
  char input2[] = "what's up with him!";
  Sleepable instance1 = NotSoSimpleSleepable_Create(
      80,
      NotSoSimpleDeviceSpy_Sleep,
      input1,
      sizeof(input1)
      );
  Sleepable instance2 = NotSoSimpleSleepable_Create(
      80,
      NotSoSimpleDeviceSpy_Sleep,
      input2,
      sizeof(input2)
      );
  CHECK_TRUE(AskToSleep(instance1, 79));
  CHECK_EQUAL(1, not_so_simple_device_sleep_counter);
  STRCMP_EQUAL("what's up with her!", not_so_simple_device_content_param_spy);
  CHECK_TRUE(AskToSleep(instance2, 79));
  CHECK_EQUAL(2, not_so_simple_device_sleep_counter);
  STRCMP_EQUAL("what's up with him!", not_so_simple_device_content_param_spy);
  CHECK_FALSE(AskToSleep(instance1, 99));
  CHECK_EQUAL(2, not_so_simple_device_sleep_counter);
  STRCMP_EQUAL("what's up with him!", not_so_simple_device_content_param_spy);
}