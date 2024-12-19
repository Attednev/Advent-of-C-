from helper import get_input

MIN_HEIGHT = 0
MAX_HEIGHT = 9
INCLINE = 1


def traverse(top_map, x, y):
    end_positions = []
    if top_map[y][x] == MAX_HEIGHT:
        end_positions.append((x, y))

    if x > 0 and top_map[y][x - 1] == top_map[y][x] + INCLINE:
        end_positions += traverse(top_map, x - 1, y)
    if y > 0 and top_map[y - 1][x] == top_map[y][x] + INCLINE:
        end_positions += traverse(top_map, x, y - 1)
    if x + 1 < len(top_map[y]) and top_map[y][x + 1] == top_map[y][x] + INCLINE:
        end_positions += traverse(top_map, x + 1, y)
    if y + 1 < len(top_map) and top_map[y + 1][x] == top_map[y][x] + INCLINE:
        end_positions += traverse(top_map, x, y + 1)

    return end_positions


def solve(data):
    starting_positions = [(x, y) for y in range(len(data)) for x in range(len(data[y])) if data[y][x] == MIN_HEIGHT]

    result_part1, result_part2 = 0, 0
    for s_x, s_y in starting_positions:
        end_pos = traverse(data, s_x, s_y)
        result_part1 += len(set(end_pos))
        result_part2 += len(end_pos)

    print(f'Result for day 10 Part 1: {result_part1}')
    print(f'Result for day 10 Part 2: {result_part2}')


def main():
    data = get_input()
    numbers = [[int(n) for n in line] for line in data]
    solve(numbers)


if __name__ == '__main__':
    main()
