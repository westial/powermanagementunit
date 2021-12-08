#include "WakeUp.h"

int WakeUp(Sleepable instance) {
  return 0 <= Sleepable_TurnOn(instance) ? 1 : -1;
}

int xx_WakeUp(Sleepable instance, unsigned char power_level) {
  if (instance->power_threshold <= power_level) {
    return 0 <= Sleepable_TurnOn(instance) ? 1 : -1;
  }
  return 0;
}
