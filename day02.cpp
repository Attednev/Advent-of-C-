#include "day02.h"

std::size_t read_nth_number(std::string str, std::size_t n) {
	std::string number = "0";
	std::size_t i{0};
	for (std::size_t j = 0; j < n; j++) {
		number = "0";
		for (; i < str.length(); i++) {
			if (str[i] >= '0' && str[i] <= '9') {
				number.append(&str[i]);
			} else if (number.length() != 1) {
				break;
			}
		}
	}
	return std::stoi(number);
}

std::size_t get_position_by_index(std::size_t element, std::size_t other1, std::size_t other2) {
	return element < other1 && element < other2 ? 1 : element > other1 && element > other2 ? 3 : 2;
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
			std::size_t red_index{line.substr(start_index, end_index - start_index).find("red")};
			std::size_t blue_index{line.substr(start_index, end_index - start_index).find("blue")};
			std::size_t green_index{line.substr(start_index, end_index - start_index).find("green")};

			std::size_t red_position{get_position_by_index(red_index, blue_index, green_index)};
			std::size_t blue_position{get_position_by_index(blue_index, green_index, red_index)};
			std::size_t green_position{get_position_by_index(green_index, red_index, blue_index)};
			
			std::size_t red_cubes{read_nth_number(line.substr(start_index, end_index - start_index), red_position)};
			std::size_t blue_cubes{read_nth_number(line.substr(start_index, end_index - start_index), blue_position)};
			std::size_t green_cubes{read_nth_number(line.substr(start_index, end_index - start_index), green_position)};
			
			min_red_cubes = std::max(red_cubes, min_red_cubes);
			min_blue_cubes = std::max(blue_cubes, min_blue_cubes);
			min_green_cubes = std::max(green_cubes, min_green_cubes);
			
			is_possible_game = is_possible_game & (red_cubes <= MAX_RED && blue_cubes <= MAX_BLUE && green_cubes <= MAX_GREEN);
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