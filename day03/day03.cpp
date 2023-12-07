#include "../day0.h"

struct symbol {
    std::size_t line;
    std::size_t column;
    std::vector<std::size_t> surrounding_numbers{};
    bool operator==(const symbol& other) const {
        return line == other.line && column == other.column;
    }
};

struct range {
    long long line{};
    long long start_pos{};
    long long end_pos{};
};

struct machine_state{
    const std::vector<std::string>& input;
    std::vector<symbol>& symbol_positions;
    const std::vector<char> symbols{'*', '+', '#', '-', '@', '$', '%', '&', '/', '='};
};

bool is_adjacent_to_symbol(std::vector<symbol>& symbol_positions, const range& range, std::size_t number) {
    for (std::size_t line_number = range.line < 1 ? 0 : range.line - 1; line_number <= range.line + 1; line_number++)
        for (std::size_t column = range.start_pos < 0 ? 0 : range.start_pos; column <= range.end_pos; column++) {
            symbol position{line_number, column};
            if (contains(symbol_positions, position)) {
                symbol_positions[get_index_of(symbol_positions, position)].surrounding_numbers.push_back(number);
                return true;
            }
        }
    return false;
}

std::size_t calculate_gear_sum(const machine_state& state) {
    std::size_t total{0};
    for (long long i = 0; i < state.input.size(); i++) {
        std::string line{state.input[i]};
        std::replace_if(line.begin(), line.end(), [&](char symbol) {
            return symbol == '\r' || contains(state.symbols, symbol);
        }, '.');
        std::vector<std::string> splits{split(line, '.')};

        long long end_pos{-1};
        for (const auto& split : splits) {
            if (split.length() == 0) {
                end_pos++;
                continue;
            }
            long long number_length{static_cast<long long>(split.length())};
            end_pos += number_length + 1;
            if (is_adjacent_to_symbol(state.symbol_positions, {i, end_pos - number_length - 1, end_pos}, std::stoi(split)))
                total += std::stoi(split);
        }
    }
    return total;
}

void get_symbol_positions(const machine_state& state) {
    for (std::size_t i = 0; i < state.input.size(); i++)
        for (std::size_t j = 0; j < state.input[i].size(); j++)
            if (contains(state.symbols, state.input[i].at(j)))
                state.symbol_positions.emplace_back(i, j);
}

void solve(const std::vector<std::string>& input) {
    std::vector<symbol> symbol_positions{};
    machine_state state{input, symbol_positions};
    get_symbol_positions(state);
    std::size_t gear_sum{calculate_gear_sum(state)};
    std::size_t gear_ratio{0};
    for (const symbol& s : symbol_positions)
        if (s.surrounding_numbers.size() == 2)
            gear_ratio += std::accumulate(s.surrounding_numbers.begin(), s.surrounding_numbers.end(), 1, std::multiplies<>());

    std::cout << "1) Result is " << gear_sum << std::endl;
    std::cout << "2) Result is " << gear_ratio << std::endl;
}

int main() {
    solve(read_input_file("../day03/day03_input"));
}