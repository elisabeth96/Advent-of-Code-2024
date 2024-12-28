//
// Created by elisabeth on 27.12.24.
//
#include <fstream>
#include <iostream>
#include <vector>
#include <map>

struct Location {
    int x;
    int y;
};

// operator for the addition of two locations
Location operator+(const Location &loc1, const Location &loc2) {
    return {loc1.x + loc2.x, loc1.y + loc2.y};
}

// operator for the subtraction of two locations
Location operator-(const Location &loc1, const Location &loc2) {
    return {loc1.x - loc2.x, loc1.y - loc2.y};
}
int main() {
    std::string path = "/home/elisabeth/CLionProjects/Advent-of-Code-2024/";
    std::vector<std::string> input;
    std::fstream input_file(path + "input_day08.txt");
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

    std::vector<std::vector<int>> locations(input.size(), std::vector<int>(input[0].size(), 0));
    std::map<char, std::vector<Location>> antennas;
    // save locations of antennas in input
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[i].size(); j++) {
            if (input[i][j] != '.') {
                antennas[input[i][j]].push_back({i, j});
            }
        }
    }
    // solution of part 1
    // go through all antennas and calculate the pairwise distance between two locations
    /*for (auto &antenna: antennas) {
        for (int i = 0; i < antenna.second.size(); i++) {
            for (int j = i + 1; j < antenna.second.size(); j++) {
                Location diff = antenna.second[j] - antenna.second[i];
                Location loc1 = antenna.second[j] + diff;
                Location loc2 = antenna.second[i] - diff;
                if (loc1.x >= 0 && loc1.x < input.size() && loc1.y >= 0 && loc1.y < input[0].size()) {
                    locations[loc1.x][loc1.y]++;
                }
                if (loc2.x >= 0 && loc2.x < input.size() && loc2.y >= 0 && loc2.y < input[0].size()) {
                    locations[loc2.x][loc2.y]++;
                }
            }
        }
    }
    // count the number of locations with at least one antenna
    int count = 0;
    for (auto &line: locations) {
        for (auto &loc: line) {
            if (loc > 0) {
                count++;
            }
        }
    }
    std::cout << "Solution for part 1: " << count << std::endl;*/

    // solution of part 2
    for (auto &antenna: antennas) {
        for (int i = 0; i < antenna.second.size(); i++) {
            for (int j = i + 1; j < antenna.second.size(); j++) {
                locations[antenna.second[i].x][antenna.second[i].y]++;
                locations[antenna.second[j].x][antenna.second[j].y]++;
                Location diff = antenna.second[j] - antenna.second[i];
                Location loc1 = antenna.second[j] + diff;
                Location loc2 = antenna.second[i] - diff;
                while(loc1.x >= 0 && loc1.x < input.size() && loc1.y >= 0 && loc1.y < input[0].size()) {
                    locations[loc1.x][loc1.y]++;
                    loc1 = loc1 + diff;
                }
                while (loc2.x >= 0 && loc2.x < input.size() && loc2.y >= 0 && loc2.y < input[0].size()) {
                    locations[loc2.x][loc2.y]++;
                    loc2 = loc2 - diff;
                }
            }
        }
    }
    // count the number of locations with at least one antenna
    int count = 0;
    for (auto &line: locations) {
        for (auto &loc: line) {
            if (loc > 0) {
                count++;
            }
        }
    }
    std::cout << "Solution for part 2: " << count << std::endl;
}