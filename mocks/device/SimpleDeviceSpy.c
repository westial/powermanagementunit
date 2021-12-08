#include "SimpleDeviceSpy.h"

int simple_device_sleep_counter;
int simple_device_wake_up_counter;

void SimpleDeviceSpy_Sleep() {
  ++simple_device_sleep_counter;
}

void SimpleDeviceSpy_WakeUp() {
  ++simple_device_wake_up_counter;
}