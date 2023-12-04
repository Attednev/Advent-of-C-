#include "day0.h"

int solve(std::vector<std::string> input, bool part2 = false) {
	std::vector<std::string> numbers{"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};
	std::vector<std::string> number_words{"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "zero"};
	if (part2) {
		numbers.insert(numbers.end(), number_words.begin(), number_words.end());	
	}
	std::size_t total_sum = 0;

	std::for_each(input.begin(), input.end(), [&](std::string line) {
		std::string first_element, last_element;
		std::size_t first_pos{0}, last_pos{0};

		std::for_each(numbers.begin(), numbers.end(), [&](auto element) {
			std::size_t pos{line.find(element)};
			if (pos != std::string::npos && (first_element.empty() || pos < first_pos)) {
				first_pos = pos;
				first_element = element;
			}
            pos = line.rfind(element);
            if (pos != std::string::npos && (last_element.empty() || pos > last_pos)) {
                last_pos = pos;
                last_element = element;
            }
		});
		std::string first_number{numbers[std::distance(numbers.begin(), std::find(numbers.begin(), numbers.end(), first_element)) % 10]};
		std::string last_number{numbers[std::distance(numbers.begin(), std::find(numbers.begin(), numbers.end(), last_element)) % 10]};
		total_sum += std::stoi(first_number + last_number);
	});
	std::string output{part2 ? "Part 2" : "Part 1"};
	output.append(": The sum of all the calibration values is ");
	std::cout << output << total_sum << std::endl;
	return 0;
}

int main() {
	return solve(read_input_file(1), true);
}
