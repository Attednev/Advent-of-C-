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
#include <cmath>

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

std::string join(const std::vector<std::size_t> &list) {
    std::string output;
    for (const std::size_t number : list)
        output.append(std::to_string(number));
    return output;
}

std::string join(const std::vector<std::string> &list) {
    std::string output;
    for (const std::string& str : list)
        output.append(str);
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

template <typename T>
void print_vector(std::vector<T> list) {
    std::cout << "[";
    for (std::size_t i = 0; i < list.size(); i++) {
        std::cout << list[i];
        if (i + 1 < list.size())
            std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

template <typename T, typename S>
void print_map(std::unordered_map<T, S> map) {
    std::cout << "{" << std::endl;
    for (auto& [k, v] : map) {
        std::cout << "    {" << k << ": " << v;
        std::cout << "}" << std::endl;
    }
    std::cout << "}" << std::endl;
}