project (PowerManagementUnit)

# include project source
include_directories(${PROJECT_SOURCE_DIR}/../include)
include_directories(${PROJECT_SOURCE_DIR}/../include/powermu)
include_directories(${PROJECT_SOURCE_DIR}/../include/number)

# include mocks only for test code
include_directories(${PROJECT_SOURCE_DIR}/../mocks)

# add cpputest library
add_library(imp_cpputest STATIC IMPORTED)
set_property(TARGET imp_cpputest PROPERTY IMPORTED_LOCATION $ENV{CPPUTEST_PARENT_DIR}/libCppUTest.a)

# build test library for application
add_library(GetLevelTest powermu/GetLevelTest.cpp)
add_library(PercentTest number/PercentTest.cpp)

add_executable(RunAllTests RunAllTests.cpp)

target_link_libraries(RunAllTests
        imp_cpputest
        GetLevelTest
        PercentTest
        PowerMU
        Percent
        GetLevelStub)
