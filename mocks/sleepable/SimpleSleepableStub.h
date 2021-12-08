#ifndef POWERMANAGEMENTUNIT_MOCKS_SIMPLESLEEPABLE_H_
#define POWERMANAGEMENTUNIT_MOCKS_SIMPLESLEEPABLE_H_

#include "Sleepable.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct SimpleSleepableStruct *SimpleSleepable;

Sleepable SimpleSleepable_Create(
    unsigned char power_threshold,
    void (*sleep)(),
    void (*wake_up)()
    );

#ifdef __cplusplus
}
#endif

#endif//POWERMANAGEMENTUNIT_MOCKS_SIMPLESLEEPABLE_H_
