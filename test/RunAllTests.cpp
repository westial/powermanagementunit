#include "CppUTest/CommandLineTestRunner.h"

IMPORT_TEST_GROUP(GetLevel);
IMPORT_TEST_GROUP(Percent);

int main(int argc, char** argv)
{
    return RUN_ALL_TESTS(argc, argv);
}