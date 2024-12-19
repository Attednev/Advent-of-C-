from helper import get_input


UP = 0
RIGHT = 1
DOWN = 2
LEFT = 3


def get_starting_position(data):
    for i in range(len(data)):
        if '^' in data[i]:
            return data[i].find('^'), i
    print('No starting position found')
    exit(0)


def is_wall(data, x, y):
    return data[y][x] == '#'


def part1(data, x, y):
    visited = []
    try:
        while True:

            while not is_wall(data, x, y - 1):
                if (x, y) not in visited:
                    visited.append((x, y))
                y -= 1

            while not is_wall(data, x + 1, y):
                if (x, y) not in visited:
                    visited.append((x, y))
                x += 1

            while not is_wall(data, x, y + 1):
                if (x, y) not in visited:
                    visited.append((x, y))
                y += 1

            while not is_wall(data, x - 1, y):
                if (x, y) not in visited:
                    visited.append((x, y))
                x -= 1

    except IndexError:
        pass

    visited.append((x, y))     # Final location
    return visited


def get_next_wall(data, x, y, direction, obstacle_x, obstacle_y):
    dx = {UP: 0, DOWN: 0, RIGHT: 1, LEFT: -1}
    dy = {UP: -1, DOWN: 1, RIGHT: 0, LEFT: 0}
    while True:
        if x < dx[direction] or y < dy[direction] or x + dx[direction] >= len(data[0]) or y + dy[direction] >= len(data):
            return x, y, None, None
        if is_wall(data, x + dx[direction], y + dy[direction]):
            break
        if x + dx[direction] == obstacle_x and y + dy[direction] == obstacle_y:
            break
        x += dx[direction]
        y += dy[direction]
    return x, y, x + dx[direction], y + dy[direction]


def is_loop(data, x, y, obstacle_x, obstacle_y):
    trace = []
    while True:
        for direction in [UP, RIGHT, DOWN, LEFT]:
            x, y, wall_x, wall_y = get_next_wall(data, x, y, direction, obstacle_x, obstacle_y)
            if (wall_x, wall_y) == (None, None):
                return False
            if (wall_x, wall_y, direction) in trace:
                return True
            trace.append((wall_x, wall_y, direction))


def part2(data, x, y):
    potential_obstacles = set()
    visited = part1(data, x, y)
    for v_x, v_y in visited:
        if (v_x, v_y) == (x, y) or is_wall(data, v_x, v_y):
            continue

        if is_loop(data, x, y, v_x, v_y):
            potential_obstacles.add((v_x, v_y))

    return potential_obstacles


def main():
    data = get_input()
    x, y = get_starting_position(data)
    data[y] = data[y][:x] + "." + data[y][x + 1:]
    print(f'Result for day 6 Part 1: {len(part1(data, x, y))}')
    print(f'Result for day 6 Part 2: {len(part2(data, x, y))}')


if __name__ == '__main__':
    main()
