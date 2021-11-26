#include "AskToSleep.h"
#include "Sleepable.h"

unsigned char AskToSleep(Sleepable instance, unsigned char power_level) {
  if (instance->power_threshold > power_level) {
    Sleepable_TurnOff(instance);
    return 1;
  }
  return 0;
}