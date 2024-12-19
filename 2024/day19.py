import re

from helper import get_input


cache = {}


def parse_data(data):
    towels = [k for k in re.findall(r"([rwubg]+)", data[0])]
    requested = []
    for line in data[1:]:
        requested.append(line)
    return towels, requested


def solve(towels, request, index):
    global cache
    if index == len(request):
        return 1

    number_of_combinations = 0
    if request[index:] in cache:
        return cache[request[index:]]

    next_combinations = [t for t in towels if request[index:].startswith(t)]
    if len(next_combinations) > 0:
        for combination in next_combinations:
            number_of_combinations += solve(towels, request, index + len(combination))
        cache[request[index:]] = number_of_combinations

    return number_of_combinations


def main():
    data = get_input()
    towels, requested = parse_data(data)

    result_part1 = 0
    result_part2 = 0
    for request in requested:
        ret = solve(towels, request, 0)
        if ret > 0:
            result_part1 += 1
        result_part2 += ret

    print(f'Result for day 19 Part 1: {result_part1}')
    print(f'Result for day 19 Part 2: {result_part2}')


if __name__ == '__main__':
    main()
