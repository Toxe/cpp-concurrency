add_executable(message_queue_poll
    main_poll.cpp
    message_queue/message_queue.hpp
    supervisor/messages.hpp
    supervisor/supervisor.cpp
    supervisor/supervisor.hpp
    worker/messages.hpp
    worker/worker.cpp
    worker/worker.hpp
)

add_executable(message_queue_wait_until_finished
    main_wait_until_finished.cpp
    message_queue/message_queue.hpp
    supervisor/messages.hpp
    supervisor/supervisor.cpp
    supervisor/supervisor.hpp
    worker/messages.hpp
    worker/worker.cpp
    worker/worker.hpp
)

set_target_properties(message_queue_poll PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(message_queue_poll PUBLIC cxx_std_20)
target_compile_options(message_queue_poll PRIVATE ${SANITIZER_FLAGS} ${DEFAULT_COMPILER_OPTIONS_AND_WARNINGS})
target_include_directories(message_queue_poll PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ../common)
target_link_libraries(message_queue_poll PRIVATE ${SANITIZER_FLAGS} prime Threads::Threads fmt::fmt spdlog::spdlog spdlog::spdlog_header_only)

set_target_properties(message_queue_wait_until_finished PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(message_queue_wait_until_finished PUBLIC cxx_std_20)
target_compile_options(message_queue_wait_until_finished PRIVATE ${SANITIZER_FLAGS} ${DEFAULT_COMPILER_OPTIONS_AND_WARNINGS})
target_include_directories(message_queue_wait_until_finished PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ../common)
target_link_libraries(message_queue_wait_until_finished PRIVATE ${SANITIZER_FLAGS} prime Threads::Threads fmt::fmt spdlog::spdlog spdlog::spdlog_header_only)
