#ifndef POWERMANAGEMENTUNIT_INCLUDE_SLEEPABLE_SLEEPABLE_H_
#define POWERMANAGEMENTUNIT_INCLUDE_SLEEPABLE_SLEEPABLE_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SleepableInterfaceStruct *SleepableInterface;

typedef struct SleepableStruct *Sleepable;

void Sleepable_Init(
    Sleepable instance,
    SleepableInterface interface,
    unsigned char power_threshold);
void Sleepable_Destroy(Sleepable instance);
int Sleepable_TurnOff(Sleepable instance);
int Sleepable_TurnOn(Sleepable instance);

#ifdef __cplusplus
}
#endif

#endif//POWERMANAGEMENTUNIT_INCLUDE_SLEEPABLE_SLEEPABLE_H_

#include "SleepablePrivate.h"
