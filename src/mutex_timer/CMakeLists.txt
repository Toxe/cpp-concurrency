add_executable(mutex_timer
    main.cpp
    ../common/include/mutex_timer.h
)

set_target_properties(mutex_timer PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(mutex_timer PUBLIC cxx_std_20)
target_compile_options(mutex_timer PRIVATE ${SANITIZER_FLAGS} ${DEFAULT_COMPILER_OPTIONS_AND_WARNINGS})
target_include_directories(mutex_timer PRIVATE ../common/include)
target_link_libraries(mutex_timer PRIVATE ${SANITIZER_FLAGS} prime Threads::Threads fmt::fmt spdlog::spdlog spdlog::spdlog_header_only)
