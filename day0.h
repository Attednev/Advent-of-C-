#pragma once

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <limits>
#include <numeric>
#include <utility>
#include <cerrno>
#include <cstring>
#include <unordered_map>

std::vector<std::string> read_input_file(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Unable to read file: " + std::string{std::strerror(errno)});
    std::vector<std::string> result{};
    std::string line{};
    while (std::getline(file, line)) result.push_back(line);
    return result;
}

std::vector<std::string> split(const std::string &string, char character) {
    std::vector<std::string> output{};
    std::size_t start_pos, end_pos{0};
    while ((start_pos = end_pos) != std::string::npos) {
        end_pos = string.find(character, start_pos);
        output.push_back(string.substr(start_pos, end_pos - start_pos));
        if (end_pos != std::string::npos) end_pos++;
    }
    return output;
}

std::vector<std::string> split(const std::string &string) {
    std::vector<std::string> output{split(string, ' ')};
    std::erase_if(output, [](const std::string &element) { return element.empty(); });
    return output;
}

std::vector<std::size_t> to_number_vector(const std::vector<std::string>& list) {
    std::vector<std::size_t> output{};
    output.reserve(list.size());
    std::for_each(list.begin(), list.end(), [&](auto element) { output.push_back(std::stoul(element)); });
    return output;
}

std::string join(const std::vector<std::string> &list, const std::string &character) {
    std::string output;
    for (std::size_t i = 0; i < list.size(); i++)
        output.append(list[i]).append(i + 1 < list.size() ? character : "");
    return output;
}

std::string join(const std::vector<std::size_t> &list, const std::string &character) {
    std::string output;
    for (std::size_t i = 0; i < list.size(); i++)
        output.append(std::to_string(list[i])).append(i + 1 < list.size() ? character : "");
    return output;
}


bool contains(std::vector<std::string>& list, const std::string& element) {
    return std::any_of(list.begin(), list.end(), [&](const auto& e) { return e == element; });
}

bool contains(std::vector<std::string>& list, char element) {
    return contains(list, std::string{element});
}

bool contains(std::vector<std::size_t>& list, std::size_t element) {
    return std::any_of(list.begin(), list.end(), [&](const auto& e) { return e == element; });
}

std::size_t max(std::size_t a, std::size_t b) {
    return (a < b) * b + (a >= b) * a;
}

std::size_t min(std::size_t a, std::size_t b) {
    return (a < b) * a + (a >= b) * b;
}




/*std::size_t read_nth_number(std::string str, std::size_t n, bool return_position = false, bool throw_on_error = false) {
    std::string number = "0";
    std::size_t i{0};
    for (std::size_t j = 0; j < n; j++) {
        if (!throw_on_error) {
            number = "0";
        }
        for (; i < str.length(); i++) {
            if (str[i] >= '0' && str[i] <= '9') {
                number += str[i];
            } else if (number.length() != 1) {
                i++;
                break;
            }
        }
    }
    std::cout << "line: " << str << " | number: " << number << std::endl;
    return return_position ? i - number.length() : std::stoi(number);
}*/