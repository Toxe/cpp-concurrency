if((CMAKE_CXX_COMPILER_ID MATCHES "GNU"  AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "10.0.0") OR
   (CMAKE_CXX_COMPILER_ID MATCHES "MSVC" AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "19.28"))
    add_executable(jthread_class_member_function_with_stop_token
        main.cpp
    )

    set_target_properties(jthread_class_member_function_with_stop_token PROPERTIES CXX_EXTENSIONS OFF)
    target_compile_features(jthread_class_member_function_with_stop_token PUBLIC cxx_std_20)
    target_compile_options(jthread_class_member_function_with_stop_token PRIVATE ${SANITIZER_FLAGS} ${DEFAULT_COMPILER_OPTIONS_AND_WARNINGS})
    target_include_directories(jthread_class_member_function_with_stop_token PRIVATE ../common)
    target_link_libraries(jthread_class_member_function_with_stop_token PRIVATE ${SANITIZER_FLAGS} prime Threads::Threads fmt::fmt spdlog::spdlog spdlog::spdlog_header_only)
endif()
