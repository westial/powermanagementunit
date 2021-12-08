#include "PowerMU.h"
#include "AskToSleep.h"

PowerMU PowerMU_Create(const void *get_level, PercentRange *range) {
  PowerMU pmu;
  pmu.level = get_level;
  pmu.percent_range = *range;
  pmu.sleepables = Sleepable_Create(10);
  return pmu;
}

unsigned char PowerMU_GetLevel(PowerMU *pmu) {
  return (unsigned char) Percent_Calculate(&pmu->percent_range, pmu->level());
}

int PowerMU_Balance(PowerMU* pmu) {
  if (0 == SleepableBus_Length(&pmu->sleepables)) return -1;
  return AskToSleep(
      SleepableBus_Get(&pmu->sleepables, 0),
      PowerMU_GetLevel(pmu)
      );
}

int PowerMU_Register(PowerMU* pmu, Sleepable device) {
  return SleepableBus_Add(&pmu->sleepables, device);
}