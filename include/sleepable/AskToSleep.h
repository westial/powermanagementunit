#ifndef POWERMANAGEMENTUNIT_INCLUDE_SLEEPABLE_ASKTOSLEEP_H_
#define POWERMANAGEMENTUNIT_INCLUDE_SLEEPABLE_ASKTOSLEEP_H_

#include "Sleepable.h"
#ifdef __cplusplus
extern "C" {
#endif

unsigned char AskToSleep(Sleepable aDevice, unsigned char power_level);

#ifdef __cplusplus
}
#endif

#endif//POWERMANAGEMENTUNIT_INCLUDE_SLEEPABLE_ASKTOSLEEP_H_
