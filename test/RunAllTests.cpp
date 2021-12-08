#include "CppUTest/CommandLineTestRunner.h"

IMPORT_TEST_GROUP(Balance);
IMPORT_TEST_GROUP(GetLevel);
IMPORT_TEST_GROUP(Percent);
IMPORT_TEST_GROUP(AskToSleep);
IMPORT_TEST_GROUP(SleepableBus);

int main(int argc, char** argv)
{
    return RUN_ALL_TESTS(argc, argv);
}