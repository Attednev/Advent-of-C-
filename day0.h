#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <limits>

std::vector<std::string> read_input_file(int day) {
	std::string filename{(day < 10 ? "day0" : "day") + std::to_string(day) + "_input"};
	std::ifstream file(filename);
	if (!file.is_open()) {
		throw std::runtime_error("Unable to read file");
	}
	
	std::vector<std::string> result{};
	std::string line{};
	while (std::getline(file, line)) {
		result.push_back(line);
	}
	return result;
}