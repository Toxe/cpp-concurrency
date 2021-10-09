add_executable(atomic
    main.cpp
)

set_target_properties(atomic PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(atomic PUBLIC cxx_std_20)
target_compile_options(atomic PRIVATE ${SANITIZER_FLAGS} ${DEFAULT_COMPILER_OPTIONS_AND_WARNINGS})
target_include_directories(atomic PRIVATE ../common)
target_link_libraries(atomic PRIVATE ${SANITIZER_FLAGS} prime Threads::Threads fmt::fmt spdlog::spdlog spdlog::spdlog_header_only)
