#include <run_with_time_limit.h>
#include <vector>
#include <atomic>
#include <thread>
#include <chrono>


void run_with_time_limit(AlgoFunction algo, std::vector<int>& primes, int MAX_NUM, int MAX_TIME) {
    std::atomic<bool> stopFlag = false;

    std::thread timer([&] {
        std::this_thread::sleep_for(std::chrono::seconds(MAX_TIME));
        stopFlag.store(true, std::memory_order_relaxed);
    });

    algo(primes, MAX_NUM, stopFlag);

    timer.join();
}