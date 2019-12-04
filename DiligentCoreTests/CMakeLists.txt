cmake_minimum_required(VERSION 3.6)

project(DiligentCoreTests)

file(GLOB SOURCE LIST_DIRECTORIES false src/*.cpp)
file(GLOB INCLUDE LIST_DIRECTORIES false include/*.h)

add_executable(DiligentCore_Tests ${SOURCE} ${INCLUDE})

target_link_libraries(DiligentCore_Tests PRIVATE gtest_main)
target_include_directories(DiligentCore_Tests PRIVATE include)
#target_compile_options(DiligentCore_Tests PRIVATE "/MT$<$<CONFIG:Debug>:d>")

#set_common_target_properites(DiligentCore_Tests)
