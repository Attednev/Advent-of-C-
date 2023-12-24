#include "day0.h"

struct function {
    double coefficient_x;
    double constant;
};

void solve(const std::vector<std::string>& input) {
    std::vector<function> functions{};
    std::vector<std::size_t> points{};
    std::vector<std::size_t> deltas{};
    for (auto& line : trim_lines(input)) {
        auto splits{split(line, '@')};
        auto point{to_number_svector(split(splits[0], ", "))};
        auto delta{to_number_svector(split(splits[1], ", "))};
        auto slope{(double)delta[1] / (double)delta[0]};
        auto y_intercept{(double)point[1] - slope * (double)point[0]};
        functions.emplace_back(slope, y_intercept);
        points.emplace_back(point[0]);
        deltas.emplace_back(delta[0]);
    }

    std::size_t number_of_collisions{0};
    for (std::size_t i = 0; i < functions.size(); i++) {
        auto& [a1, b1] = functions[i];
        for (std::size_t j = i + 1; j < functions.size(); j++) {
            auto& [a2, b2] = functions[j];
            auto intersection_x{(b2 - b1) / (a1 - a2)};
            auto intersection_y{a1 * intersection_x + b1};
            if (intersection_x >= 200000000000000 && intersection_x <= 400000000000000 &&
                    intersection_y >= 200000000000000 && intersection_y <= 400000000000000 &&
                    ((deltas[i] > 0) == (intersection_x > points[i]) &&
                    (deltas[j] > 0) == (intersection_x > points[j]))) {
                number_of_collisions++;
            }
        }
    }
    std::cout << "1) Result is " << number_of_collisions << std::endl;
}

int main() {
    solve(read_input_file("../inputs/day24"));
}