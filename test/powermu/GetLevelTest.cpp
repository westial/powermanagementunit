#include "CppUTest/TestHarness.h"
#include "PowerMU.h"
#include "powermu/GetLevelStub.h"


TEST_GROUP(GetLevel){

    void setup() override{

    }

    void teardown() override{}};

TEST(GetLevel, LevelIsAtTheTop) {
  stub_level_percentage = 100;
  PercentRange range = Percent_Create(0, 100);
  PowerMU pmu = PowerMU_Create((const void *) get_stub_level_percentage, &range);
  CHECK_EQUAL(100, PowerMU_GetLevel(&pmu));
}

TEST(GetLevel, LevelIsAtTheBottom) {
  stub_level_percentage = 0;
  PercentRange range = Percent_Create(0, 100);
  PowerMU pmu = PowerMU_Create((const void *) get_stub_level_percentage, &range);
  CHECK_EQUAL(0, PowerMU_GetLevel(&pmu));
}

TEST(GetLevel, FloatingPointPercentValue) {
  stub_level_percentage = 7;
  PercentRange range = Percent_Create(0, 11);
  PowerMU pmu = PowerMU_Create((const void *) get_stub_level_percentage, &range);
  CHECK_EQUAL(63, PowerMU_GetLevel(&pmu));
}

TEST(GetLevel, LevelIsOverTheTop) {
  stub_level_percentage = 1010;
  PercentRange range = Percent_Create(0, 1000);
  PowerMU pmu = PowerMU_Create((const void *) get_stub_level_percentage, &range);
  CHECK_EQUAL(100, PowerMU_GetLevel(&pmu));
}

TEST(GetLevel, LevelIsUnderTheBottom) {
  stub_level_percentage = -10;
  PercentRange range = Percent_Create(0, 100);
  PowerMU pmu = PowerMU_Create((const void *) get_stub_level_percentage, &range);
  CHECK_EQUAL(0, PowerMU_GetLevel(&pmu));
}

TEST(GetLevel, NegativeLevelReturnsFloatPercent) {
  stub_level_percentage = -3;
  PercentRange range = Percent_Create(-11, 67);
  PowerMU pmu = PowerMU_Create((const void *) get_stub_level_percentage, &range);
  CHECK_EQUAL(10, PowerMU_GetLevel(&pmu));
}
