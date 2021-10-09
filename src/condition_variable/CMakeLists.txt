add_executable(condition_variable
    main.cpp
    ../common/prime.cpp
    ../common/prime.h
)

set_target_properties(condition_variable PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(condition_variable PUBLIC cxx_std_20)
target_compile_options(condition_variable PRIVATE ${SANITIZER_FLAGS} ${DEFAULT_COMPILER_OPTIONS_AND_WARNINGS})
target_include_directories(condition_variable PRIVATE ../common)
target_link_libraries(condition_variable PRIVATE ${SANITIZER_FLAGS} Threads::Threads fmt::fmt spdlog::spdlog spdlog::spdlog_header_only)
