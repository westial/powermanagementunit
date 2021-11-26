#include "Sleepable.h"

Sleepable Sleepable_Create(unsigned char power_threshold, void (*sleep_)()) {
  Sleepable instance;
  instance.power_threshold = power_threshold;
  instance.sleep = sleep_;
  return instance;
}