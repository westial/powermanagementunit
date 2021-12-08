#include "SleepableBus.h"
#include <malloc.h>

SleepableBus Sleepable_Create(unsigned int max_length) {
  return (SleepableBus){
      .length = 0,
      .devices = malloc(max_length * sizeof(Sleepable)),
      .max_length = max_length
  };
}

int SleepableBus_Add(SleepableBus *bus, Sleepable device) {
  if (bus->max_length > bus->length) {
    bus->devices[bus->length++] = device;
    return 1;
  } else {
    return 0;
  }
}

Sleepable SleepableBus_Get(SleepableBus *bus, unsigned int index) {
  if (index < bus->length) return bus->devices[index];
  return 0;
}

unsigned int SleepableBus_Length(SleepableBus *bus) {
  return bus->length;
}

void SleepableBus_Destroy(SleepableBus *bus) {
  while (0 < bus->length) {
    free(bus->devices[--bus->length]);
  }
}