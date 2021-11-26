#include "AskToSleep.h"
#include "Sleepable.h"

static void make_sleep(Sleepable* aDevice);

void make_sleep(Sleepable* aDevice) {
  aDevice->sleep();
}

unsigned char AskToSleep(Sleepable *aDevice, unsigned char power_level) {
  if (aDevice->power_threshold > power_level) {
    make_sleep(aDevice);
    return 1;
  }
  return 0;
}