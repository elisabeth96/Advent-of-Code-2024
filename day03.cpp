//
// Created by elisabeth on 04.12.24.
//
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include <numeric>

int parse_number(std::string num) {
    int number = 0;
    for (int i = 0; i < num.size(); i++) {
        if (!std::isdigit(num[i])) {
            return 0;
        }
        number += (int) (num[i] - '0') * pow(10, num.size() - i - 1);
    }
    return number;
}

int main() {
    std::string path = "/home/elisabeth/CLionProjects/Advent-of-Code-2024/";
    std::vector<std::string> input;
    std::fstream input_file(path + "input_day03.txt");
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

    std::string all = std::accumulate(input.begin(), input.end(), std::string());

    // first part of the task
    long long sum = 0;
    int pos = 0;
    bool task2 = true;

    // delete stuff between don't and do
    if(task2) {
        while (all.find("don't()", pos) != std::string::npos) {
            pos = all.find("don't()", pos);
            int next_delim = all.find("do()", pos);
            all.erase(pos, next_delim - pos + 4);
            pos = 0;
        }
    }

    while (all.find("mul(", pos + 1) != std::string::npos) {
        pos = all.find("mul(", pos + 1);
        int next_delim = all.find(',', pos + 4);
        int next_delim2 = all.find(')', pos + 4);
        int num1 = parse_number(all.substr(pos + 4, next_delim - pos - 4));
        int num2 = parse_number(all.substr(next_delim + 1, next_delim2 - next_delim - 1));
        sum += num1 * num2;
    }

    std::cout << "Solution for part " << (task2 ? "2" : "1") << ": "<< sum << std::endl;
}
