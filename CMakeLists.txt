cmake_minimum_required(VERSION 3.11)

project(metafsimple)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-pedantic -Wall -Wextra")

set(CLANG_TEST_LINK_FLAGS "-lpthread -lm")

set(GCC_TEST_LINK_FLAGS "-pthread")

set(CLANG_COVERAGE_COMPILE_FLAGS "-O0 -g -fprofile-instr-generate -fcoverage-mapping")
set(CLANG_COVERAGE_LINK_FLAGS "-lpthread -lm -fprofile-instr-generate -fcoverage-mapping")

set(GCC_COVERAGE_COMPILE_FLAGS "-O0 -fprofile-arcs -ftest-coverage")
set(GCC_COVERAGE_LINK_FLAGS "-pthread -lgcov --coverage")

message("Compiler ID: " ${CMAKE_CXX_COMPILER_ID})

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(TEST_LINK_FLAGS ${CLANG_TEST_LINK_FLAGS})
    set(COVERAGE_COMPILE_FLAGS ${CLANG_COVERAGE_COMPILE_FLAGS})
    set(COVERAGE_LINK_FLAGS ${CLANG_COVERAGE_LINK_FLAGS})
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(TEST_LINK_FLAGS ${GCC_TEST_LINK_FLAGS})
    set(COVERAGE_COMPILE_FLAGS ${GCC_COVERAGE_COMPILE_FLAGS})
    set(COVERAGE_LINK_FLAGS ${GCC_COVERAGE_LINK_FLAGS})
endif()	

message("Test link flags: " ${TEST_LINK_FLAGS})
message("Coverage compile flags: " ${COVERAGE_COMPILE_FLAGS})
message("Coverage link flags: " ${COVERAGE_LINK_FLAGS})

include_directories(
    include
    metaf/include
)

set(SOURCES ${SOURCES} 
    googletest/googletest/src/gtest-all.cc
    test/main.cpp
    test/unit_datatypes.cpp
    test/unit_warninglogger.cpp
    test/unit_metadataadapter.cpp
    test/unit_basicdataadapter.cpp
    test/unit_essentialsadapter.cpp
    test/integration_basic_reports.cpp
    test/integration_report_data.cpp
    test/integration_wind_main.cpp
    test/integration_visibility_main.cpp
    test/integration_sky_condition_main.cpp
    test/integration_current_weather.cpp
    test/integration_tafs.cpp
    test/integration_metar_trends.cpp
    test/integration_temp_pres_main.cpp
    test/integration_sea_surface.cpp
    test/integration_temp_pres_rmk.cpp
    test/integration_runway_state.cpp
    test/integration_wind_historical.cpp
    test/integration_chino_visno.cpp
)

# Tests

add_executable(test ${SOURCES})

target_include_directories(test PRIVATE 
    googletest/googletest
    googletest/googletest/include
    test/include)

set_target_properties(test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin
    LINK_FLAGS ${TEST_LINK_FLAGS})

# Coverage

add_executable(testcoverage ${SOURCES})

target_include_directories(testcoverage PRIVATE 
    googletest/googletest
    googletest/googletest/include
    test/include)

set_target_properties(testcoverage PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin
    COMPILE_FLAGS ${COVERAGE_COMPILE_FLAGS}
    LINK_FLAGS ${COVERAGE_LINK_FLAGS})
