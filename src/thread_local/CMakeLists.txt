add_executable(thread_local
    main.cpp
)

set_target_properties(thread_local PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(thread_local PUBLIC cxx_std_20)
target_compile_options(thread_local PRIVATE ${SANITIZER_FLAGS} ${DEFAULT_COMPILER_OPTIONS_AND_WARNINGS})
target_include_directories(thread_local PRIVATE ../common)
target_link_libraries(thread_local PRIVATE ${SANITIZER_FLAGS} Threads::Threads fmt::fmt spdlog::spdlog spdlog::spdlog_header_only)
