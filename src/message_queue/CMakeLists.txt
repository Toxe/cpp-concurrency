set(ALL_TARGETS
    poll
    wait_until_finished
)

foreach(suffix ${ALL_TARGETS})
    set(target "message_queue_${suffix}")

    add_executable(${target}
        "main_${suffix}.cpp"
        message_queue/message_queue.hpp
        supervisor/messages.hpp
        supervisor/supervisor.cpp
        supervisor/supervisor.hpp
        worker/messages.hpp
        worker/worker.cpp
        worker/worker.hpp
    )

    set_target_properties(${target} PROPERTIES CXX_EXTENSIONS OFF)
    target_compile_features(${target} PUBLIC cxx_std_20)
    target_compile_options(${target} PRIVATE ${SANITIZER_FLAGS} ${DEFAULT_COMPILER_OPTIONS_AND_WARNINGS})
    target_include_directories(${target} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ../common)
    target_link_libraries(${target} PRIVATE ${SANITIZER_FLAGS} prime Threads::Threads fmt::fmt spdlog::spdlog spdlog::spdlog_header_only)
endforeach()
