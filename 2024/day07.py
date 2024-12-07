import operator

from helper import get_input


def parse_equations(equations):
    eq = []
    for equation in equations:
        splits = equation.split(': ')
        result = int(splits[0])
        numbers = [int(x) for x in splits[1].split(' ') if x != '']
        eq.append((result, numbers))
    return eq


def operator_concat(a, b):
    return int(str(a) + str(b))


def combine(numbers, interim, result, concat=False):
    if len(numbers) == 0:
        return interim == result

    operators = ([operator_concat] if concat else []) + [operator.mul, operator.add]
    for op in operators:
        if combine(numbers[1:], op(interim, numbers[0]), result, concat):
            return True

    return False


def part1(equations, concat=False):
    total = 0
    for result, numbers in equations:
        if combine(numbers[1:], numbers[0], result, concat):
            total += result
    return total


def part2(equations):
    return part1(equations, concat=True)


def main():
    data = get_input()
    equations = parse_equations(data)
    print(f'Result for day 1 Part 1: {part1(equations)}')
    print(f'Result for day 1 Part 2: {part2(equations)}')


if __name__ == '__main__':
    main()
