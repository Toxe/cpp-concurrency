add_executable(nth_prime_single_threaded
    main.cpp
    ../common/prime.cpp
    ../common/prime.h
)

set_target_properties(nth_prime_single_threaded PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(nth_prime_single_threaded PUBLIC cxx_std_20)
target_compile_options(nth_prime_single_threaded PRIVATE ${SANITIZER_FLAGS} ${DEFAULT_COMPILER_OPTIONS_AND_WARNINGS})
target_include_directories(nth_prime_single_threaded PRIVATE ../common)
target_link_libraries(nth_prime_single_threaded PRIVATE ${SANITIZER_FLAGS} Threads::Threads fmt::fmt spdlog::spdlog spdlog::spdlog_header_only)
