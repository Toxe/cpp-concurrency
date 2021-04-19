#include <thread>

#include <fmt/core.h>
#include <fmt/ostream.h>
#include <spdlog/spdlog.h>

#include "common/prime.h"

int calc_nth_prime(int n)
{
    spdlog::info("{}: calc prime {}...", std::this_thread::get_id(), n);
    int prime = nth_prime(n);
    spdlog::info("{}: prime {} is {}", std::this_thread::get_id(), n, prime);
    return prime;
}

struct ThreadA {
    int (*f_)(int);
    int n_;
    std::thread t_;

    ThreadA(int (*f)(int), int n) : f_{f}, n_{n} {
        spdlog::info("{}: ThreadA constructor", std::this_thread::get_id());
    };

    ~ThreadA() {
        spdlog::info("{}: ThreadA destructor", std::this_thread::get_id());

        if (joinable())
            join();
    }

    void run() {
        spdlog::info("{}: ThreadA::run", std::this_thread::get_id());
        t_ = std::thread(f_, n_);
    }

    void join() {
        auto id = t_.get_id();
        spdlog::info("{}: ThreadA::join {}", std::this_thread::get_id(), id);
        t_.join();
        spdlog::info("{}: joined {}", std::this_thread::get_id(), id);
    }

    bool joinable() {
        bool b = t_.joinable();
        spdlog::info("{}: ThreadA::joinable {} --> {}", std::this_thread::get_id(), t_.get_id(), b);
        return b;
    }
};

struct ThreadB {
    int n_;
    std::thread t_;

    ThreadB(int n) : n_{n} {
        spdlog::info("{}: ThreadB constructor", std::this_thread::get_id());
    };

    ~ThreadB() {
        spdlog::info("{}: ThreadB destructor", std::this_thread::get_id());

        if (joinable())
            join();
    }

    int calc() {
        return calc_nth_prime(n_);
    }

    void run() {
        spdlog::info("{}: ThreadB::run", std::this_thread::get_id());
        t_ = std::thread(&ThreadB::calc, this);
    }

    void join() {
        auto id = t_.get_id();
        spdlog::info("{}: ThreadB::join {}", std::this_thread::get_id(), id);
        t_.join();
        spdlog::info("{}: joined {}", std::this_thread::get_id(), id);
    }

    bool joinable() {
        bool b = t_.joinable();
        spdlog::info("{}: ThreadB::joinable {} --> {}", std::this_thread::get_id(), t_.get_id(), b);
        return b;
    }
};

int main()
{
    ThreadA ta1(&calc_nth_prime, 30000);
    ta1.run();

    {
        ThreadA ta2(&calc_nth_prime, 30001);
        ta2.run();
    }

    ThreadB tb(30002);
    tb.run();

    calc_nth_prime(30003);
    calc_nth_prime(30004);

    ta1.join();
    tb.join();

    spdlog::info("{}: done", std::this_thread::get_id());
}
