from re import findall
from functools import reduce
from operator import mul

from helper import get_input_as_str


def part1(memory):
    result = 0
    locations = findall(r'mul\([0-9]+,[0-9]+\)', memory)
    for location in locations:
        result += reduce(mul, [int(x) for x in location[4:-1].split(',')])

    print(f'Result for day 1 Part 1: {result}')


def part2(memory):
    result = 0
    do = True
    locations = findall(r'(mul\([0-9]+,[0-9]+\)|do\(\)|don\'t\(\))', memory)
    for location in locations:
        if not (location.startswith('mul') and do):
            do = True if location == 'do()' else False
            continue
        result += reduce(mul, [int(x) for x in location[4:-1].split(',')])

    print(f'Result for day 1 Part 2: {result}')


def main():
    lines = get_input_as_str()
    part1(lines)
    part2(lines)


if __name__ == '__main__':
    main()
