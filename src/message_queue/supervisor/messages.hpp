#pragma once

#include <variant>

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
