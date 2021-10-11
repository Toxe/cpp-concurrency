#include <spdlog/spdlog.h>

#include "message_queue/message_queue.hpp"
#include "supervisor/supervisor.hpp"

int main()
{
    Supervisor supervisor(4);
    supervisor.calc_primes(30000, 30010);
    supervisor.wait_until_finished();
    supervisor.shutdown();

    spdlog::info("quit");
}
