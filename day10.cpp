//
// Created by elisabeth on 28.12.24.
//
#include <fstream>
#include <iostream>
#include <vector>
#include <set>


int count_paths(const std::vector<std::vector<int>>& height_map, const std::pair<int, int>& start) {
    std::vector<std::pair<int, int>> positions;
    positions.push_back(start);

    std::set<std::pair<int, int>> end_positions;

    while (!positions.empty()) {
        std::pair<int, int> current = positions.back();
        positions.pop_back();

        // if height is nine, we have reached the end
        if(height_map[current.first][current.second] == 9) {
            end_positions.insert(current);
            continue;
        }

        // otherwise try going up, down, left, right. The height has to be one more than the current height
        int height = height_map[current.first][current.second];

        // left
        if (current.second > 0 && height_map[current.first][current.second - 1] == height + 1) {
            positions.emplace_back(current.first, current.second - 1);
        }
        // right
        if (current.second < height_map[0].size() - 1 && height_map[current.first][current.second + 1] == height + 1) {
            positions.emplace_back(current.first, current.second + 1);
        }
        // up
        if (current.first > 0 && height_map[current.first - 1][current.second] == height + 1) {
            positions.emplace_back(current.first - 1, current.second);
        }
        // down
        if (current.first < height_map.size() - 1 && height_map[current.first + 1][current.second] == height + 1) {
            positions.emplace_back(current.first + 1, current.second);
        }
    }

    return end_positions.size();
}

int count_paths2(const std::vector<std::vector<int>>& height_map, const std::pair<int, int>& start) {
    std::vector<std::pair<int, int>> positions;
    positions.push_back(start);

    int end_positions = 0;

    while (!positions.empty()) {
        std::pair<int, int> current = positions.back();
        positions.pop_back();

        // if height is nine, we have reached the end
        if(height_map[current.first][current.second] == 9) {
            end_positions++;
            continue;
        }

        // otherwise try going up, down, left, right. The height has to be one more than the current height
        int height = height_map[current.first][current.second];

        // left
        if (current.second > 0 && height_map[current.first][current.second - 1] == height + 1) {
            positions.emplace_back(current.first, current.second - 1);
        }
        // right
        if (current.second < height_map[0].size() - 1 && height_map[current.first][current.second + 1] == height + 1) {
            positions.emplace_back(current.first, current.second + 1);
        }
        // up
        if (current.first > 0 && height_map[current.first - 1][current.second] == height + 1) {
            positions.emplace_back(current.first - 1, current.second);
        }
        // down
        if (current.first < height_map.size() - 1 && height_map[current.first + 1][current.second] == height + 1) {
            positions.emplace_back(current.first + 1, current.second);
        }
    }

    return end_positions;
}

int main() {
    std::string path = "/home/elisabeth/CLionProjects/Advent-of-Code-2024/";
    std::vector<std::string> input;
    std::fstream input_file(path + "input_day10.txt");
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

    std::vector<std::vector<int>> height_map;
    std::vector<std::pair<int, int>> start_locations;

    for (int i = 0; i < input.size(); i++) {
        std::vector<int> row;
        for (int j = 0; j < input[i].size(); j++) {
            row.push_back(input[i][j] - '0');
            if (input[i][j] == '0') {
                start_locations.emplace_back(i, j);
            }
        }
        height_map.push_back(row);
    }

    long long sum = 0;

    for (const auto& start : start_locations) {
        sum += count_paths(height_map, start);
    }

    std::cout << "Solution for part 1: " << sum << std::endl;

    long long sum2 = 0;

    for (const auto& start : start_locations) {
        sum2 += count_paths2(height_map, start);
    }

    std::cout << "Solution for part 2: " << sum2 << std::endl;
}