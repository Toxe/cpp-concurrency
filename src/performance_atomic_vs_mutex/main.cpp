#include <atomic>
#include <chrono>
#include <mutex>
#include <thread>

#include <spdlog/spdlog.h>

constexpr int max_counter = 10'000'000;

std::chrono::milliseconds measure(void (*func)())
{
    const auto t1 = std::chrono::high_resolution_clock::now();

    func();

    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - t1);
}

void atomic_no_thread()
{
    std::atomic<int> counter = 0;

    for (int i = 0; i < max_counter; ++i)
        ++counter;
}

void atomic_one_thread()
{
    std::atomic<int> counter = 0;

    std::thread t([&] {
        while (counter < max_counter)
            ;
    });

    for (int i = 0; i < max_counter; ++i)
        ++counter;

    t.join();
}

void mutex_no_thread()
{
    std::mutex mtx;
    int counter = 0;

    for (int i = 0; i < max_counter; ++i) {
        std::lock_guard<std::mutex> lock(mtx);
        ++counter;
    }
}

void mutex_one_thread()
{
    std::mutex mtx;
    int counter = 0;

    std::thread t([&] {
        while (true) {
            std::lock_guard<std::mutex> lock(mtx);

            if (counter >= max_counter)
                break;
        }
    });

    for (int i = 0; i < max_counter; ++i) {
        std::lock_guard<std::mutex> lock(mtx);
        ++counter;
    }

    t.join();
}

int main()
{
    const auto ms1 = measure(atomic_no_thread);
    const auto ms2 = measure(atomic_one_thread);
    const auto ms3 = measure(mutex_no_thread);
    const auto ms4 = measure(mutex_one_thread);

    spdlog::info("atomic  (no thread): {}ms", ms1.count());
    spdlog::info("atomic (one thread): {}ms", ms2.count());
    spdlog::info("mutex   (no thread): {}ms", ms3.count());
    spdlog::info("mutex  (one thread): {}ms", ms4.count());
}
