#ifndef POWERMANAGEMENTUNIT_PREDEFINED_VOIDSLEEPABLE_H_
#define POWERMANAGEMENTUNIT_PREDEFINED_VOIDSLEEPABLE_H_

#include "Sleepable.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct VoidSleepableStruct *VoidSleepable;

Sleepable VoidSleepable_Create(
    unsigned char power_threshold,
    void (*sleep)(),
    void (*wake_up)()
    );

#ifdef __cplusplus
}
#endif

#endif//POWERMANAGEMENTUNIT_PREDEFINED_VOIDSLEEPABLE_H_
