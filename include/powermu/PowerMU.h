//
// Created by jaume on 11/19/21.
//

#ifndef POWERMANAGEMENTUNIT_INCLUDE_POWERMU_POWERMU_H_
#define POWERMANAGEMENTUNIT_INCLUDE_POWERMU_POWERMU_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct PowerMU {
  unsigned char (*level)();
} PowerMU;

PowerMU PowerMU_Create(const void *get_level);

unsigned char PowerMU_GetLevel(PowerMU* pmu);

#ifdef __cplusplus
}
#endif

#endif//POWERMANAGEMENTUNIT_INCLUDE_POWERMU_POWERMU_H_
