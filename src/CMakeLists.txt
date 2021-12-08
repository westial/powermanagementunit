project (PowerManagementUnit)

include_directories(${PROJECT_SOURCE_DIR}/../include)
include_directories(${PROJECT_SOURCE_DIR}/../include/powermu)
include_directories(${PROJECT_SOURCE_DIR}/../include/number)
include_directories(${PROJECT_SOURCE_DIR}/../include/sleepable)

add_library(PowerMU ./powermu/PowerMU.c)
add_library(Percent ./number/Percent.c)
add_library(AskToSleep ./sleepable/AskToSleep.c)
add_library(Sleepable ./sleepable/Sleepable.c)
add_library(SleepableBus ./sleepable/SleepableBus.c)
add_library(WakeUp ./sleepable/WakeUp.c)