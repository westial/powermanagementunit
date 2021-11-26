//
// Created by jaume on 11/25/21.
//

#ifndef POWERMANAGEMENTUNIT_INCLUDE_SLEEPABLE_SLEEPABLE_H_
#define POWERMANAGEMENTUNIT_INCLUDE_SLEEPABLE_SLEEPABLE_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Sleepable {
  unsigned char power_threshold;
  void (*sleep)();
} Sleepable;

Sleepable Sleepable_Create(unsigned char power_threshold, void (*sleep_)());

#ifdef __cplusplus
}
#endif

#endif//POWERMANAGEMENTUNIT_INCLUDE_SLEEPABLE_SLEEPABLE_H_
