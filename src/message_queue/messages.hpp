#pragma once

#include <variant>

// Supervisor
// struct SupervisorCalculationRequest {
//     int first;
//     int last;
// };

struct SupervisorCalculationResults {
    int nth_prime;
    int prime;
};

struct SupervisorQuit {};

using SupervisorMessage = std::variant<SupervisorCalculationResults, SupervisorQuit>;
// using SupervisorMessage = std::variant<SupervisorCalculationRequest, SupervisorCalculationResults, SupervisorQuit>;

// Worker
struct WorkerCalculate {
    int nth_prime;
};

struct WorkerQuit {};

using WorkerMessage = std::variant<WorkerCalculate, WorkerQuit>;
