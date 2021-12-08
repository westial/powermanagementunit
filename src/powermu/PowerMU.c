#include "PowerMU.h"
#include "AskToSleep.h"
#include "WakeUp.h"

int all_device_callback(
    int (*callback)(Sleepable, unsigned char),
    unsigned char power_level,
    SleepableBus *bus,
    int *error_count
    );

int make_all_device_sleep(
    unsigned char power_level,
    SleepableBus *bus,
    int *error_count
    );
int make_all_device_wake_up(
    unsigned char power_level,
    SleepableBus *bus,
    int *error_count
    );

int all_device_callback(
    int (*callback)(Sleepable, unsigned char),
    unsigned char power_level,
    SleepableBus *bus,
    int *error_count
) {
  unsigned int index;
  int result;
  int count = 0;
  for (index = 0; index < SleepableBus_Length(bus); index++) {
    result = callback(SleepableBus_Get(bus, index), power_level);
    if (0 > result) {
      *error_count += 1;
    } else {
      count += result;
    }
  }
  return count;
}

int make_all_device_sleep(
    unsigned char power_level,
    SleepableBus *bus,
    int *error_count) {
  return all_device_callback(AskToSleep, power_level, bus, error_count);
}

int make_all_device_wake_up(
    unsigned char power_level,
    SleepableBus *bus,
    int *error_count) {
  return all_device_callback(WakeUp, power_level, bus, error_count);
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
  report.error = 0;
  if (0 == SleepableBus_Length(&pmu->sleepables)) {
    report.error = -1;
  } else {
    report.error = 0;
    report.asleep = make_all_device_sleep(
        PowerMU_GetLevel(pmu),
        &pmu->sleepables,
        &report.error
        );
    report.awake = make_all_device_wake_up(
        PowerMU_GetLevel(pmu),
        &pmu->sleepables,
        &report.error
        );
  }
  return report;
}

int PowerMU_Register(PowerMU* pmu, Sleepable device) {
  return SleepableBus_Add(&pmu->sleepables, device);
}

void PowerMU_Destroy(PowerMU* pmu) {
  SleepableBus_Destroy(&pmu->sleepables);
}