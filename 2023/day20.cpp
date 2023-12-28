#include "day0.h"

struct module {
    char type{};
    bool internal_state{false};
    std::vector<std::string> connections{};
    std::unordered_map<std::string, bool> ingoing_modules_conjunction{};
    std::deque<bool> ingoing_modules_flipflop{};

    explicit module() : type{' '} {}
    explicit module(char t, auto&& c) : type{t}, connections{std::forward<decltype(c)>(c)} {}

    short trigger() {
        if (type == '&') return std::any_of(ingoing_modules_conjunction.begin(), ingoing_modules_conjunction.end(), [](auto& element) { return element.second == false; });
        if (type == 'b') return false;
        bool next_input{ingoing_modules_flipflop[0]};
        ingoing_modules_flipflop.pop_front();
        if (next_input) return -1;
        return (internal_state = !internal_state);
    }
};

void run(auto& modules, auto& signal_count, bool& is_high) {
    std::deque<std::string> working_order{"broadcaster"};
    while (!working_order.empty()) {
        auto current_node{working_order.front()};
        working_order.pop_front();

        short new_high{modules[current_node].trigger()};
        if (new_high == -1) continue;
        is_high = new_high;

        for (auto& dest : modules[current_node].connections) {
            modules[dest].ingoing_modules_flipflop.push_back(is_high);
            modules[dest].ingoing_modules_conjunction[current_node] = is_high;
            working_order.push_back(dest);
            signal_count[is_high ? 1 : 0]++;
        }
    }
}

std::size_t press_button_n_times(auto& modules, std::size_t n) {
    std::vector<std::size_t> signal_count(2, 0);
    bool is_high{false};
    for (std::size_t i = 1; i <= n; i++) {
        run(modules, signal_count, is_high);
        if (!std::any_of(modules.begin(), modules.end(), [](auto& element) { return element.second.internal_state; })) {
            std::cout << "Loop detected in iteration " << i << std::endl;
            signal_count = {(signal_count[0] + i) * n / i, signal_count[1] * n / i};
            i = n - (n % i);
        }
    }
    return signal_count[0] * signal_count[1];
}

void solve(const std::vector<std::string>& lines) {
    std::unordered_map<std::string, module> modules{};
    for (auto& line : lines) {
        auto splits{split(line, " -> ")};
        auto type{splits[0][0]};
        auto name{splits[0][0] == 'b' ? splits[0] : splits[0].substr(1)};
        auto connections{split(trim(splits[1]), ", ")};

        modules.emplace(name, std::move(module {type, connections}));
    }

    for (auto& [n, m] : modules) {
        if (m.type != '&') continue;
        for (auto& [n2, m2] : modules)
            if (contains(m2.connections, n))
                m.ingoing_modules_conjunction.emplace(n2, false);
    }

    std::cout << "1) Result is " << press_button_n_times(modules, 1000) << std::endl;


    // Input follows certain scheme: Broadcaster sends signals to chains of flipflops. Some of these chain elements
    // are connected to a (loop-)central conjunction. All conjunctions are connected to a central conjunction (with
    // one interim conjunction though) which outputs the result to rx.
    // The chain of flipflops is basically a binary counter, and the connections of the flipflops to the central
    // conjunction tells us which of the flipflops need to be active in order to generate a high signal at the
    // conjunction. Since the output of the conjunctions is then simply forwarded to the end, we need to find a
    // configuration where all the (loop-)central conjunctions are active, which means we need to find the lcm of
    // the binary values represented by the flipflop chains
    std::size_t minimal_button_presses{1};
    for (auto loop : modules["broadcaster"].connections) {
        std::size_t binary_value{0};
        for (std::size_t i = 0; modules[loop].type != '&'; i++) {
            binary_value |= (1 << i) * (modules[loop].connections.size() == 2 || modules[modules[loop].connections[0]].type == '&');
            loop = modules[loop].connections[modules[loop].connections.size() != 1 && modules[modules[loop].connections[0]].type == '&'];
        }
        minimal_button_presses = std::lcm(minimal_button_presses, binary_value);
    }

    std::cout << "2) Result is " << minimal_button_presses << std::endl;
}

int main() {
    solve(read_input_file("../inputs/day20"));
}