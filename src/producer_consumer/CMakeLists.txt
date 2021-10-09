add_executable(producer_consumer
    main.cpp
    ../common/prime.cpp
    ../common/prime.h
)

set_target_properties(producer_consumer PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(producer_consumer PUBLIC cxx_std_20)
target_compile_options(producer_consumer PRIVATE ${SANITIZER_FLAGS} ${DEFAULT_COMPILER_OPTIONS_AND_WARNINGS})
target_include_directories(producer_consumer PRIVATE ../common)
target_link_libraries(producer_consumer PRIVATE ${SANITIZER_FLAGS} Threads::Threads fmt::fmt spdlog::spdlog spdlog::spdlog_header_only)
