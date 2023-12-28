#include "day0.h"

#define lens_map std::unordered_map<std::size_t, std::list<item>>

struct item {
    std::string label;
    std::size_t focal_length{0};
    item(std::string& s, std::size_t fl) : label{s}, focal_length{fl} {}
};

std::size_t hash(const std::string& str) {
    return std::accumulate(str.begin(), str.end(), 0ul, [](auto acc, auto c) {
        return ((acc + c) + ((acc + c) << 4)) & ((1 << 8) - 1);
    });
}

void remove_lens(lens_map& hashmap, const std::vector<std::string>& splits) {
    std::erase_if(hashmap[hash(splits[0])], [&](auto& element) { return element.label == splits[0]; });
}

void insert_lens(lens_map& hashmap, std::vector<std::string> splits) {
    item new_val{splits[0], std::stoul(splits[1])};
    std::list<item>& box{hashmap[hash(splits[0])]};
    if (!std::any_of(box.begin(), box.end(), [&](auto& element) { return element.label == splits[0]; }))
        return box.push_back(new_val);
    std::replace_if(box.begin(), box.end(), [&](auto& element) { return element.label == splits[0]; }, new_val);
}

std::size_t calculate_focusing_power(lens_map& hashmap) {
    std::size_t total{0};
    for (std::size_t i = 0; i < hashmap.size(); i++)
        for (auto j{1}; auto& item : hashmap[i])
            total += (i + 1) * j++ * item.focal_length;
    return total;
}

std::size_t configure_boxes(const std::string& line) {
    lens_map hashmap{};
    for (auto& n : split(line, ',')) {
        if (n.find('-') != std::string::npos) remove_lens(hashmap, split(trim(n), '-'));
        else if (n.find('=') != std::string::npos) insert_lens(hashmap, split(trim(n), '='));
    }
    return calculate_focusing_power(hashmap);
}

void solve(const std::vector<std::string>& lines) {
    std::vector<std::string> splits{split(lines[0], ',')};
    std::size_t sum_of_hashes{std::accumulate(splits.cbegin(),splits.cend(), 0ul, [](auto acc, auto& s) { return acc + hash(trim(s)); })};
    std::cout << "1) Result is " << sum_of_hashes << std::endl;
    std::cout << "2) Result is " << configure_boxes(lines[0]) << std::endl;

}

int main() {
    solve(read_input_file("../inputs/day15"));
}
