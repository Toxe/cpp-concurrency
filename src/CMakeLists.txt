set(ALL_TARGETS
    nth_prime_single_threaded
    async
    atomic
    condition_variable1
    lock_guard
    thread_local
)

add_executable(thread_local thread_local.cpp)
add_executable(nth_prime_single_threaded nth_prime_single_threaded.cpp
                                         common/prime.h common/prime.cpp)
add_executable(async async.cpp
                     common/prime.h common/prime.cpp)
add_executable(atomic atomic.cpp
                      common/prime.h common/prime.cpp)
add_executable(condition_variable1 condition_variable1.cpp
                                   common/prime.h common/prime.cpp)
add_executable(lock_guard lock_guard.cpp
                          common/prime.h common/prime.cpp)

# std::jthread: GCC 10+
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "10.0.0")
        list(APPEND ALL_TARGETS jthread)

        add_executable(jthread jthread.cpp
                               common/prime.h common/prime.cpp)
    endif()
endif()

# std::latch: GCC 11+, Clang 11+
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "11.0.0")
        list(APPEND ALL_TARGETS latch_arrive_and_wait
                                latch_wait)

        add_executable(latch_arrive_and_wait latch_arrive_and_wait.cpp
                                             common/prime.h common/prime.cpp)
        add_executable(latch_wait latch_wait.cpp
                                  common/prime.h common/prime.cpp)
    endif()
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "11.0.0")
        list(APPEND ALL_TARGETS latch_arrive_and_wait
                                latch_wait)

        add_executable(latch_arrive_and_wait latch_arrive_and_wait.cpp
                                             common/prime.h common/prime.cpp)
        add_executable(latch_wait latch_wait.cpp
                                  common/prime.h common/prime.cpp)
    endif()
endif()

foreach(target ${ALL_TARGETS})
    set_target_properties(${target} PROPERTIES CXX_EXTENSIONS OFF)
    target_compile_features(${target} PUBLIC cxx_std_20)
    target_compile_options(${target} PRIVATE ${SANITIZER_FLAGS} ${DEFAULT_COMPILER_OPTIONS_AND_WARNINGS})
    target_link_libraries(${target} PRIVATE ${SANITIZER_FLAGS} Threads::Threads fmt::fmt spdlog::spdlog spdlog::spdlog_header_only)
endforeach()
