#ifndef POWERMANAGEMENTUNIT_MOCKS_SLEEPABLE_FAILINGSIMPLESLEEPABLESTUB_H_
#define POWERMANAGEMENTUNIT_MOCKS_SLEEPABLE_FAILINGSIMPLESLEEPABLESTUB_H_

#include "Sleepable.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct SimpleSleepableStruct *SimpleSleepable;

Sleepable FailingSimpleSleepable_Create(unsigned char power_threshold, void (*sleep)());

#ifdef __cplusplus
}
#endif

#endif//POWERMANAGEMENTUNIT_MOCKS_SLEEPABLE_FAILINGSIMPLESLEEPABLESTUB_H_
