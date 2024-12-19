from functools import reduce

from helper import get_input_unfiltered


EMPTY = 0
WALL = 1
BOX = 2
ROBOT = 3
WIDE_BOX_1 = 4
WIDE_BOX_2 = 5


def widen(data):
    new_data = []
    for i in range(len(data)):
        if len(data[i]) == 0:
            new_data += data[i:]
            break
        line = ''
        for j in range(len(data[i])):
            replacements = {'#': '##', '@': '@.', 'O': '[]', '.': '..'}
            line += replacements[data[i][j]]
        new_data.append(line)
    return new_data


def parse_input(data):
    walls_horizontal = {}
    walls_vertical = {}
    grid = [[EMPTY for _ in range(len(data[y]))] for y in range(len(data))]
    position = None
    movements = ''
    for i in range(len(data)):
        if len(data[i]) == 0:
            movements = ''.join(data[i + 1:])
            grid = grid[:i]
            break
        for j in range(len(data[i])):
            if data[i][j] == '#':
                grid[i][j] = WALL
                walls_horizontal.setdefault(i, []).append(j)
                walls_vertical.setdefault(j, []).append(i)
            if data[i][j] == '@':
                position = [j, i]
            if data[i][j] == 'O':
                grid[i][j] = BOX
            if data[i][j] == '[':
                grid[i][j] = WIDE_BOX_1
            if data[i][j] == ']':
                grid[i][j] = WIDE_BOX_2

    return position, grid, walls_horizontal, walls_vertical, movements


def move(position, direction, grid, walls):
    relevant_direction = 1 if direction[0] == 0 else 0
    tmp = position[relevant_direction] + direction[relevant_direction]
    start_x = tmp if relevant_direction == 0 else position[0]
    start_y = tmp if relevant_direction == 1 else position[1]
    x = start_x
    y = start_y

    if grid[y][x] == WALL:
        return position, grid

    wide_horizontal = (grid[y][x] == WIDE_BOX_1 or grid[y][x] == WIDE_BOX_2) and relevant_direction == 0
    if grid[y][x] == BOX or wide_horizontal:
        while grid[y][x] == BOX or grid[y][x] == WIDE_BOX_1 or grid[y][x] == WIDE_BOX_2:
            if relevant_direction == 0:
                x += direction[relevant_direction]
            else:
                y += direction[relevant_direction]

        wall_pos = None
        for wall in walls[position[1 - relevant_direction]]:
            if direction[relevant_direction] > 0 and wall > position[relevant_direction]:
                wall_pos = wall
                break
            if direction[relevant_direction] < 0 and wall > position[relevant_direction]:
                break
            wall_pos = wall

        if (relevant_direction == 0 and x == wall_pos) or (relevant_direction == 1 and y == wall_pos):
            return position, grid

        if wide_horizontal:
            while [x, y] != position:
                if relevant_direction == 0:
                    grid[y][x] = grid[y][x - direction[relevant_direction]]
                    x -= direction[relevant_direction]
                else:
                    grid[y][x] = grid[y - direction[relevant_direction]][x]
                    y -= direction[relevant_direction]
        else:
            grid[y][x] = BOX
        grid[start_y][start_x] = EMPTY

    if (grid[y][x] == WIDE_BOX_1 or grid[y][x] == WIDE_BOX_2) and relevant_direction == 1:
        to_check = [position]
        pushing = []
        while len(to_check) > 0:
            c_x, c_y = to_check.pop(0)
            if grid[c_y + direction[1]][c_x] == WALL:
                return position, grid
            if grid[c_y + direction[1]][c_x] == WIDE_BOX_1:
                to_check.append([c_x, c_y + direction[1]])
                to_check.append([c_x + 1, c_y + direction[1]])
            if grid[c_y + direction[1]][c_x] == WIDE_BOX_2:
                to_check.append([c_x, c_y + direction[1]])
                to_check.append([c_x - 1, c_y + direction[1]])
            if [c_x, c_y] not in pushing:
                pushing.append([c_x, c_y])

        pushing.reverse()
        for c_x, c_y in pushing:
            grid[c_y + direction[1]][c_x] = grid[c_y][c_x]
            grid[c_y][c_x] = EMPTY

    position[relevant_direction] = start_x if relevant_direction == 0 else start_y

    return position, grid


def solve(position, grid, walls_horizontal, walls_vertical, movements, relevant_object):
    delta = {'<': (-1, 0), '>': (1, 0), '^': (0, -1), 'v': (0, 1)}
    for movement in movements:
        position, gird = move(position, delta[movement], grid, walls_vertical if delta[movement][0] == 0 else walls_horizontal)

    return reduce(lambda c, p: c + 100 * p[1] + p[0],
                  [(x, y) for y in range(len(grid)) for x in range(len(grid[y])) if grid[y][x] == relevant_object], 0)


def part1(position, grid, walls_horizontal, walls_vertical, movements):
    result = solve(position, grid, walls_horizontal, walls_vertical, movements, BOX)
    print(f'Result for day 15 Part 1: {result}')


def part2(position, grid, walls_horizontal, walls_vertical, movements):
    result = solve(position, grid, walls_horizontal, walls_vertical, movements, WIDE_BOX_1)
    print(f'Result for day 15 Part 2: {result}')


def main():
    data = get_input_unfiltered()

    starting_position, grid, walls_horizontal, walls_vertical, movements = parse_input(data)
    part1(starting_position, grid, walls_horizontal, walls_vertical, movements)

    starting_position, grid, walls_horizontal, walls_vertical, movements = parse_input(widen(data))
    part2(starting_position, grid, walls_horizontal, walls_vertical, movements)


if __name__ == '__main__':
    main()
