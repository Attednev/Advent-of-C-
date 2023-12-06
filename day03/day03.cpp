#include "../day0.h"

std::size_t read_nth_number(std::string str, std::size_t n, bool return_position = false, bool throw_on_error = false) {
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
    return return_position ? i - number.length() : std::stoi(number);
}

long long
add_part_values(std::vector<std::pair<long long, char>> &positions, std::size_t number, std::size_t number_pos_size_t,
                std::vector<std::vector<long long>> &gear_ratio) {
    long long number_length{static_cast<long long>(std::to_string(number).length())};
    long long number_position{static_cast<long long>(number_pos_size_t)};
    long long output{0};
    for (auto [index, symbol] : positions) {
        if (index - number_position >= -1 && index - number_position <= number_length) {
            output = static_cast<long long>(number);
            if (symbol == '*') {
                gear_ratio[index].push_back(static_cast<long long>(number));
                return output;
            }
        }
    }
    return output;
}

std::vector<std::pair<long long, char>> find_symbols(std::string line) {
    std::vector<std::pair<long long, char>> output{};
    for (long long i = 0; i < line.length(); i++) {
        if (line[i] != '.' && line[i] >= '!' && (line[i] < '0' || line[i] > '9')) {
            output.emplace_back(i, line[i]);
        }
    }
    return output;
}

void solve(std::vector<std::string> input) {
    std::size_t total{0};
    std::size_t number;
    std::vector<std::vector<std::vector<long long>>> gear_ratio{};
    for (std::size_t i = 0; i < input.size() + 2; i++) {
        std::vector<std::vector<long long>> v1{};
        for (std::size_t j = 0; j < input[0].length(); j++) {
            std::vector<long long> v{};
            v1.push_back(v);
        }
        gear_ratio.push_back(v1);
    }
    for (std::size_t i = 0; i < input.size(); i++) {
        std::vector<std::pair<long long, char>> above = find_symbols(i > 0 ? input[i - 1] : "");
        std::vector<std::pair<long long, char>> center = find_symbols(input[i]);
        std::vector<std::pair<long long, char>> below = find_symbols(i + 1 < input.size() ? input[i + 1] : "");

        for (std::size_t j = 1; (number = read_nth_number(input[i], j)) != 0; j++) {
            std::size_t number_position = read_nth_number(input[i], j, true);
            for (short k = 1; k <= 3; k++) {
                long long parts_found = add_part_values(above, number, number_position, gear_ratio[i + k]);
                if (parts_found != 0) {
                    total += parts_found;
                    break;
                }
            }
        }
    }

    std::size_t gear_sum{0};
    for (const std::vector<std::vector<long long>>& v1 : gear_ratio) {
        for (std::vector<long long> v : v1) {
            if (v.size() == 2) {
                gear_sum += v[0] * v[1];
            }
        }
    }

    std::cout << "The sum of all the important parts is " << total << std::endl;
    std::cout << "The sum of gear ratios is " << gear_sum << std::endl;
}

int main() {
    std::cout << "Currently broken" << std::endl;
    return -1;
    solve(read_input_file("../day03/day03_input"));
}