#include "AskToSleep.h"
#include "CppUTest/TestHarness.h"
#include "Sleepable.h"

static void spy_simple_sleep_command();
static int spy_sleep_counter;

void spy_simple_sleep_command() {
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
  CHECK_FALSE(AskToSleep(device, 0));
  CHECK_FALSE(AskToSleep(device, 50));
  CHECK_FALSE(AskToSleep(device, 100));
}

TEST(AskToSleep, ReturnNoNeedToSleep) {
  Sleepable device;
  device.power_threshold = 50;
  CHECK_FALSE(AskToSleep(device, 50));
  CHECK_FALSE(AskToSleep(device, 51));
}

TEST(AskToSleep, MakeDeviceSleep) {
  Sleepable device = Sleepable_Create(100, spy_simple_sleep_command);
  CHECK_TRUE(AskToSleep(device, 99));
  CHECK_EQUAL(1, spy_sleep_counter);
}