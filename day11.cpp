#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <cstdint>
#include <algorithm>
#include <unordered_map>

using NumberType = uint64_t;

const NumberType POW10[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};

inline int count_digits(NumberType n) {
    if (n == 0) return 1;
    if (n < 10) return 1;
    if (n < 100) return 2;
    if (n < 1000) return 3;
    if (n < 10000) return 4;
    if (n < 100000) return 5;
    if (n < 1000000) return 6;
    return floor(log10(n)) + 1;
}

inline std::pair<NumberType, NumberType> split_number_fast(NumberType n, int digits) {
    int half = digits / 2;
    NumberType divisor = (half <= 8) ? POW10[half] : pow(10, half);
    return std::make_pair(n / divisor, n % divisor);
}

uint64_t process_numbers(const std::vector<NumberType>& numbers, int steps) {
    std::unordered_map<NumberType, uint64_t> current;
    for (NumberType num : numbers) {
        current[num]++;
    }

    std::unordered_map<NumberType, uint64_t> next;
    next.reserve(current.size() * 2);

    for (int step = 0; step < steps; ++step) {
        next.clear();

        for (auto [num, n] : current) {
            if (num == 0) {
                next[1] += n;
                continue;
            }

            int digits = count_digits(num);
            if (digits % 2 == 0) {
                auto split = split_number_fast(num, digits);
                next[split.first] += n;
                next[split.second] += n;
            } else {
                if (num <= UINT64_MAX / 2024) {
                    next[num * 2024] += n;
                } else {
                    std::cout << "Overflow for number " << num << std::endl;
                }
            }
        }
        std::swap(current, next);
    }

    uint64_t count = 0;
    for (auto [num, n] : current) {
        count += n;
    }
    return count;
}

int main() {
    std::string path = "/home/elisabeth/CLionProjects/Advent-of-Code-2024/";
    std::ifstream input_file(path + "input_day11.txt");
    if (!input_file.is_open()) {
        std::cout << "Could not open file" << std::endl;
        return 1;
    }

    std::vector<NumberType> initial_numbers;
    NumberType number;
    while (input_file >> number) {
        initial_numbers.push_back(number);
    }

    // First get all numbers after 25 steps
    auto result = process_numbers(initial_numbers, 25);
    std::cout << "After 25 steps: " << result << " numbers\n";

    auto result2 = process_numbers(initial_numbers, 75);
    std::cout << "After 75 steps: " << result2 << " numbers\n";


    return 0;

    // Define the step sizes and batch sizes for each phase

    std::cout << "\nFinal count after 75 steps: "  << std::endl;

    return 0;
}