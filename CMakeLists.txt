cmake_minimum_required(VERSION 3.18)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project("C++ Concurrency" LANGUAGES CXX)

# default compiler options and warnings
include(cmake/DefaultCompilerOptionsAndWarnings.cmake)

# static analyzers
include(cmake/StaticAnalyzers.cmake)

# sanitizers
include(cmake/Sanitizers.cmake)

find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(Threads REQUIRED)

add_subdirectory(src/async)
add_subdirectory(src/atomic)
add_subdirectory(src/condition_variable)
add_subdirectory(src/jthread)
add_subdirectory(src/latch_arrive_and_wait)
add_subdirectory(src/latch_wait)
add_subdirectory(src/lock_guard)
add_subdirectory(src/mutex_timer)
add_subdirectory(src/nth_prime_single_threaded)
add_subdirectory(src/producer_consumer)
add_subdirectory(src/thread_class)
add_subdirectory(src/thread_local)
