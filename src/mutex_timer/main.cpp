#include <chrono>
#include <mutex>
#include <numeric>
#include <thread>
#include <vector>

#include <spdlog/spdlog.h>

#include "mutex_timer.h"
#include "prime.h"

std::mutex mtx;
MutexTimer mutex_timer("lock_guard", "calc_nth_prime");

void calc_nth_prime(int n, std::vector<int>& primes)
{
    int prime = nth_prime(n);

    {
        const auto t0 = std::chrono::steady_clock::now();
        std::lock_guard<std::mutex> lock(mtx);
        mutex_timer.update(t0);
        primes.push_back(prime);
    }
}

int main()
{
    spdlog::set_level(spdlog::level::debug);

    const auto t1 = std::chrono::steady_clock::now();

    std::vector<std::thread> threads;
    std::vector<int> primes;

    for (int n = 30000; n <= 30010; ++n)
        threads.emplace_back(calc_nth_prime, n, std::ref(primes));

    for (auto& t : threads)
        t.join();

    const auto t2 = std::chrono::steady_clock::now();
    const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

    spdlog::info("sum of primes = {}", std::accumulate(primes.begin(), primes.end(), 0));
    spdlog::info("duration: {}ms", ms.count());

    mutex_timer.summary();
}
