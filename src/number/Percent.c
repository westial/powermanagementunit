#include "Percent.h"

static float calculate(double zero, double hundred, double aValue);
static double limitTop(double max, double result);
static double limitBottom(double min, double result);
static double limit(double min, double max, double result);

PercentRange Percent_Create(double zero, double hundred) {
  PercentRange range;
  range.zero = zero;
  range.hundred = hundred;
  return range;
}

float calculate(double zero, double hundred, double aValue) {
  double zeroDiff = 0 - zero;
  float result = (float)(((aValue + zeroDiff) * 100) / (hundred + zeroDiff));
  return result;
}

double limitTop(double max, double result) {
  return (float)max < result ? (float)max : result;
}

double limitBottom(double min, double result) {
  return (float)min > result ? (float)min : result;
}

double limit(double min, double max, double result) {
  return limitBottom(min, limitTop(max, result));
}

float Percent_Calculate(PercentRange *range, double aValue) {
  return calculate(
          range->zero,
          range->hundred,
      limit(
          range->zero,
          range->hundred,
          aValue)
      );
}