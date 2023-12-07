#include "../day0.h"

std::size_t get_number_of_possible_wins(std::unordered_map<std::size_t, std::size_t>& translation) {
    std::size_t total{1};
    for (auto& [time, record] : translation) {
        double left{(static_cast<double>(time) - (std::sqrt(time * time - 4 * record))) / 2};
        double right{(static_cast<double>(time) + std::sqrt(time * time - 4 * record)) / 2};
        double rounded_left{std::ceil(left)};
        double rounded_right{std::floor(right)};
        left = left == rounded_left ? left + 1 : rounded_left;
        right = right == rounded_right ? right - 1 : rounded_right;
        total *= static_cast<std::size_t>(right - left + 1);
    }
    return total;
}

void solve(const std::vector<std::string>& lines) {
    std::vector<std::size_t> time{to_number_vector(split(split(lines[0], ':')[1]))};
    std::vector<std::size_t> record{to_number_vector(split(split(lines[1], ':')[1]))};
    std::size_t concat_time{std::stoul(join(time))};
    std::size_t concat_record{std::stoul(join(record))};
    std::unordered_map<std::size_t, std::size_t> translation{};
    for (std::size_t i = 0; i < time.size(); i++)
        translation.insert({time[i], record[i]});
    std::cout << "1) Result is: " << get_number_of_possible_wins(translation) << std::endl;
    translation = {{concat_time, concat_record}};
    std::cout << "2) Result is: " << get_number_of_possible_wins(translation) << std::endl;
}

int main() {
    solve(read_input_file("../day06/day06_input"));
}