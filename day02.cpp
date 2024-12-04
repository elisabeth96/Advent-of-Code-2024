//
// Created by elisabeth on 04.12.24.
//
#include <fstream>
#include <iostream>
#include <vector>

bool meets_criteria(std::vector<int> line) {
    bool increasing = true;
    bool decreasing = true;
    for (int i = 1; i < line.size(); i++) {
        if (line[i] - line[i - 1] >= 0) {
            decreasing = false;
        }
        if (line[i] - line[i - 1] <= 0) {
            increasing = false;
        }
        if (std::abs(line[i] - line[i - 1]) > 3) {
            increasing = false;
            decreasing = false;
            break;
        }
    }
    return increasing || decreasing;
}


int main() {
    std::string path = "/home/elisabeth/CLionProjects/Advent-of-Code-2024/";
    std::vector<std::string> input;
    std::fstream input_file(path + "input_day02.txt");
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

    //each line in input is a string consisting of multiple numbers separated by a space
    //split the string into the individual numbers and save them in a vector per line
    std::vector<std::vector<int>> numbers;
    for (auto& line : input) {
        std::vector<int> line_numbers;
        int pos_delim = 0;
        while (pos_delim != std::string::npos && pos_delim < line.size()) {
            int next_delim = line.find(' ', pos_delim + 1);
            if (next_delim == std::string::npos) {
                line_numbers.push_back(std::stoi(line.substr(pos_delim)));
                break;
            }
            line_numbers.push_back(std::stoi(line.substr(pos_delim, next_delim - pos_delim)));
            pos_delim = next_delim + 1;
        }
        numbers.push_back(line_numbers);
    }

    //first part of the task
    // check for each line if it is strictly increasing or decreasing with a maximum difference of 3
    // count the number of lines that fulfill this condition
    /*int count = 0;
    for (auto& line : numbers) {
        bool increasing = true;
        bool decreasing = true;
        for (int i = 1; i < line.size(); i++) {
            if (line[i] - line[i - 1] >= 0) {
                decreasing = false;
            }
            if (line[i] - line[i - 1] <= 0) {
                increasing = false;
            }
            if (std::abs(line[i] - line[i - 1]) > 3) {
                increasing = false;
                decreasing = false;
                break;
            }
        }
        if (increasing || decreasing) {
            count++;
        }
    }
    std::cout << "The solution to part 1 is: " << count << std::endl;*/

    //second part of the task
    int count = 0;
    for (auto& line : numbers) {
        if (meets_criteria(line)) {
            count++;
        } else {
            // check if criteria is met if one number is removed
            for (int i = 0; i < line.size(); i++) {
                std::vector<int> new_line;
                for (int j = 0; j < line.size(); j++) {
                    if (j != i) {
                        new_line.push_back(line[j]);
                    }
                }
                if (meets_criteria(new_line)) {
                    count++;
                    break;
                }
            }
        }
    }
    std::cout << "The solution to part 2 is: " << count << std::endl;
}