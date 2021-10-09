#include "prime.h"

#include <cmath>

int nth_prime(int n)
{
    int number = 1;

    while (n > 0) {
        ++number;

        if (is_prime(number))
            --n;
    }

    return number;
}

bool is_prime(int number)
{
    if (number < 2)
        return false;

    const int root = static_cast<int>(std::sqrt(number));

    for (int i = 2; i <= root; ++i)
        if (number % i == 0)
            return false;

    return true;
}
