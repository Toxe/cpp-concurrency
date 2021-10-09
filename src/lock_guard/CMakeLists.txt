add_executable(lock_guard
    main.cpp
    ../common/prime.cpp
    ../common/prime.h
)

set_target_properties(lock_guard PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(lock_guard PUBLIC cxx_std_20)
target_compile_options(lock_guard PRIVATE ${SANITIZER_FLAGS} ${DEFAULT_COMPILER_OPTIONS_AND_WARNINGS})
target_include_directories(lock_guard PRIVATE ../common)
target_link_libraries(lock_guard PRIVATE ${SANITIZER_FLAGS} Threads::Threads fmt::fmt spdlog::spdlog spdlog::spdlog_header_only)
