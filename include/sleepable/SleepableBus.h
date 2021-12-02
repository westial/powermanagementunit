#ifndef POWERMANAGEMENTUNIT_INCLUDE_SLEEPABLE_SLEEPABLEBUS_H_
#define POWERMANAGEMENTUNIT_INCLUDE_SLEEPABLE_SLEEPABLEBUS_H_

#include "Sleepable.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct SleepableBus {
  unsigned int length;
  Sleepable *devices;
  unsigned int max_length;
} SleepableBus;

SleepableBus Sleepable_Create(unsigned int max_length);

int SleepableBus_Add(SleepableBus *bus, Sleepable device);

Sleepable SleepableBus_Get(SleepableBus *bus, unsigned int index);

unsigned int SleepableBus_Length(SleepableBus *bus);

void SleepableBus_Destroy(SleepableBus *bus);

#ifdef __cplusplus
}
#endif

#endif//POWERMANAGEMENTUNIT_INCLUDE_SLEEPABLE_SLEEPABLEBUS_H_
