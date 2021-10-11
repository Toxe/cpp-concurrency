#pragma once

#include <condition_variable>
#include <mutex>
#include <thread>
#include <vector>

#include "message_queue/message_queue.hpp"
#include "messages.hpp"
#include "worker/messages.hpp"
#include "worker/worker.hpp"

class Supervisor {
    std::mutex mtx_;
    std::condition_variable cv_wait_until_finished_;

    bool running_;

    std::thread thread_;

    int num_threads_;
    std::vector<Worker> workers_;

    MessageQueue<WorkerMessage> worker_message_queue_;
    MessageQueue<SupervisorMessage> supervisor_message_queue_;

    int waiting_for_results_ = 0;

    void main();

    void handle_message(SupervisorCalculationResults&& calculation_results);
    void handle_message(SupervisorQuit&&);

    void start_workers();
    void shutdown_workers();
    void clear_message_queues();

public:
    Supervisor(const int num_threads);
    ~Supervisor();

    void run(const int num_threads);
    void join();

    void restart(const int num_threads);
    void shutdown();

    void calc_primes(const int first, const int last);

    [[nodiscard]] bool has_all_results();
    void wait_until_finished();
};
