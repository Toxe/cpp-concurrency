cmake_minimum_required(VERSION 3.12)
project("Threads" LANGUAGES CXX)

# default compiler options and warnings
include(cmake/DefaultCompilerOptionsAndWarnings.cmake)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(ALL_TARGETS
    thread_local
)

foreach(target ${ALL_TARGETS})
    add_executable(${target} ${target}.cpp)
    target_compile_features(${target} PUBLIC cxx_std_17)
    target_compile_options(${target} PRIVATE ${DEFAULT_COMPILER_OPTIONS_AND_WARNINGS})
    set_target_properties(${target} PROPERTIES CXX_EXTENSIONS OFF)
endforeach()
