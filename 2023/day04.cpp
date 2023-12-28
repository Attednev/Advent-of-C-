#include "day0.h"

void solve(const std::vector<std::string>& lines) {
    std::size_t total_points{0};
    std::vector<std::size_t> number_of_cards_owned(lines.size(), 1);
    for (std::size_t i = 0; i < lines.size(); i++) {
        std::size_t scratchcard_points{0}, number_of_winning_cards{0};
        std::vector<std::string> splits{split(lines[i], ':')};
        std::vector<std::string> numbers{split(splits[1], '|')};
        std::vector<std::size_t> winning_numbers = to_number_vector(split(numbers[0]));
        std::vector<std::size_t> numbers_you_got = to_number_vector(split(numbers[1]));
        for (auto number : winning_numbers) {
            if (!contains(numbers_you_got, number)) {
                continue;
            }
            number_of_winning_cards++;
            scratchcard_points = scratchcard_points == 0 ? 1 : scratchcard_points * 2;
            if (number_of_winning_cards + i < number_of_cards_owned.size()) {
                number_of_cards_owned[number_of_winning_cards + i] += number_of_cards_owned[i];
            }
        }
        total_points += scratchcard_points;
    }
    std::cout << "1) The scratchcards have a value of " << total_points << std::endl;
    std::cout << "2) The number of scratchcards owned is " << std::reduce(number_of_cards_owned.begin(), number_of_cards_owned.end()) << std::endl;
}

int main() {
    solve(read_input_file("../inputs/day04"));
}