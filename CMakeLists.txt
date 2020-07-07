cmake_minimum_required(VERSION 3.11)

project(metafsimple)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-pedantic -Wall -Wextra -fcxx-exceptions")

include_directories(
    include
    metaf/include
)

# Tests

add_executable(test 
    googletest/googletest/src/gtest-all.cc
    test/main.cpp
    test/unit_datatypes.cpp
    test/unit_warninglogger.cpp
    test/unit_dataadapter.cpp
    test/unit_metadataadapter.cpp
    test/unit_essentialsdataadapter.cpp
    test/unit_currentdataadapter.cpp
    test/unit_stationdataadapter.cpp
    test/unit_aerodromedataadapter.cpp
    test/unit_forecastdataadapter.cpp
    test/integration_parse_simplify_report.cpp
)

target_include_directories(test PRIVATE 
    googletest/googletest
    googletest/googletest/include)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(TEST_LINK_FLAGS "-lpthread -lm")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(TEST_LINK_FLAGS "-pthread")
endif()	

set_target_properties(test PROPERTIES 
    LINK_FLAGS ${TEST_LINK_FLAGS})
