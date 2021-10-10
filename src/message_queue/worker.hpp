#pragma once

#include <thread>

#include "message_queue.hpp"
#include "messages.hpp"

class Worker {
    bool running_;

    const int id_;
    std::thread thread_;

    MessageQueue<WorkerMessage>& worker_message_queue_;
    MessageQueue<SupervisorMessage>& supervisor_message_queue_;

    void main();

    void handle_message(WorkerCalculate&& calculate);
    void handle_message(WorkerQuit&&);

public:
    Worker(const int id, MessageQueue<WorkerMessage>& worker_message_queue, MessageQueue<SupervisorMessage>& supervisor_message_queue);
    Worker(Worker&& other);
    ~Worker();

    [[nodiscard]] int id() const { return id_; }

    void run();
    void join();
};
