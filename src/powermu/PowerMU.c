#include "PowerMU.h"

PowerMU PowerMU_Create(const void *get_level, PercentRange *range) {
  PowerMU pmu;
  pmu.level = get_level;
  pmu.percent_range = *range;
  return pmu;
}

unsigned char PowerMU_GetLevel(PowerMU *pmu) {
  return (unsigned char) Percent_Calculate(&pmu->percent_range, pmu->level());
}