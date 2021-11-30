project (PowerManagementUnit)

include_directories(${PROJECT_SOURCE_DIR}/../include)
include_directories(${PROJECT_SOURCE_DIR}/../include/sleepable)

add_library(GetLevelStub GetLevelStub.c)
add_library(SimpleDeviceSpy device/SimpleDeviceSpy.c)
add_library(SimpleSleepableStub sleepable/SimpleSleepableStub.c)