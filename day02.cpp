#include "day0.h"

#define MAX_RED 12
#define MAX_BLUE 14
#define MAX_GREEN 13

std::size_t get_position_by_index(std::size_t element, std::size_t other1, std::size_t other2) {
    return element < other1 && element < other2 ? 1 : element > other1 && element > other2 ? 3 : 2;
}

std::pair<std::size_t, std::size_t, std::size_t> get_number_of_cubes(const std::string& line, std::size_t start, std::size_t end) {
    std::size_t red_index{line.substr(start, end - start).find("red")};
    std::size_t blue_index{line.substr(start, end - start).find("blue")};
    std::size_t green_index{line.substr(start, end - start).find("green")};

    std::size_t red_position{get_position_by_index(red_index, blue_index, green_index)};
    std::size_t blue_position{get_position_by_index(blue_index, green_index, red_index)};
    std::size_t green_position{get_position_by_index(green_index, red_index, blue_index)};

    std::size_t red_cubes{read_nth_number(line.substr(start, end - start), red_position)};
    std::size_t blue_cubes{read_nth_number(line.substr(start, end - start), blue_position)};
    std::size_t green_cubes{read_nth_number(line.substr(start, end - start), green_position)};

    return std::make_pair(red_cubes, blue_cubes, green_cubes);
}

void solve(std::vector<std::string> input) {
    std::size_t sum_of_game_ids{0};
    std::size_t power_of_cubes{0};

    std::for_each(input.begin(), input.end(), [&](const std::string& line) {

        std::size_t game_id = read_nth_number(line, 1);
        std::size_t start_index{line.find(':') + 1};
        std::size_t end_index{line.find(';')};

        std::size_t min_red_cubes{0};
        std::size_t min_blue_cubes{0};
        std::size_t min_green_cubes{0};

        bool is_possible_game{true};
        while (start_index < end_index) {
            auto [red, blue, green] = get_number_of_cubes(line, start_index, end_index);

            min_red_cubes = std::max(red, min_red_cubes);
            min_blue_cubes = std::max(blue, min_blue_cubes);
            min_green_cubes = std::max(green, min_green_cubes);

            is_possible_game = is_possible_game && red <= MAX_RED && blue <= MAX_BLUE && green <= MAX_GREEN;
            start_index = end_index == line.length() ? end_index : end_index + 1;

            if (start_index < line.length()) {
                end_index = line.substr(start_index + 1, line.length()).find(';');
                end_index = end_index == std::string::npos ? line.length() : end_index + start_index + 1;
            }
        }

        if (is_possible_game) {
            sum_of_game_ids += game_id;
        }
        power_of_cubes += min_red_cubes * min_blue_cubes * min_green_cubes;
    });
    std::cout << "The sum of the possible game ids is " << sum_of_game_ids << std::endl;
    std::cout << "The sum of the power of the sets is " << power_of_cubes << std::endl;
}

int main() {
    solve(read_input_file(2));
}