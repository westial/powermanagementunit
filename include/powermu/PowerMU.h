#ifndef POWERMANAGEMENTUNIT_INCLUDE_POWERMU_POWERMU_H_
#define POWERMANAGEMENTUNIT_INCLUDE_POWERMU_POWERMU_H_

#include "Percent.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct PowerMU {
  double (*level)();
  PercentRange percent_range;
} PowerMU;

PowerMU PowerMU_Create(const void* get_level, PercentRange* rang);

unsigned char PowerMU_GetLevel(PowerMU* pmu);

#ifdef __cplusplus
}
#endif

#endif//POWERMANAGEMENTUNIT_INCLUDE_POWERMU_POWERMU_H_
