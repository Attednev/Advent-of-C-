#include "../day0.h"

struct player {
    std::string hand;
    std::size_t bet{0};
    std::size_t score{0};
};

// 6: five of a kind | 5: four of a kind | 4: full house | 3: three of a kind | 2: two pair | 1: one pair | 0: high card
std::size_t get_score_from_hand(std::unordered_map<char, std::size_t>& cards, std::string& hand) {
    switch (cards.size()) {
        case 1: return 6;
        case 2: return cards[hand[0]] == 4 || cards[hand[0]] == 1 ? 5 : 4;
        case 3: return 3 - (cards[hand[0]] * cards[hand[1]] * cards[hand[2]] * cards[hand[3]] * cards[hand[4]] % 3);
        case 4: return 1;
        default: return 0;
    }
}

void update_player_ranking(std::vector<player>& players, bool count_jokers) {
    std::unordered_map<char, std::size_t> card_values{{{'2', 1}, {'3', 2}, {'4', 3}, {'5', 4}, {'6', 5}, {'7', 6},
                                                       {'8', 7}, {'9', 8}, {'T', 9}, {'Q', 11}, {'K', 12},
                                                       {'A', 13}, {'J', count_jokers ? 0 : 10}}};
    std::sort(players.begin(), players.end(), [&](player& a, player& b) {
        if (a.score == b.score) {
            for (std::size_t i = 0; i < a.hand.length(); i++) {
                if (card_values[a.hand[i]] == card_values[b.hand[i]]) continue;
                return card_values[a.hand[i]] < card_values[b.hand[i]];
            }
        }
        return a.score < b.score;
    });
}

std::size_t get_total_earnings(std::vector<player>& players, bool count_jokers) {
    update_player_ranking(players, count_jokers);
    std::size_t total{0};
    for (std::size_t i = 0; i < players.size(); i++)
        total += (i + 1) * players[i].bet;
    return total;
}

char get_highest_card(std::unordered_map<char, std::size_t>& cards) {
    std::unordered_map<char, std::size_t> card_values{{{'2', 1}, {'3', 2}, {'4', 3}, {'5', 4}, {'6', 5}, {'7', 6},
                                                       {'8', 7}, {'9', 8}, {'T', 9}, {'J', 10}, {'Q', 11}, {'K', 12},
                                                       {'A', 13}, {'J', 0}}};
    char highest;
    std::size_t highest_duplicates{0};
    std::size_t highest_score{0};
    for (auto& [c, a] : cards) {
        if (c == 'J') continue;
        if (a > highest_duplicates || (a == highest_duplicates && card_values[c] > highest_score)) {
            highest_score = card_values[c];
            highest_duplicates = a;
            highest = c;
        }
    }
    return highest;
}

std::string get_hand_from_cards(std::unordered_map<char, std::size_t>& cards) {
    std::string hand;
    for (auto& [c, a] : cards)
        for (std::size_t i = 0; i < a; i++)
            hand += c;
    return hand;
}

std::string get_best_joker_option(std::unordered_map<char, std::size_t>& cards) {
    if (cards.size() != 1) {
        cards[get_highest_card(cards)] += cards['J'];
        cards.erase('J');
    }
    return get_hand_from_cards(cards);
}

void evaluate_player_scores(std::vector<player>& players, bool count_jokers) {
    for (player& player : players) {
        std::unordered_map<char, std::size_t> cards{};
        for (const char card : player.hand) {
            if (contains(cards, card)) cards[card]++;
            else cards.insert({card, 1});
        }
        std::string hand{player.hand};
        if (count_jokers) {
            hand = get_best_joker_option(cards);
        }
        player.score = get_score_from_hand(cards, hand);
    }
}

void solve(const std::vector<std::string>& lines, bool part2) {
    std::vector<player> players{};
    players.reserve(lines.size());
    for (const std::string& line : lines)
        players.push_back({split(line)[0], std::stoul(split(line)[1])});
    evaluate_player_scores(players, part2);
    std::cout << (part2 ? "2)" : "1)") << " Result is " << get_total_earnings(players, part2) << std::endl;
}

int main() {
    solve(read_input_file("../inputs/day07"), false);
    solve(read_input_file("../inputs/day07"), true);
}