cmake_minimum_required(VERSION 3.5)

project(testing_libraries)

include(CTest)

add_library(imp_cpputest STATIC IMPORTED)
add_library(imp_cpputestExt STATIC IMPORTED)
set_property(TARGET imp_cpputest PROPERTY
             IMPORTED_LOCATION $ENV{CPPUTEST_HOME}/libCppUTest.a )
set_property(TARGET imp_cpputestExt PROPERTY
             IMPORTED_LOCATION $ENV{CPPUTEST_HOME}/libCppUTestExt.a )

target_include_directories(imp_cpputest INTERFACE $ENV{CPPUTEST_HOME}/../include)
target_include_directories(imp_cpputestExt INTERFACE $ENV{CPPUTEST_HOME}/../include)

add_subdirectory(00-test-utils/utils)
add_subdirectory(00-test-test/test)

