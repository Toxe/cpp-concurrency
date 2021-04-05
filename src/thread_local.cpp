#include <chrono>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>
#include <vector>

int global_counter = 0;
thread_local int local_counter = 0;

std::mutex mtx;

void do_something(int n)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(3, 5);

    for (int i = 0; i < 10; ++i) {
        int ms = dist(gen) * 10; // 30-50 ms

        std::this_thread::sleep_for(std::chrono::milliseconds{ms});

        {
            std::lock_guard<std::mutex> lock(mtx);
            std::cout << std::this_thread::get_id() << " Thread #" << n << " slept for " << ms << " ms. global_counter: " << ++global_counter << ", local_counter: " << ++local_counter << '\n';
        }
    }
}

int main()
{
    std::vector<std::thread> threads;

    for (int i = 0; i < 10; ++i)
        threads.emplace_back(do_something, i);

    for (auto& t : threads)
        t.join();

    std::cout << "Done. global_counter: " << global_counter << ", local_counter: " << local_counter << '\n';
}
