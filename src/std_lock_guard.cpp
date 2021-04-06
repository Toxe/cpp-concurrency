#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <tuple>
#include <vector>

#include "common/prime.h"

std::mutex mtx;

void calc_nth_prime(int n, std::vector<std::tuple<int, int, std::chrono::milliseconds>>& primes)
{
    const auto t1 = std::chrono::high_resolution_clock::now();
    int prime = nth_prime(n);
    const auto t2 = std::chrono::high_resolution_clock::now();
    const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

    {
        std::lock_guard<std::mutex> lock(mtx);
        primes.emplace_back(n, prime, ms);
    }
}

int main()
{
    const auto t1 = std::chrono::high_resolution_clock::now();

    std::vector<std::thread> threads;
    std::vector<std::tuple<int, int, std::chrono::milliseconds>> primes;

    for (int n = 30000; n <= 30010; ++n)
        threads.emplace_back(calc_nth_prime, n, std::ref(primes));

    for (auto& t : threads)
        t.join();

    const auto t2 = std::chrono::high_resolution_clock::now();
    const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

    int sum_of_primes = 0;

    for (auto [n, prime, ms] : primes) {
        sum_of_primes += prime;
        std::cout << "prime #" << n << ": " << prime << " (" << ms.count() << "ms)\n";
    }

    std::cout << "sum of primes = " << sum_of_primes << '\n';
    std::cout << "duration: " << ms.count() << "ms\n";
}
