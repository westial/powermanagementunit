#include "PowerMU.h"

PowerMU PowerMU_Create(const void* get_level) {
  PowerMU pmu;
  pmu.level = get_level;
  return pmu;
}

unsigned char PowerMU_GetLevel(PowerMU* pmu) {
  return pmu->level();
}