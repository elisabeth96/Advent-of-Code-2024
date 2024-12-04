//
// Created by elisabeth on 04.12.24.
//

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

int main(){
    //Read in the input file
    std::string path = "/home/elisabeth/CLionProjects/Advent-of-Code-2024/";
    std::vector<std::string> input;
    std::fstream input_file(path + "input_day01.txt");
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

    //first part of the task
    // add numbers to vectors
    /*std::vector<int> list1;
    std::vector<int> list2;
    for (auto& line : input){
        int pos_delim = line.find(' ');
        list1.push_back(std::stoi(line.substr(0, pos_delim)));
        list2.push_back(std::stoi(line.substr(pos_delim+1)));
    }
    std::sort(list1.begin(), list1.end());
    std::sort(list2.begin(), list2.end());

    // sum up differences
    int sum = 0;
    for (int i = 0; i < list1.size(); i++){
        sum += abs(list1[i] - list2[i]);
    }
    std::cout << "The sum of the differences is: " << sum << std::endl;*/

    //second part of the task
    // add numbers to set and map, respectively
    std::set<int> list1;
    std::map<int, int> list2;
    for (auto& line : input){
        int pos_delim = line.find(' ');
        list1.insert(std::stoi(line.substr(0, pos_delim)));
        if (list2.find(std::stoi(line.substr(pos_delim+1))) == list2.end())
            list2[std::stoi(line.substr(pos_delim+1))] = 1;
        else
            list2[std::stoi(line.substr(pos_delim+1))] += 1;
    }

    // find for each element in list1 the number of occurences in list2
    int sum = 0;
    for (auto& elem : list1){
        if (list2.find(elem) != list2.end()){
            sum += elem * list2[elem];
        }
    }
    std::cout << "The similarity score is: " << sum << std::endl;


    return 0;
}