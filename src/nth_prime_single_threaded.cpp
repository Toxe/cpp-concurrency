#include <chrono>
#include <iostream>

#include "common/prime.h"

int calc_nth_prime(int n)
{
    const auto t1 = std::chrono::high_resolution_clock::now();
    int prime = nth_prime(n);
    const auto t2 = std::chrono::high_resolution_clock::now();
    const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

    std::cout << "prime #" << n << ": " << prime << " (" << ms.count() << "ms)\n";

    return prime;
}

int main()
{
    const auto t1 = std::chrono::high_resolution_clock::now();

    int sum_of_primes = 0;

    for (int n = 30000; n <= 30010; ++n)
        sum_of_primes += calc_nth_prime(n);

    const auto t2 = std::chrono::high_resolution_clock::now();
    const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

    std::cout << "sum of primes = " << sum_of_primes << '\n';
    std::cout << "duration: " << ms.count() << "ms\n";
}
