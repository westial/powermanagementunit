#include "AskToSleep.h"
#include "Sleepable.h"

int AskToSleep(Sleepable instance, unsigned char power_level) {
  if (instance->power_threshold > power_level) {
    return 0 <= Sleepable_TurnOff(instance) ? 1 : -1;
  }
  return 0;
}