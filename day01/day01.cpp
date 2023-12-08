#include "../day0.h"

std::size_t get_calibration_value(const std::vector<std::string> &input, std::unordered_map<std::string, std::string> numbers) {
    std::size_t total_sum = 0;
    std::for_each(input.begin(), input.end(), [&](std::string line) {
        std::pair<std::size_t, std::size_t> position{std::string::npos, std::string::npos};
        std::pair<std::string, std::string> digits{"", ""};
        std::for_each(numbers.begin(), numbers.end(), [&](auto element) {
            std::size_t f_pos{line.find(element.first)};
            std::size_t l_pos{line.rfind(element.first)};
            if (f_pos != std::string::npos && (position.first == std::string::npos || f_pos < position.first)) {
                position.first = f_pos;
                digits.first = element.second;
            }
            if (l_pos != std::string::npos && (position.second == std::string::npos || l_pos > position.second)) {
                position.second = l_pos;
                digits.second = element.second;
            }
        });
        if (position.first != std::string::npos && position.second != std::string::npos)
            total_sum += std::stoi(digits.first + digits.second);
    });
    return total_sum;
}

void solve(const std::vector<std::string> &input) {
    std::unordered_map<std::string, std::string> numbers{{"1", "1"}, {"2", "2"}, {"3", "3"},
                                                         {"4", "4"}, {"5", "5"}, {"6", "6"},
                                                         {"7", "7"}, {"8", "8"}, {"9", "9"},
                                                         {"0", "0"}};
    std::cout << "1) Result: " << get_calibration_value(input, numbers) << std::endl;

    numbers.insert({{"one",   "1"}, {"two",   "2"}, {"three", "3"}, {"four",  "4"},
                    {"five",  "5"}, {"six",   "6"}, {"seven", "7"}, {"eight", "8"},
                    {"nine",  "9"}, {"zero",  "0"}});
    std::cout << "2) Result: " << get_calibration_value(input, numbers) << std::endl;
}

int main() {
    solve(read_input_file("../inputs/day01"));
}
