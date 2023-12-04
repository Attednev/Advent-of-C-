#include "day0.h"

void add_to_list(const std::string& number, std::vector<std::size_t>& list) {
    if (!number.empty()) {
        list.push_back(std::stoi(number));
    }
}

void extract_numbers(const std::string& line, std::vector<std::size_t>& winning_numbers, std::vector<std::size_t>& numbers_you_got) {
    short mode{0};      // modes: 0=card_number, 1=winning_numbers, 2=numbers_you_got
    std::string number;
    for (const char symbol : line) {
        if (symbol == ' ') {
            add_to_list(number, mode == 1 ? winning_numbers : numbers_you_got);
            number = "";
        } else if (symbol == ':' || symbol == '|') {
            mode++;
            number = "";
        } else if (symbol >= '0' && symbol <= '9') {
            number += symbol;
        }
    }
    add_to_list(number, mode == 1 ? winning_numbers : numbers_you_got);
}

void solve(std::vector<std::string> lines) {
    std::size_t total_points{0};
    std::vector<std::size_t> number_of_cards_owned(lines.size(), 1);
    for (std::size_t i = 0; i < lines.size(); i++) {
        std::vector<std::size_t> winning_numbers;
        std::vector<std::size_t> numbers_you_got;
        extract_numbers(lines[i], winning_numbers, numbers_you_got);
        std::size_t scratchcard_points{0};
        std::size_t number_of_winning_cards{0};
        for (auto number : winning_numbers) {
            if (std::find(numbers_you_got.begin(), numbers_you_got.end(), number) != numbers_you_got.end()) {
                number_of_winning_cards++;
                scratchcard_points = scratchcard_points == 0 ? 1 : scratchcard_points * 2;
                if (number_of_winning_cards + i < number_of_cards_owned.size()) {
                    number_of_cards_owned[number_of_winning_cards + i] += number_of_cards_owned[i];
                }
            }
        }
        total_points += scratchcard_points;
    }
    std::cout << "1) The scratchcards have a value of " << total_points << std::endl;
    std::cout << "2) The number of scratchcards owned is " << std::reduce(number_of_cards_owned.begin(), number_of_cards_owned.end()) << std::endl;
}


int main() {
    solve(read_input_file(4));
}