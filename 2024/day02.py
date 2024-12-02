from helper import get_input
from enum import Enum


def input_to_lists(lines):
    levels = []
    for line in lines:
        splits = line.split(' ')
        if len(splits) <= 1:
            break
        row = []
        for value in splits:
            row.append(int(value))
        levels.append(row)
    return levels


def is_safe(row):
    class CHANGE(Enum):
        INCREASE = 1
        DECREASE = 2
        NONE = 3
    change = CHANGE.INCREASE if row[1] > row[0] else CHANGE.DECREASE
    for i in range(1, len(row)):
        diff = abs(row[i] - row[i - 1])
        if (diff < 1 or diff > 3
                or (row[i] > row[i - 1] and change != CHANGE.INCREASE)
                or (row[i] < row[i - 1] and change != CHANGE.DECREASE)):
            return False
    return True


def part1(levels):
    safe_reports = 0
    for row in levels:
        if is_safe(row):
            safe_reports += 1

    print(f'Result for day 1 Part 1: {safe_reports}')


def part2(levels):
    safe_reports = 0
    for row in levels:
        for i in range(len(row)):
            tmp = row[:i] + row[(i + 1):]
            if is_safe(tmp):
                safe_reports += 1
                break

    print(f'Result for day 1 Part 2: {safe_reports}')


def main():
    lines = get_input()
    levels = input_to_lists(lines)
    part1(levels)
    part2(levels)


if __name__ == '__main__':
    main()
