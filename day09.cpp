//
// Created by elisabeth on 27.12.24.
//
#include <fstream>
#include <iostream>
#include <vector>
#include <map>

int main() {
    std::string path = "/home/elisabeth/CLionProjects/Advent-of-Code-2024/";
    std::string input;
    std::fstream input_file(path + "input_day09.txt");
    if (!input_file.is_open()) {
        std::cout << "Could not open file" << std::endl;
        return 1;
    }
    std::getline(input_file, input);
    input_file.close();

    std::vector<int> old_format;
    for (auto &c: input) {
        int n = c - '0';
        old_format.push_back(n);
    }

    std::vector<int> new_format;
    std::map<int, int> empty_spaces;
    std::map<int, int> files;
    for (int i = 0; i < old_format.size(); i++) {
        int l = old_format[i];
        int index = i % 2 == 0 ? i / 2 : -1;
        if (index == -1){
            empty_spaces[new_format.size()] = l;
        } else{
            files[new_format.size()] = l;
        }
        while (l > 0) {
            new_format.push_back(index);
            l--;
        }
    }
    // part 1
    /*int index_left = 0;
    int index_right = new_format.size()-1;
    while(index_left < index_right){
        while(index_left < new_format.size() - 1 && new_format[index_left] != -1){
            index_left++;
        }
        while(index_right > 0 && new_format[index_right]== -1){
            index_right--;
        }
        if (index_left < index_right){
            std::swap(new_format[index_left], new_format[index_right]);
        }
    }*/

    // part 2
    while(!files.empty()) {
        auto it = files.rbegin();
        auto [file_start, file_size] = *it;
        files.erase(file_start);

        if(file_start < empty_spaces.begin()->first) break;

        // look for leftmost empty slot that is big enough
        for(auto [empty_start, empty_size] : empty_spaces){
            if (empty_size >= file_size && empty_start <= file_start){
                // insert file
                for (int i = 0; i < file_size; i++){
                    std::swap(new_format[empty_start + i], new_format[file_start + i]);
                }
                // update empty spaces
                empty_spaces.erase(empty_start);
                if (empty_size > file_size){
                    empty_spaces[empty_start + file_size] = empty_size - file_size;
                }
                break;
            }
        }
    }

    long long sum = 0;
    for (int i = 0; i < new_format.size(); i++) {
        //std::cout << new_format[i] << " ";
        if (new_format[i] == -1){
            continue;
        }
        sum += new_format[i] * i;
    }

    std::cout<< "The solution of part 1 is: " << sum << std::endl;
}