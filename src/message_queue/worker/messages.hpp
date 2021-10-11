#pragma once

#include <variant>

struct WorkerCalculate {
    int nth_prime;
};

struct WorkerQuit {};

using WorkerMessage = std::variant<WorkerCalculate, WorkerQuit>;
