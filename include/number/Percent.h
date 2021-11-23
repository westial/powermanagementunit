//
// Created by jaume on 11/23/21.
//

#ifndef POWERMANAGEMENTUNIT_INCLUDE_NUMBER_PERCENT_H_
#define POWERMANAGEMENTUNIT_INCLUDE_NUMBER_PERCENT_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct PercentRange {
  double zero;
  double hundred;
} PercentRange;

PercentRange Percent_Create(double zero, double hundred);

float Percent_Calculate(PercentRange *range, double aValue);

#ifdef __cplusplus
}
#endif

#endif//POWERMANAGEMENTUNIT_INCLUDE_NUMBER_PERCENT_H_
