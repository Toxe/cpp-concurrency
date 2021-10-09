add_executable(thread_class
    main.cpp
    ../common/prime.cpp
    ../common/prime.h
)

set_target_properties(thread_class PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(thread_class PUBLIC cxx_std_20)
target_compile_options(thread_class PRIVATE ${SANITIZER_FLAGS} ${DEFAULT_COMPILER_OPTIONS_AND_WARNINGS})
target_include_directories(thread_class PRIVATE ../common)
target_link_libraries(thread_class PRIVATE ${SANITIZER_FLAGS} Threads::Threads fmt::fmt spdlog::spdlog spdlog::spdlog_header_only)
