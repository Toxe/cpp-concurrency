#include <chrono>
#include <condition_variable>
#include <future>
#include <mutex>
#include <numeric>
#include <queue>
#include <string>
#include <thread>
#include <vector>

#include <fmt/core.h>
#include <spdlog/spdlog.h>

#include "common/prime.h"

using namespace std::chrono_literals;

std::mutex log_mutex;
std::mutex data_mutex;
std::condition_variable cv;
std::queue<int> queue;
bool running = true;

void log(const std::string& s)
{
    std::lock_guard<std::mutex> lock(log_mutex);
    spdlog::info(s);
}

void producer()
{
    log(fmt::format("producer: starting"));

    for (int n = 30000; n <= 30010; ++n) {
        {
            std::lock_guard<std::mutex> lock(data_mutex);
            log(fmt::format("producer: providing value {}...", n));
            queue.push(n);
        }

        cv.notify_one();
    }

    {
        std::unique_lock<std::mutex> lock(data_mutex);
        log(fmt::format("producer: finished, waiting until queue is empty (queue size now: {})", queue.size()));
        cv.wait(lock, [] { return queue.empty(); });
        log(fmt::format("producer: queue is empty, signaling workers to stop"));
        running = false;
    }

    cv.notify_all();

    log(fmt::format("producer: stopping"));
}

void worker(int id, std::vector<int>& primes)
{
    log(fmt::format("worker {}: started", id));

    while (true) {
        int nth;

        {
            std::unique_lock<std::mutex> lock(data_mutex);
            cv.wait(lock, [] { return !queue.empty() || !running; });

            if (!running)
                break;

            nth = queue.front();
            queue.pop();
            log(fmt::format("worker {}: received value {}, queue size: {}", id, nth, queue.size()));
        }

        int prime = nth_prime(nth);
        log(fmt::format("worker {}: prime number {} is: {}", id, nth, prime));

        {
            std::lock_guard<std::mutex> lock(data_mutex);
            primes.push_back(prime);
        }

        // signal other workers to run or the producer to check if the queue is empty
        cv.notify_one();
    }

    log(fmt::format("worker {}: stopping", id));
}

int main()
{
    const auto t1 = std::chrono::high_resolution_clock::now();

    std::vector<std::thread> workers;
    std::vector<int> primes;

    for (int i = 0; i < 3; ++i)
        workers.emplace_back(worker, i, std::ref(primes));

    producer();

    log(fmt::format("producer finished"));
    log(fmt::format("waiting for workers to finish"));

    for (auto& t : workers)
        t.join();

    const auto t2 = std::chrono::high_resolution_clock::now();
    const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

    log(fmt::format("workers finished"));
    log(fmt::format("quit"));

    spdlog::info("sum of primes = {}", std::accumulate(primes.begin(), primes.end(), 0));
    spdlog::info("duration: {}ms", ms.count());
}
