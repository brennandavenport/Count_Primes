#pragma once

#include <vector>
#include <atomic>

void bruteForce(std::vector<int>& primes, int maxNum, std::atomic<bool>& stopFlag);
void optimizedBruteForce(std::vector<int>& primes, int maxNum, std::atomic<bool>& stopFlag);