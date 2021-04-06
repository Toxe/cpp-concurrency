#include <chrono>
#include <condition_variable>
#include <future>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

#include <fmt/core.h>
#include <spdlog/spdlog.h>

#include "common/prime.h"

using namespace std::chrono_literals;

std::mutex log_mutex;
std::mutex data_mutex;
std::condition_variable cv;
std::queue<int> queue;

void log(const std::string& s)
{
    std::lock_guard<std::mutex> lock(log_mutex);
    spdlog::info(s);
}

void producer(int id)
{
    log(fmt::format("started producer {}", id));

    for (int i = 0; i < 5; ++i) {
        const int value = 10 * id + i;

        {
            std::lock_guard<std::mutex> lock(data_mutex);
            log(fmt::format("providing value {}...", value));
            queue.push(value);
        }

        cv.notify_one();
        std::this_thread::sleep_for(50ms);
    }

    log(fmt::format("stopping producer {}", id));
}

void consumer(int id)
{
    log(fmt::format("started consumer {}", id));

    while (true) {
        int value;

        {
            std::unique_lock<std::mutex> lock(data_mutex);
            cv.wait(lock, []{ return !queue.empty(); });
            value = queue.front();
            queue.pop();
            log(fmt::format("consumer {} received value {}", id, value));
        }

        std::this_thread::sleep_for(10ms);
    }

    log(fmt::format("stopping consumer {}", id));
}

int main()
{
    auto prod1 = std::async(std::launch::async, producer, 1);
    auto prod2 = std::async(std::launch::async, producer, 2);

    auto cons1 = std::async(std::launch::async, consumer, 1);
    auto cons2 = std::async(std::launch::async, consumer, 2);
    auto cons3 = std::async(std::launch::async, consumer, 3);
}
