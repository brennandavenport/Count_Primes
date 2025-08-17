#pragma once
#include <atomic>
#include <vector>

using AlgoFunction = void(*)(std::vector<int>&, int, std::atomic<bool>&);

void run_with_time_limit(AlgoFunction algo, std::vector<int>& primes, int maxNum, int seconds);