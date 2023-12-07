#include "../day0.h"

struct resource_range {
    long long range_delta{0};
    std::size_t range_end{0};
};

void transfer_to_next_stage_part1(std::vector<std::size_t>& resources, std::unordered_map<std::size_t, resource_range>& translation) {
    for (std::size_t& resource : resources) {
        for (const auto& [range_start, range] : translation) {
            if (range_start <= resource && resource <= range.range_end) {
                resource += range.range_delta;
                break;
            }
        }
    }
}

void transfer_to_next_stage_part2(std::vector<std::size_t>& resources, std::unordered_map<std::size_t, resource_range>& translation, std::size_t start = 0) {
    std::size_t length{resources.size()};
    for (std::size_t i = start; i < length; i += 2) {
        for (const auto& [range_start, range] : translation) {
            // Range does not fit current resource range
            if (resources[i] + resources[i + 1] <= range_start || resources[i] >= range.range_end)
                continue;
            // If the range fits in entirely we can simply apply to transformation
            if (range_start <= resources[i] && resources[i] + resources[i + 1] <= range.range_end) {
                resources[i] += range.range_delta;
                break;
            }
            // Cut of font part of the range since it does not fit the range (but back part does)
            if (resources[i] < range_start) {
                resources.push_back(resources[i]);
                resources.push_back(range_start - resources[i]);
                resources[i + 1] -= range_start - resources[i];
                resources[i] = range_start + range.range_delta;
            }
            // Cut of back part of the range since it does not fit the range (but some part did)
            if (range.range_end < resources[i] + resources[i + 1]) {
                resources.push_back(range.range_end);
                resources.push_back(resources[i] + resources[i + 1] - range.range_end);
                resources[i + 1] -= resources[i] + resources[i + 1] - range.range_end;
                resources[i] += range.range_delta;
            }
            break;
        }
    }
    // Check if intervals that have been cut off can still be matched with some other interval
    if (resources.size() != length) {
        transfer_to_next_stage_part2(resources, translation, length);
    }
}

void parse_input(const std::vector<std::string>& lines, std::vector<std::size_t>& seeds, std::vector<std::unordered_map<std::size_t, resource_range>>& maps) {
    seeds = to_number_vector(split(split(lines[0], ':')[1]));
    std::unordered_map<std::size_t, resource_range> translation{};
    for (std::size_t i = 1; i < lines.size(); i++) {
        if (!lines[i].empty() && lines[i][0] != '\r' && lines[i][0] != '\n') {
            std::vector<std::size_t> numbers{to_number_vector(split(lines[i]))};
            long long delta{static_cast<long long>(numbers[0]) - static_cast<long long>(numbers[1])};
            translation.insert({numbers[1], {delta, numbers[1] + numbers[2]}});
            continue;
        } else if (i++ >= 3) {
            maps.push_back(translation);
            translation = {};
        }
    }
    if (!translation.empty())
        maps.push_back(translation);
}

void solve(const std::vector<std::string>& lines) {
    std::vector<std::size_t> seeds{};
    std::vector<std::unordered_map<std::size_t, resource_range>> maps{};
    parse_input(lines, seeds, maps);
    std::vector<std::size_t> resources{seeds};

    for (std::size_t i = 0; i < 7; i++)
        transfer_to_next_stage_part1(resources, maps[i]);
    std::cout << "1) Result is: " << *std::min_element(resources.begin(), resources.end()) << std::endl;

    for (std::size_t i = 0; i < 7; i++)
        transfer_to_next_stage_part2(seeds, maps[i]);
    resources = {};
    for (std::size_t i = 0; i < seeds.size(); i += 2)
        resources.push_back(seeds[i]);
    std::cout << "2) Result is: " << *std::min_element(resources.begin(), resources.end()) << std::endl;
}

int main() {
    solve(read_input_file("../day05/day05_input"));
}
