#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <variant>
#include <limits>
#include <numeric>
#include <optional>
#include <utility>
#include <cerrno>
#include <cstring>
#include <unordered_map>
#include <cstdint>
#include <cmath>
#include <stack>
#include <list>

std::vector<std::string> read_input_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Unable to read file: " + std::string{std::strerror(errno)});
    std::vector<std::string> result{};
    std::string line{};
    while (std::getline(file, line)) result.push_back(line);
    return result;
}

std::vector<std::string> split(const std::string& string, const std::string& substr) {
    std::vector<std::string> output{};
    std::size_t start_pos, end_pos{0};
    while ((start_pos = end_pos) != std::string::npos) {
        end_pos = string.find(substr, start_pos);
        output.push_back(string.substr(start_pos, end_pos - start_pos));
        if (end_pos != std::string::npos) end_pos += substr.length();
    }
    return output;
}

std::vector<std::string> split(const std::string& string, const char character) {
    return split(string, std::string{character});
}

void remove_empty(std::vector<std::string>& list) {
    std::erase_if(list, [](const std::string &element) { return element.empty(); });
}

std::vector<std::string> split(const std::string& string) {
    std::vector<std::string> output{split(string, ' ')};
    remove_empty(output);
    return output;
}

std::vector<std::size_t> to_number_vector(const std::vector<std::string>& list) {
    std::vector<std::size_t> output{};
    output.reserve(list.size());
    std::for_each(list.begin(), list.end(), [&](auto element) { output.push_back(std::stoul(element)); });
    return output;
}

std::vector<long long> to_number_svector(const std::vector<std::string>& list) {
    std::vector<long long> output{};
    output.reserve(list.size());
    std::for_each(list.begin(), list.end(), [&](auto element) { output.push_back(std::stoll(element)); });
    return output;
}

std::string trim(const std::string& element) {
    std::size_t start_pos{0};
    std::size_t end_pos{element.length() - 1};
    for (; start_pos < element.length(); start_pos++)
        if (element[start_pos] != ' ' && element[start_pos] != '\r')
            break;
    for (; end_pos > start_pos; end_pos--)
        if (element[end_pos] != ' ' && element[end_pos] != '\r')
            break;
    if (start_pos > end_pos)
        return std::string{""};
    return element.substr(start_pos, end_pos - start_pos + 1);
}

std::string join(const std::vector<std::string>& list, const std::string& character) {
    std::string output;
    for (std::size_t i = 0; i < list.size(); i++)
        output.append(list[i]).append(i + 1 < list.size() ? character : "");
    return output;
}

std::string join(const std::vector<std::size_t>& list, const std::string& character) {
    std::string output;
    for (std::size_t i = 0; i < list.size(); i++)
        output.append(std::to_string(list[i])).append(i + 1 < list.size() ? character : "");
    return output;
}

std::string join(const std::vector<std::size_t>& list) {
    std::string output;
    for (const std::size_t number : list)
        output.append(std::to_string(number));
    return output;
}

std::string join(const std::vector<std::string>& list) {
    std::string output;
    for (const std::string& str : list)
        output.append(str);
    return output;
}

template <typename T, typename S>
bool contains(const S& list, const T element) {
    return std::any_of(list.begin(), list.end(), [&](const auto& e) { return e == element; });
}

template <typename T>
bool contains(const std::vector<T>& list, const T element) {
    return contains<T, std::vector<T>>(list, element);
}

bool contains(const std::vector<std::string>& list, const char element) {
    return contains(list, std::string{element});
}

template <typename T, typename S>
bool contains(const std::unordered_map<T, S>& list, const T element) {
    return std::any_of(list.begin(), list.end(), [&](const auto& e) { return e.first == element; });
}

template <typename T, typename S>
void insert_or_append(std::unordered_map<T, std::vector<S>>& map, T key, S value) {
    if (map.find(key) == map.end()) map.insert({key, {value}});
    else map[key].push_back(value);
}

std::size_t max(const std::size_t a, const std::size_t b) {
    return (a < b) * b + (a >= b) * a;
}

std::size_t min(const std::size_t a, const std::size_t b) {
    return (a < b) * a + (a >= b) * b;
}
namespace range_index {
    std::size_t npos = std::string::npos;
}
template <typename T>
std::size_t get_index_of(const std::vector<T> list, const T element) {
    for (std::size_t i = 0; i < list.size(); i++)
        if (list[i] == element)
            return i;
    return range_index::npos;
}

template <typename T>
void print_vector(const std::vector<T>& list) {
    std::cout << "[";
    for (std::size_t i = 0; i < list.size(); i++) {
        std::cout << list[i];
        if (i + 1 < list.size())
            std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

template <typename T, typename S>
void print_map(const std::unordered_map<T, S>& map) {
    std::cout << "{" << std::endl;
    for (auto& [k, v] : map) {
        std::cout << "    {" << k << ": " << v;
        std::cout << "}" << std::endl;
    }
    std::cout << "}" << std::endl;
}

std::vector<std::string> trim_lines(const std::vector<std::string>& lines) {
    std::vector<std::string> trimmed{};
    trimmed.reserve(lines.size());
    for (auto& line : lines)
        trimmed.emplace_back(trim(line));
    return std::move(trimmed);
}
