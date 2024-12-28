//
// Created by elisabeth on 25.12.24.
//
#include <fstream>
#include <iostream>
#include <vector>
#include <set>

enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

// print the grid
void print_grid(std::vector<std::vector<char>> &grid) {
    for (auto &row: grid) {
        for (char c: row) {
            std::cout << c;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void turn(Direction &dir) {
    switch (dir) {
        case Direction::UP:
            dir = Direction::RIGHT;
            break;
        case Direction::DOWN:
            dir = Direction::LEFT;
            break;
        case Direction::LEFT:
            dir = Direction::UP;
            break;
        case Direction::RIGHT:
            dir = Direction::DOWN;
            break;
    }
}

bool is_loop(std::vector<std::vector<char>> &grid) {
    int x = 0, y = 0;
    Direction dir = Direction::UP;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == '^') {
                x = i;
                y = j;
                break;
            }
        }
    }
    int counter = 0;
    int counter_max = grid.size()*grid[0].size();
    while (x >= 0 && x < grid.size() && y >= 0 && y < grid[x].size() && counter < counter_max + 1) {
        grid[x][y] = 'X';
        counter++;
        switch (dir) {
            case Direction::UP:
                if (x - 1 >= 0 && grid[x - 1][y] == '#') {
                    turn(dir);
                } else {
                    x--;
                }
                break;
            case Direction::DOWN:
                if (x + 1 < grid.size() && grid[x + 1][y] == '#') {
                    turn(dir);
                } else {
                    x++;
                }
                break;
            case Direction::LEFT:
                if (y - 1 >= 0 && grid[x][y - 1] == '#') {
                    turn(dir);
                } else {
                    y--;
                }
                break;
            case Direction::RIGHT:
                if (y + 1 < grid[x].size() && grid[x][y + 1] == '#') {
                    turn(dir);
                } else {
                    y++;
                }
                break;
        }
    }
    return counter >= counter_max;
}


int main() {
    std::string path = "/home/elisabeth/CLionProjects/Advent-of-Code-2024/";
    std::vector<std::string> input;
    std::fstream input_file(path + "input_day06.txt");
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

    std::vector<std::vector<char>> grid;
    for (auto &line: input) {
        std::vector<char> row;
        for (char c: line) {
            row.push_back(c);
        }
        grid.push_back(row);
    }

    // part 1
    //find start position '^' in the grid and set the direction
    /*int x = 0, y = 0;
    Direction dir = Direction::UP;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == '^') {
                x = i;
                y = j;
                break;
            }
        }
    }
    while (x >= 0 && x < grid.size() && y >= 0 && y < grid[x].size()) {
        grid[x][y] = 'X';
        switch (dir) {
            case Direction::UP:
                if (x - 1 >= 0 && grid[x - 1][y] == '#') {
                    turn(dir);
                } else {
                    x--;
                }
                break;
            case Direction::DOWN:
                if (x + 1 < grid.size() && grid[x + 1][y] == '#') {
                    turn(dir);
                } else {
                    x++;
                }
                break;
            case Direction::LEFT:
                if (y - 1 >= 0 && grid[x][y - 1] == '#') {
                    turn(dir);
                } else {
                    y--;
                }
                break;
            case Direction::RIGHT:
                if (y + 1 < grid[x].size() && grid[x][y + 1] == '#') {
                    turn(dir);
                } else {
                    y++;
                }
                break;
        }
    }

    // count the number of visited cells
    int count = 0;
    for (auto &row: grid) {
        for (char c: row) {
            if (c == 'X') {
                count++;
            }
        }
    }
    std::cout << "Solution for part 1: " << count << std::endl;*/

    // part 2
    int counter = 0;

    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == '#' || (grid[i][j] == '^')) {
                continue;
            }
            std::cout<<i<<" "<<j<<std::endl;
            std::vector<std::vector<char>> new_grid = grid;
            new_grid[i][j] = '#';
            if (is_loop(new_grid)) {
                counter++;
            }
        }
    }
std::cout << "Solution for part 2: " << counter << std::endl;
}