#include "day0.h"

struct extrapolation {
    long long front{0}, back{0};
    extrapolation& operator+=(const extrapolation& other) {
        front += other.front;
        back += other.back;
        return *this;
    }
};

extrapolation extrapolate(std::vector<long long>&& values) {
    extrapolation total{0, 0};
    bool odd_iteration{true};
    while (!std::all_of(values.begin(), values.end(), [](auto i) { return i == 0; })) {
        total.front += (1 - 2 * odd_iteration) * values.front();
        total.back += values.back();
        std::adjacent_difference(values.begin(), values.end(), values.begin());
        values.erase(values.begin());
    }
    return total;
}

void solve(const std::vector<std::string>& lines) {
    extrapolation result{0, 0};
    for (const std::string& line : lines)
        result += extrapolate(to_number_svector(split(line)));
    std::cout << "1) Result is " << result.back << std::endl;
    std::cout << "2) Result is " << result.front << std::endl;
}

int main() {
    solve(read_input_file("../inputs/day09"));
}
