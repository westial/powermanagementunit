#ifndef POWERMANAGEMENTUNIT_MOCKS_SLEEPABLE_NOTSOSIMPLESLEEPABLESTUB_H_
#define POWERMANAGEMENTUNIT_MOCKS_SLEEPABLE_NOTSOSIMPLESLEEPABLESTUB_H_

#include "Sleepable.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct NotSoSimpleSleepableStruct *NotSoSimpleSleepable;

Sleepable NotSoSimpleSleepable_Create(
    unsigned char power_threshold,
    int (*sleep)(char *, int),
    int (*wake_up)(char *, int),
    char *input,
    int input_size);

#ifdef __cplusplus
}
#endif

#endif//POWERMANAGEMENTUNIT_MOCKS_SLEEPABLE_NOTSOSIMPLESLEEPABLESTUB_H_
