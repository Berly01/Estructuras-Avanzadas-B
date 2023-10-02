#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include "SortingAlgorithms.h"

void save_results(const std::vector<std::pair<int, unsigned long long>>&);

int main() {

    const auto ARRAY_SIZE = { 1000, 5000, 10000, 25000, 50000, 75000, 100000, 
                            250000, 375000, 500000, 650000, 800000, 1000000 };
    const int NUMBER_OF_TESTS{ 5 };
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> random_numbers_generator(0, 1000000);
    std::vector<int> main_array;
    std::vector<std::pair<int, unsigned long long>> execution_times;

    for (const auto& N : ARRAY_SIZE) {
        unsigned long long run_time{ 0 };

        for (int i = 0; i < NUMBER_OF_TESTS; i++) {
            main_array.resize(N);
            std::for_each(main_array.begin(), main_array.end(), [&](auto& value) { value = random_numbers_generator(generator); });

            auto START{ std::chrono::high_resolution_clock::now() };

            SortingAlgorithms<int>::bubble_sort(main_array);

            auto END{ std::chrono::high_resolution_clock::now() };

            auto TOTAL_TIME{ std::chrono::duration_cast<std::chrono::milliseconds>(END - START) };

            run_time += static_cast<unsigned long long>(TOTAL_TIME.count());

            main_array.clear();
        }
        std::cout << "Size: " << N << " complete\n";
        execution_times.emplace_back(std::make_pair(N, run_time / NUMBER_OF_TESTS));
    }
    
    save_results(execution_times);  
    return 0;
}

void save_results(const std::vector<std::pair<int, unsigned long long>>& array) {

    std::ofstream out_file("results.txt", std::ios::out);
    std::stringstream ss;

    for (const auto& i : array) {
        ss << i.first << ' ' << i.second << '\n';
        out_file << ss.str();
        ss.str("");
    }

    out_file.close();
}