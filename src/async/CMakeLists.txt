add_executable(async
    main.cpp
)

set_target_properties(async PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(async PUBLIC cxx_std_20)
target_compile_options(async PRIVATE ${SANITIZER_FLAGS} ${DEFAULT_COMPILER_OPTIONS_AND_WARNINGS})
target_link_libraries(async PRIVATE ${SANITIZER_FLAGS} prime Threads::Threads fmt::fmt spdlog::spdlog spdlog::spdlog_header_only)
