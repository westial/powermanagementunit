project (PowerManagementUnit)

# include project source
include_directories(${PROJECT_SOURCE_DIR}/../include)
include_directories(${PROJECT_SOURCE_DIR}/../include/powermu)
include_directories(${PROJECT_SOURCE_DIR}/../include/number)
include_directories(${PROJECT_SOURCE_DIR}/../include/sleepable)

# include mocks only for test code
include_directories(${PROJECT_SOURCE_DIR}/../mocks)

# add cpputest library
add_library(imp_cpputest STATIC IMPORTED)
set_property(TARGET imp_cpputest PROPERTY IMPORTED_LOCATION $ENV{CPPUTEST_PARENT_DIR}/libCppUTest.a)

# build test library for application
add_library(GetLevelTest powermu/GetLevelTest.cpp)
add_library(PercentTest number/PercentTest.cpp)
add_library(MakeDeviceSleepTest sleepable/AskDeviceToSleepTest.cpp)
add_library(SleepableBusTest sleepable/SleepableBusTest.cpp)

add_executable(RunAllTests RunAllTests.cpp)

target_link_libraries(RunAllTests
        imp_cpputest
        GetLevelTest
        PercentTest
        MakeDeviceSleepTest
        SleepableBusTest
        PowerMU
        Percent
        AskToSleep
        Sleepable
        SleepableBus
        GetLevelStub
        SimpleDeviceSpy
        SimpleSleepableStub
        NotSoSimpleDeviceSpy
        NotSoSimpleSleepableStub
        AlreadyOffSimpleSleepableStub
        FailingSimpleSleepableStub
        )
