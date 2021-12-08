#include "CppUTest/TestHarness.h"
#include "Sleepable.h"
#include "WakeUp.h"
#include "device/SimpleDeviceSpy.h"
#include "sleepable/SimpleSleepableStub.h"

TEST_GROUP(WakeUp){

    void setup() override{
    }
};

TEST(WakeUp, WakeUpADevice) {
  Sleepable instance = SimpleSleepable_Create(0, SimpleDeviceSpy_Sleep);
  int result = WakeUp(instance);
  CHECK_EQUAL(1, result);
  CHECK_EQUAL(1, instance->is_sleeping);
}