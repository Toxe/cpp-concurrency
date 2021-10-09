if((CMAKE_CXX_COMPILER_ID MATCHES "GNU"   AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "11.0.0") OR
   (CMAKE_CXX_COMPILER_ID MATCHES "Clang" AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "11.0.0") OR
   (CMAKE_CXX_COMPILER_ID MATCHES "MSVC"  AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "19.28"))
    add_executable(latch_wait
        main.cpp
    )

    set_target_properties(latch_wait PROPERTIES CXX_EXTENSIONS OFF)
    target_compile_features(latch_wait PUBLIC cxx_std_20)
    target_compile_options(latch_wait PRIVATE ${SANITIZER_FLAGS} ${DEFAULT_COMPILER_OPTIONS_AND_WARNINGS})
    target_include_directories(latch_wait PRIVATE ../common)
    target_link_libraries(latch_wait PRIVATE ${SANITIZER_FLAGS} prime Threads::Threads fmt::fmt spdlog::spdlog spdlog::spdlog_header_only)
endif()
