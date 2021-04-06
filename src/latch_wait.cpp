#include <chrono>
#include <iostream>
#include <latch>
#include <mutex>
#include <numeric>
#include <thread>
#include <vector>

#include <spdlog/spdlog.h>

#include "common/prime.h"

std::mutex mtx;

void calc_nth_prime(int n, std::vector<int>& primes, std::latch& latch)
{
    latch.wait();

    int prime = nth_prime(n);

    {
        std::lock_guard<std::mutex> lock(mtx);
        primes.push_back(prime);
    }
}

int main()
{
    std::latch latch(1);
    std::vector<std::thread> threads;
    std::vector<int> primes;

    for (int n = 30000; n <= 30010; ++n)
        threads.emplace_back(calc_nth_prime, n, std::ref(primes), std::ref(latch));

    fmt::print("Press enter to start...");
    std::cin.get();

    const auto t1 = std::chrono::high_resolution_clock::now();

    latch.count_down();

    for (auto& t : threads)
        t.join();

    const auto t2 = std::chrono::high_resolution_clock::now();
    const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

    spdlog::info("sum of primes = {}", std::accumulate(primes.begin(), primes.end(), 0));
    spdlog::info("duration: {}ms", ms.count());
}
