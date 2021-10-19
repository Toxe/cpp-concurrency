#include <chrono>
#include <stop_token>
#include <thread>
#include <vector>

#include <spdlog/spdlog.h>

#include "prime.h"

void calc_primes(std::stop_token st)
{
    spdlog::info("calc_primes: started");

    std::vector<int> primes;
    int n = 30000;

    while (!st.stop_requested())
        primes.push_back(nth_prime(n++));

    spdlog::info("calc_primes: stop requested, calculated {} primes", primes.size());
}

int main()
{
    std::jthread thread(calc_primes);

    spdlog::info("started thread, sleeping for 3 seconds...");
    std::this_thread::sleep_for(std::chrono::seconds(3));
    spdlog::info("done, requesting thread to stop...");

    // note: no need to call request_stop(), this happens automatically at the end of this scope
    // thread.request_stop();

    spdlog::info("quit");
}
