#include "PowerMU.h"
#include "AskToSleep.h"
#include "WakeUp.h"

unsigned int make_all_device_sleep(unsigned char power_level, SleepableBus *bus);
unsigned int make_all_device_wake_up(unsigned char power_level, SleepableBus *bus);

unsigned int make_all_device_sleep(unsigned char power_level, SleepableBus *bus) {
  unsigned int index;
  int result;
  unsigned int asleep_count = 0;
  for (index = 0; index < SleepableBus_Length(bus); index++) {
    result = AskToSleep(SleepableBus_Get(bus, index), power_level);
    if (0 > result) return -1;
    asleep_count += result;
  }
  return asleep_count;
}

unsigned int make_all_device_wake_up(unsigned char power_level, SleepableBus *bus) {
  unsigned int index;
  int result;
  unsigned int awake_count = 0;
  for (index = 0; index < SleepableBus_Length(bus); index++) {
    result = xx_WakeUp(SleepableBus_Get(bus, index), power_level);
    if (0 > result) return -1;
    awake_count += result;
  }
  return awake_count;
}

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

PowerReport PowerMU_Balance(PowerMU* pmu) {
  PowerReport report;
  if (0 == SleepableBus_Length(&pmu->sleepables)) {
    report.error = 1;
  } else {
    report.error = 0;
    report.asleep = (int)make_all_device_sleep(PowerMU_GetLevel(pmu), &pmu->sleepables);
    report.awake = (int)make_all_device_wake_up(PowerMU_GetLevel(pmu), &pmu->sleepables);
  }
  return report;
}

int PowerMU_Register(PowerMU* pmu, Sleepable device) {
  return SleepableBus_Add(&pmu->sleepables, device);
}

void PowerMU_Destroy(PowerMU* pmu) {
  SleepableBus_Destroy(&pmu->sleepables);
}