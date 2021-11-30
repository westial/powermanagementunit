#include "AskToSleep.h"
#include "CppUTest/TestHarness.h"
#include "Sleepable.h"
#include "device/SimpleDeviceSpy.h"
#include "sleepable/SimpleSleepableStub.h"

int simple_device_sleep_counter;

TEST_GROUP(AskToSleep){

    void setup() override{
        simple_device_sleep_counter = 0;
        SimpleSleepable_InstallInterface();
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

//TEST(AskToSleep, MakeSleepADeviceWitTwoArgsCallback) {
//  SleepableStruct device = Sleepable_Create(100, NotSoSimpleDeviceSpy_Sleep);
//  CHECK_TRUE(AskToSleep(&device, 99));
//  CHECK_EQUAL(1, not_so_simple_device_sleep_counter);
//}