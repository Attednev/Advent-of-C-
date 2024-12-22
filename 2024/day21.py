from helper import get_input
from functools import cache


@cache
def sequence_length(sequence, depth):
    buttons = {'7': (2, 3), '8': (1, 3), '9': (0, 3), '4': (2, 2), '5': (1, 2), '6': (0, 2),
               '1': (2, 1), '2': (1, 1), '3': (0, 1), 'X': (2, 0), '0': (1, 0), 'A': (0, 0),
               '^': (1, 0), '<': (2, -1), 'v': (1, -1), '>': (0, -1)}

    if depth < 0:
        return len(sequence)

    length = 0
    current = buttons['A']
    for s in sequence:
        destination = buttons[s]
        dy = destination[1] - current[1]
        dx = destination[0] - current[0]

        x_path = ('>' * -dx) + ('<' * dx)
        y_path = ('v' * -dy) + ('^' * dy)

        l1 = l2 = float('inf')

        if (destination[0], current[1]) != buttons['X']:
            l1 = sequence_length(x_path + y_path + 'A', depth - 1)
        if (current[0], destination[1]) != buttons['X']:
            l2 = sequence_length(y_path + x_path + 'A', depth - 1)

        if l1 != float('inf') or l2 != float('inf'):
            length += min(l1, l2)

        current = destination

    return length



def solve(codes, directional_pads):
    result = 0
    for code in codes:
        length = sequence_length(code, directional_pads)
        complexity = length * int(code[:-1])
        result += complexity
    return result


def part1(codes):
    print(f'Result for day 21 Part 1: {solve(codes, 2)}')


def part2(codes):
    print(f'Result for day 21 Part 2: {solve(codes, 25)}')


def main():
    codes = get_input()
    part1(codes)
    part2(codes)


if __name__ == '__main__':
    main()
