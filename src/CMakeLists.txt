project (PowerManagementUnit)

include_directories(${PROJECT_SOURCE_DIR}/../include)
include_directories(${PROJECT_SOURCE_DIR}/../include/powermu)

add_library(PowerMU ./powermu/PowerMU.c)