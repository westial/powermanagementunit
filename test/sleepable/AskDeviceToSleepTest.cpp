#include "AskToSleep.h"
#include "CppUTest/TestHarness.h"
#include "Sleepable.h"

static int spy_sleep_counter;

static void spy_simple_sleep_command();
static void spy_two_args_sleep_command(int arg1, char *args2);

// -----------------------------------------------------------------------------

void spy_simple_sleep_command() {
  ++spy_sleep_counter;
}

static void spy_two_args_sleep_command(int arg1, char *args2) {
  ++spy_sleep_counter;
}

TEST_GROUP(AskToSleep){

    void setup() override{
        spy_sleep_counter = 0;
    }
};

TEST(AskToSleep, BypassPowerCheck) {
  Sleepable device;
  device.power_threshold = 0;
  CHECK_FALSE(AskToSleep(&device, 0));
  CHECK_FALSE(AskToSleep(&device, 50));
  CHECK_FALSE(AskToSleep(&device, 100));
}

TEST(AskToSleep, ReturnNoNeedToSleep) {
  Sleepable device;
  device.power_threshold = 50;
  CHECK_FALSE(AskToSleep(&device, 50));
  CHECK_FALSE(AskToSleep(&device, 51));
}

TEST(AskToSleep, MakeSimpleDeviceSleep) {
  Sleepable device = Sleepable_Create(100, spy_simple_sleep_command);
  CHECK_TRUE(AskToSleep(&device, 99));
  CHECK_EQUAL(1, spy_sleep_counter);
}

//TEST(AskToSleep, MakeSleepADeviceWitTwoArgsCallback) {
//  Sleepable device = Sleepable_Create(100, spy_two_args_sleep_command);
//  CHECK_TRUE(AskToSleep(&device, 99));
//  CHECK_EQUAL(1, spy_sleep_counter);
//}