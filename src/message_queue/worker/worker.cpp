#include "worker.hpp"

#include <spdlog/spdlog.h>

#include "prime.h"

Worker::Worker(const int id, MessageQueue<WorkerMessage>& worker_message_queue, MessageQueue<SupervisorMessage>& supervisor_message_queue)
    : running_{false}, id_{id}, worker_message_queue_{worker_message_queue}, supervisor_message_queue_{supervisor_message_queue}
{
}

Worker::Worker(Worker&& other)
    : running_{other.running_}, id_{other.id_}, thread_{std::move(other.thread_)}, worker_message_queue_{other.worker_message_queue_}, supervisor_message_queue_{other.supervisor_message_queue_}
{
}

Worker::~Worker()
{
    join();
}

void Worker::run()
{
    thread_ = std::thread(&Worker::main, this);
}

void Worker::join()
{
    if (thread_.joinable())
        thread_.join();
}

void Worker::main()
{
    spdlog::info("worker {}: started", id_);

    auto visitor = [&](auto&& msg) { handle_message(std::move(msg)); };
    running_ = true;

    while (running_)
        std::visit(visitor, worker_message_queue_.wait_for_message());

    spdlog::info("worker {}: stopping", id_);
}

void Worker::handle_message(WorkerCalculate&& calculate)
{
    spdlog::info("worker {}: received message WorkerCalculate, nth_prime={}", id_, calculate.nth_prime);

    supervisor_message_queue_.send(SupervisorCalculationResults{calculate.nth_prime, nth_prime(calculate.nth_prime)});
}

void Worker::handle_message(WorkerQuit&&)
{
    spdlog::info("worker {}: received message WorkerQuit", id_);

    running_ = false;
}
