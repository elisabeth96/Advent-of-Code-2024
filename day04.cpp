//
// Created by elisabeth on 25.12.24.
//
#include <iostream>
#include <vector>
#include <fstream>
#include <array>

int check_horizontal(std::vector<std::vector<char>>& letters, std::array<char, 4> word) {
    int counter = 0;
    for (int i = 0; i < letters.size(); i++) {
        for (int j = 0; j < letters[i].size(); j++) {
            if (letters[i][j] == word[0]) {
                if (j + 3 < letters[i].size() && letters[i][j + 1] == word[1] && letters[i][j + 2] == word[2] && letters[i][j + 3] == word[3]) {
                    counter++;
                }
            }
        }
    }
    return counter;
}

int check_vertical(std::vector<std::vector<char>>& letters, std::array<char, 4> word){
    int counter = 0;
    for (int i = 0; i < letters[0].size(); i++) {
        for (int j = 0; j < letters.size(); j++) {
            if (letters[j][i] == word[0]) {
                if (j + 3 < letters.size() && letters[j + 1][i] == word[1] && letters[j + 2][i] == word[2] && letters[j + 3][i] == word[3]) {
                    counter++;
                }
            }
        }
    }
    return counter;
}

int check_diagonal_right(std::vector<std::vector<char>>& letters, std::array<char, 4> word){
    int counter = 0;
    for (int i = 0; i < letters.size(); i++) {
        for (int j = 0; j < letters[i].size(); j++) {
            if (letters[i][j] == word[0]) {
                if (i + 3 < letters.size() && j + 3 < letters[i].size() && letters[i + 1][j + 1] == word[1] && letters[i + 2][j + 2] == word[2] && letters[i + 3][j + 3] == word[3]) {
                    counter++;
                }
            }
        }
    }
    return counter;
}

int check_diagonal_left(std::vector<std::vector<char>>& letters, std::array<char, 4> word){
    int counter = 0;
    for (int i = 0; i < letters.size(); i++) {
        for (int j = 0; j < letters[i].size(); j++) {
            if (letters[i][j] == word[0]) {
                if (i + 3 < letters.size() && j - 3 >= 0 && letters[i + 1][j - 1] == word[1] && letters[i + 2][j - 2] == word[2] && letters[i + 3][j - 3] == word[3]) {
                    counter++;
                }
            }
        }
    }
    return counter;
}

// check for the following scheme:
// M - M
// - A -
// S - S
int check_cross(std::vector<std::vector<char>>& letters, std::array<char, 3> word1, std::array<char, 3> word2) {
    int counter = 0;
    for (int i = 0; i < letters.size() - 2; i++) {
        for (int j = 0; j < letters[i].size() - 2; j++) {
            if (letters[i][j] == word1[0] && letters[i][j+2] == word2[0]) {
                if (letters[i+1][j+1] == word1[1] && letters[i+2][j+2] == word1[2] && letters[i+2][j] == word2[2]) {
                    counter++;
                }
            }
        }
    }
    return counter;
}

int main() {
    std::string path = "/home/elisabeth/CLionProjects/Advent-of-Code-2024/";
    std::vector<std::string> input;
    std::fstream input_file(path + "input_day04.txt");
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

    // save input in vector of vectors
    std::vector<std::vector<char>> letters;
    for (auto &line: input) {
        std::vector<char> line_letters;
        for (auto &letter: line) {
            line_letters.push_back(letter);
        }
        letters.push_back(line_letters);
    }

    int counter = 0;
    counter += check_horizontal(letters, {'X', 'M', 'A', 'S'});
    counter += check_vertical(letters, {'X', 'M', 'A', 'S'});
    counter += check_diagonal_right(letters, {'X', 'M', 'A', 'S'});
    counter += check_diagonal_left(letters, {'X', 'M', 'A', 'S'});
    counter += check_horizontal(letters, {'S', 'A', 'M', 'X'});
    counter += check_vertical(letters, {'S', 'A', 'M', 'X'});
    counter += check_diagonal_right(letters, {'S', 'A', 'M', 'X'});
    counter += check_diagonal_left(letters, {'S', 'A', 'M', 'X'});
    std::cout << "Solution for part 1: " << counter << std::endl;
    counter = 0;
    counter += check_cross(letters, {'M', 'A', 'S'}, {'M', 'A', 'S'});
    counter += check_cross(letters, {'M', 'A', 'S'}, {'S', 'A', 'M'});
    counter += check_cross(letters, {'S', 'A', 'M'}, {'M', 'A', 'S'});
    counter += check_cross(letters, {'S', 'A', 'M'}, {'S', 'A', 'M'});
    std::cout << "Solution for part 2: " << counter << std::endl;



}