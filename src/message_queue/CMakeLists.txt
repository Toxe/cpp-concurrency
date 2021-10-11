add_executable(message_queue
    main.cpp
    message_queue/message_queue.hpp
    supervisor/messages.hpp
    supervisor/supervisor.cpp
    supervisor/supervisor.hpp
    worker/messages.hpp
    worker/worker.cpp
    worker/worker.hpp
)

set_target_properties(message_queue PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(message_queue PUBLIC cxx_std_20)
target_compile_options(message_queue PRIVATE ${SANITIZER_FLAGS} ${DEFAULT_COMPILER_OPTIONS_AND_WARNINGS})
target_include_directories(message_queue PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ../common)
target_link_libraries(message_queue PRIVATE ${SANITIZER_FLAGS} prime Threads::Threads fmt::fmt spdlog::spdlog spdlog::spdlog_header_only)
