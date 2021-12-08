#ifndef POWERMANAGEMENTUNIT_INCLUDE_POWERMU_POWERMU_H_
#define POWERMANAGEMENTUNIT_INCLUDE_POWERMU_POWERMU_H_

#include "Percent.h"
#include "SleepableBus.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct PowerReport {
  int awake;
  int asleep;
  int error;
} PowerReport;

typedef struct PowerMU {
  double (*level)();
  PercentRange percent_range;
  SleepableBus sleepables;
} PowerMU;

PowerMU PowerMU_Create(const void* get_level, PercentRange* rang);

unsigned char PowerMU_GetLevel(PowerMU* pmu);

PowerReport PowerMU_Balance(PowerMU* pmu);

int PowerMU_Register(PowerMU* pmu, Sleepable device);

void PowerMU_Destroy(PowerMU* pmu);

#ifdef __cplusplus
}
#endif

#endif//POWERMANAGEMENTUNIT_INCLUDE_POWERMU_POWERMU_H_
