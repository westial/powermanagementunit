project (PowerManagementUnit)

include_directories(${PROJECT_SOURCE_DIR}/../include)
include_directories(${PROJECT_SOURCE_DIR}/../include/powermu)
include_directories(${PROJECT_SOURCE_DIR}/../include/number)

add_library(PowerMU ./powermu/PowerMU.c)
add_library(Percent ./number/Percent.c)