from collections import Counter

from helper import get_input_as_str


def part1(puzzle):
    result = 0
    rows = list(filter(None, puzzle.split('\n')))
    for y in range(len(rows)):
        for x in range(len(rows[y])):
            if (x + 3 < len(rows[y])
                    and rows[y][x] + rows[y][x + 1] + rows[y][x + 2] + rows[y][x + 3] == 'XMAS'):   # RIGHT
                result += 1
            if (x >= 3
                    and rows[y][x] + rows[y][x - 1] + rows[y][x - 2] + rows[y][x - 3] == 'XMAS'):   # LEFT
                result += 1
            if (y + 3 < len(rows)
                    and rows[y][x] + rows[y + 1][x] + rows[y + 2][x] + rows[y + 3][x] == 'XMAS'):   # DOWN
                result += 1
            if (y >= 3
                    and rows[y][x] + rows[y - 1][x] + rows[y - 2][x] + rows[y - 3][x] == 'XMAS'):   # UP
                result += 1

            if (x + 3 < len(rows[y]) and y + 3 < len(rows)
                    and rows[y][x] + rows[y + 1][x + 1] + rows[y + 2][x + 2] + rows[y + 3][x + 3] == 'XMAS'):   # DOWN-RIGHT
                result += 1
            if (x >= 3 and y + 3 < len(rows)
                    and rows[y][x] + rows[y + 1][x - 1] + rows[y + 2][x - 2] + rows[y + 3][x - 3] == 'XMAS'):   # DOWN-LEFT
                result += 1
            if (x + 3 < len(rows[y]) and y >= 3
                    and rows[y][x] + rows[y - 1][x + 1] + rows[y - 2][x + 2] + rows[y - 3][x + 3] == 'XMAS'):   # UP-RIGHT
                result += 1
            if (x >= 3 and y >= 3
                    and rows[y][x] + rows[y - 1][x - 1] + rows[y - 2][x - 2] + rows[y - 3][x - 3] == 'XMAS'):   # UP-lEFT
                result += 1

    print(f'Result for day 1 Part 1: {result}')


def part2(puzzle):
    rows = list(filter(None, puzzle.split('\n')))
    occurrences = []
    for y in range(len(rows)):
        for x in range(len(rows[y])):
            if (x + 2 < len(rows[y]) and y + 2 < len(rows)
                    and rows[y][x] + rows[y + 1][x + 1] + rows[y + 2][x + 2] == 'MAS'):     # DOWN-RIGHT
                occurrences.append([y + 1, x + 1])
            if (x >= 2 and y + 2 < len(rows)
                    and rows[y][x] + rows[y + 1][x - 1] + rows[y + 2][x - 2] == 'MAS'):     # DOWN-LEFT
                occurrences.append([y + 1, x - 1])
            if (x + 2 < len(rows[y]) and y >= 2
                    and rows[y][x] + rows[y - 1][x + 1] + rows[y - 2][x + 2] == 'MAS'):     # UP-RIGHT
                occurrences.append([y - 1, x + 1])
            if (x >= 2 and y >= 2
                    and rows[y][x] + rows[y - 1][x - 1] + rows[y - 2][x - 2] == 'MAS'):     # UP-lEFT
                occurrences.append([y - 1, x - 1])

    counts = Counter(map(tuple, occurrences))
    result = len([s for s in occurrences if counts[tuple(s)] > 1]) // 2

    print(f'Result for day 1 Part 2: {result}')


def main():
    puzzle = get_input_as_str()
    part1(puzzle)
    part2(puzzle)


if __name__ == '__main__':
    main()
