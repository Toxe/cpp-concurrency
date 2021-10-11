#include <chrono>
#include <thread>

#include <spdlog/spdlog.h>

#include "message_queue/message_queue.hpp"
#include "supervisor/supervisor.hpp"

int main()
{
    Supervisor supervisor(4);

    supervisor.calc_primes(30000, 30010);

    while (!supervisor.has_all_results()) {
        spdlog::info("waiting...");
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    spdlog::info("done, time to quit");

    supervisor.shutdown();
}
