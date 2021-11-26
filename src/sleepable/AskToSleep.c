#include "AskToSleep.h"
#include "Sleepable.h"

unsigned char AskToSleep(Sleepable aDevice, unsigned char power_level) {
  if (aDevice.power_threshold > power_level) {
    aDevice.sleep();
    return 1;
  }
  return 0;
}