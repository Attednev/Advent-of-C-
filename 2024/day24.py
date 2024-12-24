from helper import get_input
import re


def parse_data(data):
    status = {}
    logic = []
    for line in data:
        if ':' in line:
            splits = line.split(':')
            status[splits[0]] = int(splits[1])
        elif '->' in line:
            logic += re.findall(r'^(\w+)\s+(\w+)\s+(\w+)\s+->\s+(\w+)$', line)
    return status, logic


def solve(status, logic):
    elements = list(status.keys())
    finished = set(elements)
    dependencies = []
    while True:
        current = [l for l in logic if l[0] in elements and l[2] in elements and l[3] not in finished]
        new_wires = [r for _, _, _, r in current]
        if len(current) == 0:
            break
        finished.update(new_wires)
        dependencies.append(current)
        elements += new_wires

    for iteration in dependencies:
        for current in iteration:
            if current[1] == 'OR':
                status[current[3]] = status[current[0]] | status[current[2]]
            if current[1] == 'AND':
                status[current[3]] = status[current[0]] & status[current[2]]
            if current[1] == 'XOR':
                status[current[3]] = status[current[0]] ^ status[current[2]]
    

def part1(status, logic):
    solve(status, logic)
    result = 0
    for i, j in enumerate(sorted([s for s in status if s.startswith('z')])):
        result += status[j] * (2 ** i)
    print(f'Result for day 24 Part 1: {result}')


def part2(status, logic):
    def get_exact_gate(x, y, g):
        return [(l, o, r, n) for l, o, r, n in logic if ((l == x or l == y) and (r == x or r == y)) and o == g][0]

    def get_uncertain_gate(x, y, g):
        return [(l, o, r, n) for l, o, r, n in logic if ((l == x or l == y) or (r == x or r == y)) and o == g][0]

    def update_faulting(gate, x, y, faulting):
        if (gate[0] == x and gate[2] != y) or (gate[2] == x and gate[0] != y):
            faulting += [y]
            y = gate[0] if gate[2] == x else gate[2]

        if (gate[0] == y and gate[2] != x) or (gate[2] == y and gate[0] != x):
            faulting += [x]
            x = gate[0] if gate[2] == y else gate[2]
        return x, y, faulting

    # From a limited observation of the circuit it seems that it simulates a
    # simple n-bit adder consisting of multiple full-adders.
    # If we can analyze the circuit from front to back and check if it is
    # consitent with how a full-adder should look like. We can then
    # find the gate that do not adhere to the diagram.
    # After finding these gates it need to replace what would have been expected
    # under normal circumstances with what actually is there so that we do not
    # count gates as faulting that depend on faulting gates
    #
    # How a full-adder works:
    # IN: X, Y, Cin
    # OUT: Out, Cout
    #
    # A = X XOR Y
    # B = X AND Y
    # C = A AND Cin
    #
    # Out  = A XOR Cin = (X XOR Y) XOR Cin
    # Cout = B  OR C   = (X AND Y)  OR ((X XOR Y) AND Cin)

    faulting = []

    x = f'x00'
    y = f'y00'
    first_out = get_exact_gate(x, y, 'XOR')
    if first_out[3] != 'z00':
        faulting += [first_out[3]]

    Cin = get_exact_gate(x, y, 'AND')[3]

    last = sorted([l for _, _, _, l in logic if l.startswith('z')])[-1]
    for i in range(1, int(last[1:])):
        x = f'x{'0' if i < 10 else ''}{i}'
        y = f'y{'0' if i < 10 else ''}{i}'

        A_out = get_exact_gate(x, y, 'XOR')[3]
        B_out = get_exact_gate(x, y, 'AND')[3]

        out_gate = get_uncertain_gate(A_out, Cin, 'XOR')
        A_out, Cin, faulting = update_faulting(out_gate, A_out, Cin, faulting)

        if out_gate[3] != f'z{'0' if i < 10 else ''}{i}':
            faulting += [out_gate[3]]

        C_gate = get_uncertain_gate(A_out, Cin, 'AND')
        A_out, Cin, faulting = update_faulting(C_gate, A_out, Cin, faulting)

        C_out = C_gate[3]

        Cout_gate = get_uncertain_gate(B_out, C_out, 'OR')
        A_out, Cin, faulting = update_faulting(Cout_gate, B_out, C_out, faulting)

        Cin = Cout_gate[3]

    faulting.sort()
    print(f'Result for day 24 Part 2: {','.join(faulting)}')


def main():
    data = get_input()
    state, logic = parse_data(data)
    part1(state, logic)
    state, logic = parse_data(data)
    part2(state, logic)


if __name__ == '__main__':
    main()
