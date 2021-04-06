set(ALL_TARGETS
    nth_prime_single_threaded
    thread_local
    std_atomic
    std_lock_guard
)

add_executable(thread_local thread_local.cpp)
add_executable(nth_prime_single_threaded nth_prime_single_threaded.cpp
                                         common/prime.h common/prime.cpp)
add_executable(std_atomic std_atomic.cpp
                          common/prime.h common/prime.cpp)
add_executable(std_lock_guard std_lock_guard.cpp
                              common/prime.h common/prime.cpp)

foreach(target ${ALL_TARGETS})
    set_target_properties(${target} PROPERTIES CXX_EXTENSIONS OFF)
    target_compile_features(${target} PUBLIC cxx_std_20)
    target_compile_options(${target} PRIVATE ${SANITIZER_FLAGS} ${DEFAULT_COMPILER_OPTIONS_AND_WARNINGS})
    target_link_libraries(${target} PRIVATE ${SANITIZER_FLAGS} Threads::Threads)
endforeach()
