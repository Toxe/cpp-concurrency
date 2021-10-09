#include <atomic>
#include <chrono>
#include <thread>
#include <vector>

#include <spdlog/spdlog.h>

#include "prime.h"

void calc_nth_prime(int n, std::atomic<int>& sum_of_primes)
{
    sum_of_primes += nth_prime(n);
}

int main()
{
    const auto t1 = std::chrono::high_resolution_clock::now();

    std::vector<std::thread> threads;
    std::atomic<int> sum_of_primes = 0;

    for (int n = 30000; n <= 30010; ++n)
        threads.emplace_back(calc_nth_prime, n, std::ref(sum_of_primes));

    for (auto& t : threads)
        t.join();

    const auto t2 = std::chrono::high_resolution_clock::now();
    const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

    spdlog::info("sum of primes = {}", sum_of_primes);
    spdlog::info("duration: {}ms", ms.count());
}
