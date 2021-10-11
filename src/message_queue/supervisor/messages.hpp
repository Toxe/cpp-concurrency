#pragma once

#include <variant>

struct SupervisorCalculationResults {
    int nth_prime;
    int prime;
};

struct SupervisorQuit {};

using SupervisorMessage = std::variant<SupervisorCalculationResults, SupervisorQuit>;
