#include <yaml-cpp/yaml.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <filesystem>
#include "run_with_time_limit.h"
#include "algos/prime_algorithms.h"

// Parse input from string -> func
const std::unordered_map<std::string, AlgoFunction> algoMap = {
    {"brute_force", bruteForce},
    {"optimized_brute_force", optimizedBruteForce}
};

struct NamedAlgo {
    std::string name;
    AlgoFunction func;
};

int main() {
    YAML::Node config = YAML::LoadFile("../config/config.yaml");
    YAML::Node algos = config["algorithms"];
    const int MAX_NUM = config["constants"]["max_number"].as<int>();
    const int MAX_TIME = config["constants"]["max_time"].as<int>();

    std::vector<NamedAlgo> algorithms;

    // Validate config.yaml
    for (auto it = algos.begin(); it != algos.end(); ++it) {
        std::string algoName = it->first.as<std::string>();
        
        if (algoMap.find(algoName) == algoMap.end()) {
            std::cerr << "Algorithm `" << algoName << "` not found in internal algorithm map" << std::endl;
            std::cerr << "To correct add algorithm to algo map in main.cpp" << std::endl;
            return 1;
        }
        if (it->second.as<bool>()) {
            algorithms.push_back({algoName, algoMap.at(algoName)});
        }
    }

    // Creating output folder
    std::string dir = "../output";

    if (!std::filesystem::exists(dir)) {
        if (!std::filesystem::create_directory(dir)) {
            std::cerr << "Failed to create directory!\n";
            return 1;
        }
    }

    // Run algos
    for (NamedAlgo& algorithm: algorithms) { 
        // Allocate reserve later
        std::vector<int> primes;
        primes.reserve(MAX_NUM / 2);

        // Call the algorithm with time constraint
        run_with_time_limit(algorithm.func, primes, MAX_NUM, MAX_TIME);

        std::string algoName = algorithm.name;
        // Writing to the file and outputing the results
        // Prepare output file
        std::string outputFileName = "../output/" + algoName + ".txt";
        std::ofstream outFile(outputFileName);

        // Debug path
        if (!outFile) {
            std::cerr << "Error opening file `" << outputFileName << "` for writing";
            return 1;
        }

        for (size_t i = 0; i < primes.size(); ++i) {
            outFile << primes[i] << '\n';
        }
        
        outFile.close();
    }
}