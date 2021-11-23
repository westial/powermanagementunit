#include "CppUTest/TestHarness.h"
#include "Percent.h"

TEST_GROUP(Percent)
{

  void setup() override
  {

  }

  void teardown() override
  {
  }
};

TEST(Percent, Zero)
{
  PercentRange range = Percent_Create(0, 1000);
  float result = Percent_Calculate(&range, 0);
  CHECK_EQUAL(0, result);
}

TEST(Percent, CalculatePositiveIntegerPercent)
{
  PercentRange range = Percent_Create(0, 1000);
  float result = Percent_Calculate(&range, 500);
  CHECK_EQUAL(50, result);
}

TEST(Percent, CalculateNegativeIntegerPercent)
{
  PercentRange range = Percent_Create(-1000, 0);
  float result = Percent_Calculate(&range, -500);
  CHECK_EQUAL(50, result);
}

TEST(Percent, CalculatePositiveFloatPercent)
{
  PercentRange range = Percent_Create(0, 1);
  float result = Percent_Calculate(&range, 0.5);
  CHECK_EQUAL(50, result);
}

TEST(Percent, CalculateAllGreaterThanZeroPercent)
{
  PercentRange range = Percent_Create(100, 1100);
  float result = Percent_Calculate(&range, 700);
  CHECK_EQUAL(60, result);
}

TEST(Percent, CalculateZeroNegativeFloatPercent)
{
  PercentRange range = Percent_Create(-1, 0);
  float result = Percent_Calculate(&range, -0.3);
  CHECK_EQUAL(70, result);
}

TEST(Percent, CalculateAllNegativeFloatPercent)
{
  PercentRange range = Percent_Create(-2, -1);
  float result = Percent_Calculate(&range, -1.3);
  CHECK_EQUAL(70, result);
}

TEST(Percent, LimitMaximumOutput)
{
  PercentRange range = Percent_Create(0, 1000);
  float result = Percent_Calculate(&range, 1500);
  CHECK_EQUAL(100, result);
}

TEST(Percent, LimitMinimumOutput)
{
  PercentRange range = Percent_Create(0, 1000);
  float result = Percent_Calculate(&range, -500);
  CHECK_EQUAL(0, result);
}

TEST(Percent, ReturnPositiveFloat)
{
  PercentRange range = Percent_Create(0, 7);
  float result = Percent_Calculate(&range, 3);
  DOUBLES_EQUAL(42.85, result, 0.01);
}

TEST(Percent, ReturnNegativeFloat)
{
  PercentRange range = Percent_Create(-7, 0);
  float result = Percent_Calculate(&range, -4);
  DOUBLES_EQUAL(42.85, result, 0.01);
}
