import re

from helper import get_input

WIDTH = 71
HEIGHT = 71

LEFT = 0
DOWN = 1
RIGHT = 2
UP = 3


def let_bytes_fall(grid, time, tiles):
    if time >= len(tiles):
        exit(1)
    for i in range(time):
        x, y = [int(k) for k in re.findall(r"\d+", tiles[i])]
        grid[y][x] = -1
    return grid


def solve(tiles, time=1024):
    # Dijkstra
    directions = [[None for _ in range(WIDTH)] for _ in range(HEIGHT)]
    grid = [[999_999 for _ in range(WIDTH)] for _ in range(HEIGHT)]
    grid = let_bytes_fall(grid, time, tiles)

    unvisited = set()
    for y in range(HEIGHT):
        for x in range(WIDTH):
            if grid[y][x] > 0:
                unvisited.add((x, y))

    grid[0][0] = 0
    while True:
        min_tile = None
        for u in unvisited:
            if min_tile is None or grid[u[1]][u[0]] < grid[min_tile[1]][min_tile[0]]:
                min_tile = u
        if min_tile is None or grid[min_tile[1]][min_tile[0]] == 999_999:
            return None
        if min_tile == (WIDTH - 1, HEIGHT - 1):
            break
        x, y = min_tile
        neighbours = [(x + 1, y, LEFT), (x, y + 1, UP), (x - 1, y, RIGHT), (x, y - 1, DOWN)]
        for n_x, n_y, n_d in neighbours:
            if (n_x, n_y) not in unvisited:
                continue
            grid[n_y][n_x] = min(grid[n_y][n_x], grid[y][x] + 1)
            directions[n_y][n_x] = n_d
        unvisited.remove(min_tile)

    delta = {LEFT: (-1, 0), RIGHT: (1, 0), DOWN: (0, 1), UP: (0, -1), None: (0, 0)}
    shortest_path = []
    x, y = WIDTH - 1, HEIGHT - 1
    while directions[y][x] is not None:
        shortest_path.append((x, y))
        x, y = x + delta[directions[y][x]][0], y + delta[directions[y][x]][1]

    return shortest_path


def part1(tiles):
    shortest_path = solve(tiles)
    print(f'Result for day 1 Part 1: {len(shortest_path)}')


def part2(tiles):
    # binary search
    low = 1024
    high = len(tiles)
    while low <= high:
        mid = low + (high - low) // 2
        if solve(tiles, mid) is None:
            high = mid - 1
        else:
            low = mid + 1
    print(f'Result for day 1 Part 2: {tiles[low + (high - low) // 2]}')


def main():
    tiles = get_input()
    part1(tiles)
    part2(tiles)


if __name__ == '__main__':
    main()
