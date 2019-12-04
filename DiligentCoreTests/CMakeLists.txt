cmake_minimum_required(VERSION 3.6)

project(DiligentCoreTests)

file(GLOB SOURCE LIST_DIRECTORIES false src/*.cpp)
file(GLOB INCLUDE LIST_DIRECTORIES false include/*.h)

add_executable(DiligentCore_Tests ${SOURCE} ${INCLUDE})

target_link_libraries(DiligentCore_Tests PRIVATE gtest_main)
target_include_directories(DiligentCore_Tests PRIVATE include)
#target_compile_options(DiligentCore_Tests PRIVATE "/MT$<$<CONFIG:Debug>:d>")

#set_common_target_properites(DiligentCore_Tests)
set_target_properties(DiligentCore_Tests PROPERTIES
    CXX_VISIBILITY_PRESET hidden # -fvisibility=hidden
    C_VISIBILITY_PRESET hidden # -fvisibility=hidden
    VISIBILITY_INLINES_HIDDEN TRUE

    # Without -fPIC option GCC fails to link static libraries into dynamic library:
    #  -fPIC  
    #      If supported for the target machine, emit position-independent code, suitable for 
    #      dynamic linking and avoiding any limit on the size of the global offset table.
    POSITION_INDEPENDENT_CODE ON

    # It is crucial to set CXX_STANDARD flag to only affect c++ files and avoid failures compiling c-files:
    # error: invalid argument '-std=c++11' not allowed with 'C/ObjC'
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
)
