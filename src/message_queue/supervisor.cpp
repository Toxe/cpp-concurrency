#include "supervisor.hpp"

#include <cassert>

#include <spdlog/spdlog.h>

Supervisor::Supervisor(const int num_threads)
    : running_{false}
{
    run(num_threads);
}

Supervisor::~Supervisor()
{
    join();
}

void Supervisor::run(const int num_threads)
{
    num_threads_ = num_threads;
    thread_ = std::thread(&Supervisor::main, this);
}

void Supervisor::join()
{
    if (thread_.joinable())
        thread_.join();
}

void Supervisor::main()
{
    spdlog::info("supervisor: starting");

    start_workers();

    auto visitor = [&](auto&& msg) { handle_message(std::move(msg)); };
    running_ = true;

    while (running_)
        std::visit(visitor, supervisor_message_queue_.wait_for_message());

    clear_message_queues();
    shutdown_workers();

    spdlog::info("supervisor: stopping");
}

void Supervisor::restart(const int num_threads)
{
    shutdown();
    run(num_threads);
}

void Supervisor::shutdown()
{
    supervisor_message_queue_.send(SupervisorQuit{});
    join();
}

void Supervisor::calc_primes(const int first, const int last)
{
    spdlog::info("supervisor: calculate primes {} to {}", first, last);

    std::unique_lock<std::mutex> lock(mtx_);

    for (int nth_prime = first; nth_prime <= last; ++nth_prime) {
        worker_message_queue_.send(WorkerCalculate{nth_prime});
        ++waiting_for_results_;
    }

    spdlog::info("supervisor: sent {} WorkerCalculate messages", waiting_for_results_);
}

// void Supervisor::handle_message(SupervisorCalculationRequest&& calculation_request)
// {
//     spdlog::info("supervisor: received message SupervisorCalculationRequest, first={}, last={}", calculation_request.first, calculation_request.last);

//     for (int nth_prime = calculation_request.first; nth_prime <= calculation_request.last; ++nth_prime) {
//         worker_message_queue_.send(WorkerCalculate{nth_prime});
//         ++waiting_for_results_;
//     }

//     spdlog::info("supervisor: sent {} WorkerCalculate messages", waiting_for_results_);
// }

void Supervisor::handle_message(SupervisorCalculationResults&& calculation_results)
{
    spdlog::info("supervisor: received message SupervisorCalculationResults, nth_prime={}, prime={}", calculation_results.nth_prime, calculation_results.prime);

    std::unique_lock<std::mutex> lock(mtx_);

    if (--waiting_for_results_ == 0)
        spdlog::info("supervisor: all results received");

    assert(waiting_for_results_ >= 0);
}

void Supervisor::handle_message(SupervisorQuit&&)
{
    spdlog::info("supervisor: received message SupervisorQuit");

    running_ = false;
}

void Supervisor::start_workers()
{
    spdlog::info("supervisor: starting workers");

    workers_.reserve(static_cast<std::size_t>(num_threads_));

    for (int id = 0; id < num_threads_; ++id) {
        workers_.emplace_back(id, worker_message_queue_, supervisor_message_queue_);
        workers_.back().run();
    }
}

void Supervisor::shutdown_workers()
{
    spdlog::info("supervisor: signaling workers to stop");

    for (int i = 0; i < std::ssize(workers_); ++i)
        worker_message_queue_.send(WorkerQuit{});

    spdlog::info("supervisor: waiting for workers to finish");

    for (auto& w : workers_)
        w.join();

    workers_.clear();
}

void Supervisor::clear_message_queues()
{
    supervisor_message_queue_.clear();
    worker_message_queue_.clear();

    waiting_for_results_ = 0;
}

bool Supervisor::has_all_results()
{
    std::unique_lock<std::mutex> lock(mtx_);

    return waiting_for_results_ == 0;
}
