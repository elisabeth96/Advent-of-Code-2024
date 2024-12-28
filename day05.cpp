//
// Created by elisabeth on 25.12.24.
//
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>

bool is_valid(std::vector<int>& list, std::map<int, std::set<int>>& ordering) {
    for (int i = 0; i < list.size(); i++) {
        for (int j = 0; j < i; j++) {
            if (ordering[list[i]].find(list[j]) != ordering[list[i]].end()) {
                return false;
            }
        }
    }
    return true;
}

bool make_valid(std::vector<int>& list, std::map<int, std::set<int>>& ordering) {
    for (int i = 0; i < list.size(); i++) {
        for (int j = 0; j < i; j++) {
            if (ordering[list[i]].find(list[j]) != ordering[list[i]].end()) {
                std::swap(list[i], list[j]);
                i = 0;
                j = 0;
            }
        }
    }
    return true;
}

int main() {
    std::string path = "/home/elisabeth/CLionProjects/Advent-of-Code-2024/";
    std::vector<std::string> input;
    std::fstream input_file(path + "input_day05.txt");
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

    std::map<int, std::set<int>> ordering;
    std::vector<std::vector<int>> lists;
    bool first_part = true;
    for (auto &line: input) {
        if (line == "") {
            first_part = false;
        }
        if (first_part) {
            int pos = line.find("|");
            int num = std::stoi(line.substr(0, pos));
            int num2 = std::stoi(line.substr(pos + 1, line.size() - pos - 1));
            ordering[num].insert(num2);
        }
        if (!first_part && line != "") {
            std::vector<int> list;
            int pos = 0;
            while (line.find(",", pos) != std::string::npos) {
                pos = line.find(",", pos);
                list.push_back(std::stoi(line.substr(0, pos)));
                line.erase(0, pos + 1);
            }
            list.push_back(std::stoi(line));
            lists.push_back(list);
        }
    }

    // check for every vector in list if the elements before are in the ordering
    int sum = 0;
    int sum2 = 0;
    for (auto &list: lists) {
        bool valid = is_valid(list, ordering);
        if (valid) {
            sum += list[list.size()/2];
        }
        if (!valid) {
            make_valid(list, ordering);
            sum2 += list[list.size()/2];
        }
    }
    std::cout << "Solution for part 1: " << sum << std::endl;
    std::cout << "Solution for part 2: " << sum2 << std::endl;
}