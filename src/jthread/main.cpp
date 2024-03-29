#include <chrono>
#include <mutex>
#include <numeric>
#include <thread>
#include <vector>

#include <spdlog/spdlog.h>

#include "prime.h"

std::mutex mtx;

void calc_nth_prime(int n, std::vector<int>& primes)
{
    int prime = nth_prime(n);

    {
        std::lock_guard<std::mutex> lock(mtx);
        primes.push_back(prime);
    }
}

int main()
{
    const auto t1 = std::chrono::high_resolution_clock::now();

    std::vector<int> primes;

    {
        std::vector<std::jthread> threads;

        for (int n = 30000; n <= 30010; ++n)
            threads.emplace_back(calc_nth_prime, n, std::ref(primes));
    }

    const auto t2 = std::chrono::high_resolution_clock::now();
    const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

    spdlog::info("sum of primes = {}", std::accumulate(primes.begin(), primes.end(), 0));
    spdlog::info("duration: {}ms", ms.count());
}
