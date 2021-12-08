#include "WakeUp.h"

int WakeUp(Sleepable instance, unsigned char power_level) {
  if (instance->power_threshold <= power_level) {
    return 0 <= Sleepable_TurnOn(instance) ? 1 : -1;
  }
  return 0;
}
