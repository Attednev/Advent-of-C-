#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <limits>

std::vector<std::string> read_input_file(int day) {
    std::string filename{(day < 10 ? "day0" : "day") + std::to_string(day) + "_input"};
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to read file");
    }

    std::vector<std::string> result{};
    std::string line{};
    while (std::getline(file, line)) {
        result.push_back(line);
    }
    return result;
}

std::size_t read_nth_number(std::string str, std::size_t n, bool return_position = false) {
    std::string number = "0";
    std::size_t i{0};
    for (std::size_t j = 0; j < n; j++) {
        number = "0";
        for (; i < str.length(); i++) {
            if (str[i] >= '0' && str[i] <= '9') {
                number += str[i];
            } else if (number.length() != 1) {
                i++;
                break;
            }
        }
    }
    return return_position ? i - number.length() : std::stoi(number);
}