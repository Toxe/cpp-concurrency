#include "supervisor.hpp"

#include <cassert>

#include <spdlog/spdlog.h>

Supervisor::Supervisor(const int number_of_worker_threads)
{
    run(number_of_worker_threads);
}

Supervisor::~Supervisor()
{
    join();
}

void Supervisor::run(const int number_of_worker_threads)
{
    number_of_worker_threads_ = number_of_worker_threads;
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

void Supervisor::restart(const int number_of_worker_threads)
{
    shutdown();
    run(number_of_worker_threads);
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
        ++number_of_outstanding_results_;
    }

    spdlog::info("supervisor: sent {} WorkerCalculate messages", number_of_outstanding_results_);
}

void Supervisor::handle_message(SupervisorCalculationResults&& calculation_results)
{
    spdlog::info("supervisor: received message SupervisorCalculationResults, nth_prime={}, prime={}", calculation_results.nth_prime, calculation_results.prime);

    std::unique_lock<std::mutex> lock(mtx_);

    if (--number_of_outstanding_results_ == 0) {
        spdlog::info("supervisor: all results received");
        cv_wait_until_finished_.notify_one();  // notify, in case we are waiting until finished
    }

    assert(number_of_outstanding_results_ >= 0);
}

void Supervisor::handle_message(SupervisorQuit&&)
{
    spdlog::info("supervisor: received message SupervisorQuit");

    running_ = false;
}

void Supervisor::start_workers()
{
    spdlog::info("supervisor: starting workers");

    workers_.reserve(static_cast<std::size_t>(number_of_worker_threads_));

    for (int id = 0; id < number_of_worker_threads_; ++id) {
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

    number_of_outstanding_results_ = 0;
}

bool Supervisor::has_all_results()
{
    std::unique_lock<std::mutex> lock(mtx_);

    return number_of_outstanding_results_ == 0;
}

void Supervisor::wait_until_finished()
{
    spdlog::info("supervisor: wait until finished...");

    std::unique_lock<std::mutex> lock(mtx_);
    cv_wait_until_finished_.wait(lock, [&] { return number_of_outstanding_results_ == 0; });

    spdlog::info("supervisor: finished");
}
