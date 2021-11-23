#include "CppUTest/TestHarness.h"
#include "PowerMU.h"
#include "GetLevelStub.h"

unsigned char stub_level_percentage;

TEST_GROUP(GetLevel)
{

  void setup() override
  {

  }

  void teardown() override
  {
  }
};

TEST(GetLevel, LevelIsAtTheTop)
{
  stub_level_percentage = 100;
  PowerMU pmu = PowerMU_Create((const void*) get_stub_level_percentage);
  CHECK_EQUAL(100, PowerMU_GetLevel(&pmu));
}

TEST(GetLevel, LevelIsAtTheBottom)
{
  stub_level_percentage = 0;
  PowerMU pmu = PowerMU_Create((const void*) get_stub_level_percentage);
  CHECK_EQUAL(0, PowerMU_GetLevel(&pmu));
}
