from helper import get_input
import re
import numpy as np


def parse_games(games):
    ret = []
    for i in range(0, len(games), 3):
        if i + 2 >= len(games):
            break
        regex = re.search(r"X([+|-]\d+), Y([+|-]\d+)", games[i])
        button_a = (int(regex.group(1)), int(regex.group(2)))
        regex = re.search(r"X([+|-]\d+), Y([+|-]\d+)", games[i + 1])
        button_b = (int(regex.group(1)), int(regex.group(2)))
        regex = re.search(r"X=(\d+), Y=(\d+)", games[i + 2])
        price = (int(regex.group(1)), int(regex.group(2)))
        ret.append((button_a, button_b, price))
    return ret


def solve(vel, dest):
    a, b = np.linalg.solve(vel, dest)
    a, b = int(round(a)), int(round(b))
    if a * vel[0][0] + b * vel[0][1] != dest[0] or a * vel[1][0] + b * vel[1][1] != dest[1]:
        return None, None
    return a, b


def part1(games):
    result = 0
    for a, b, p in games:
        f1, f2 = solve(np.array([[a[0], b[0]], [a[1], b[1]]]), np.array([p[0], p[1]]))
        if f1 is None or f2 is None:
            continue
        if f1 > 100 or f2 > 100:
            continue
        result += 3 * f1 + 1 * f2
    print(f'Result for day 13 Part 1: {result}')


def part2(games):
    result = 0
    for a, b, p in games:
        f1, f2 = solve(np.array([[a[0], b[0]], [a[1], b[1]]]), np.array([p[0] + 10000000000000, p[1] + 10000000000000]))
        if f1 is None or f2 is None:
            continue
        result += 3 * f1 + 1 * f2
    print(f'Result for day 13 Part 2: {result}')


def main():
    games = get_input()
    games = parse_games(games)
    part1(games)
    part2(games)


if __name__ == '__main__':
    main()
