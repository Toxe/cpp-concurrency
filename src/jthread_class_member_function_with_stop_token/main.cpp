#include <chrono>
#include <stop_token>
#include <thread>
#include <vector>

#include <spdlog/spdlog.h>

#include "prime.h"

class CalcPrimes {
    void thread_main(std::stop_token st);

public:
    void run();
};

void CalcPrimes::thread_main(std::stop_token st)
{
    spdlog::info("CalcPrimes::thread_main started");

    std::vector<int> primes;
    int n = 30000;

    while (!st.stop_requested())
        primes.push_back(nth_prime(n++));

    spdlog::info("CalcPrimes::thread_main stop requested, calculated {} primes", primes.size());
}

void CalcPrimes::run()
{
    std::jthread thread([&](std::stop_token st) { thread_main(st); });

    spdlog::info("CalcPrimes::run started thread, sleeping for 3 seconds...");
    std::this_thread::sleep_for(std::chrono::seconds(3));
    spdlog::info("CalcPrimes::run done, requesting thread to stop...");

    // note: no need to call request_stop(), this happens automatically at the end of this scope
    // thread.request_stop();
}

int main()
{
    CalcPrimes calc_primes;
    calc_primes.run();

    spdlog::info("quit");
}
