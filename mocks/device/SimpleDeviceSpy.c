#include "SimpleDeviceSpy.h"

void SimpleDeviceSpy_Sleep() {
  ++simple_device_sleep_counter;
}