add_executable(performance_atomic_vs_mutex
    main.cpp
)

set_target_properties(performance_atomic_vs_mutex PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(performance_atomic_vs_mutex PUBLIC cxx_std_20)
target_compile_options(performance_atomic_vs_mutex PRIVATE ${SANITIZER_FLAGS} ${DEFAULT_COMPILER_OPTIONS_AND_WARNINGS})
target_include_directories(performance_atomic_vs_mutex PRIVATE ../common)
target_link_libraries(performance_atomic_vs_mutex PRIVATE ${SANITIZER_FLAGS} prime Threads::Threads fmt::fmt spdlog::spdlog spdlog::spdlog_header_only)
