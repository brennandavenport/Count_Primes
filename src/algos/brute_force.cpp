#include "prime_algorithms.h"
#include <vector>
#include <atomic>

void bruteForce(std::vector<int>& primes, int MAX_NUM, std::atomic<bool>& stopFlag) {
    for (int i = 2; !stopFlag; ++i) {
        bool isPrime = true;
        
        for (int j = 2; j < i; ++j) {
            if (i % j == 0) {
                isPrime = false;
                break;
            }
        }

        if (isPrime) {
            primes.push_back(i);
        }
    }
    return;
}