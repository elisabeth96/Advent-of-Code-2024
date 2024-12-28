//
// Created by elisabeth on 27.12.24.
//
#include <bitset>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

// get all possible combinations of 0 and 1 with a total lenght of n
std::vector<std::string> get_combinations(int n) {
    std::vector<std::string> combinations;
    for (int i = 0; i < pow(2, n); i++) {
        std::string binary = std::bitset<64>(i).to_string();
        int pos = 0;
        while (binary[pos] == '0') {
            pos++;
        }
        std::string combination;
        if (binary.size() - pos < n) {
            for (int j = 0; j < n - binary.size() + pos; j++) {
                combination += '0';
            }
        }
        for (int j = pos; j < binary.size(); j++) {
            combination += binary[j];
        }
        combinations.push_back(combination);
    }
    return combinations;
}

// get all possible combinations of 0, 1 and 2 with a total lenght of n
void generate_combinations(int n, std::string current, std::vector<std::string>& result) {
    if (current.length() == n) {
        result.push_back(current);
        return;
    }

    generate_combinations(n, current + "0", result);
    generate_combinations(n, current + "1", result);
    generate_combinations(n, current + "2", result);
}

std::vector<std::string> get_all_combinations(int n) {
    std::vector<std::string> result;
    generate_combinations(n, "", result);
    return result;
}

// given two integer numbers, concatenate them into one
long long combine_numbers(long long num1, long long num2) {
    return num1 * pow(10, std::to_string(num2).size()) + num2;
}

int main() {
    std::string path = "/home/elisabeth/CLionProjects/Advent-of-Code-2024/";
    std::vector<std::string> input;
    std::fstream input_file(path + "input_day07.txt");
    if (!input_file.is_open()) {
        std::cout << "Could not open file" << std::endl;
        return 1;
    }
    while (!input_file.eof()) {
        std::string line;
        std::getline(input_file, line);
        input.push_back(line);
    }
    input_file.close();

    std::vector<std::vector<long long>> numbers;
    for (auto &line: input) {
        std::vector<long long> line_numbers;
        // find first number
        int pos = 0;
        int delim = line.find(": ", pos);
        line_numbers.push_back(std::stoul(line.substr(pos, delim)));
        pos = delim + 2;
        // find all other numbers
        while (line.find(" ", pos) != std::string::npos) {
            delim = line.find(" ", pos);
            line_numbers.push_back(std::stoul(line.substr(pos, delim)));
            pos = delim + 1;
        }
        line_numbers.push_back(std::stoul(line.substr(pos)));
        numbers.push_back(line_numbers);
    }

    // first part of the task
    /*long long sum = 0;
    for (auto &line: numbers) {
        long long result = line[0];
        std::vector<std::string> combinations = get_combinations(line.size() - 2);
        for (auto &combination: combinations) {
            long long res = line[1];
            for (int i = 0; i < combination.size(); i++) {
                if (combination[i] == '0') {
                    res += line[i + 2];
                } else {
                    res *= line[i + 2];
                }
                if (res > result) {
                    break;
                }
            }
            if (res == result){
                sum += result;
                break;
            }
        }
    }
    std::cout << "Solution for part 1: " << sum << std::endl;*/

    // second part of the task
    long long sum = 0;
    for (auto &line: numbers) {
        long long result = line[0];
        std::vector<std::string> combinations = get_all_combinations(line.size() - 2);
        for (auto &combination: combinations) {
            long long res = line[1];
            for (int i = 0; i < combination.size(); i++) {
                if (combination[i] == '0') {
                    res += line[i + 2];
                } else if (combination[i] == '1') {
                    res *= line[i + 2];
                } else {
                    res = combine_numbers(res, line[i + 2]);
                }
                if (res > result) {
                    break;
                }
            }
            if (res == result){
                sum += result;
                break;
            }
        }

    }
    std::cout << "Solution for part 2: " << sum << std::endl;
}