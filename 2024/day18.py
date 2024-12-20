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


def dijkstra(maze, start, end):
    prev_position = [[None for _ in range(len(maze[0]))] for _ in range(len(maze))]
    unvisited = set()
    for y in range(len(maze)):
        for x in range(len(maze[0])):
            if maze[y][x] > 0:
                unvisited.add((x, y))

    maze[start[1]][start[0]] = 0
    while True:
        min_tile = None
        for u in unvisited:
            if min_tile is None or maze[u[1]][u[0]] < maze[min_tile[1]][min_tile[0]]:
                min_tile = u
        if min_tile is None or maze[min_tile[1]][min_tile[0]] == 999_999:
            return None, None
        if min_tile == end:
            break
        x, y = min_tile
        neighbours = [(x + 1, y), (x, y + 1), (x - 1, y), (x, y - 1)]
        for n_x, n_y in neighbours:
            if (n_x, n_y) not in unvisited:
                continue
            maze[n_y][n_x] = min(maze[n_y][n_x], maze[y][x] + 1)
            prev_position[n_y][n_x] = (x, y)
        unvisited.remove(min_tile)

    shortest_path = []
    x, y = end
    while prev_position[y][x] is not None:
        shortest_path.append((x, y))
        x, y = prev_position[y][x]

    return shortest_path, maze


def part1(tiles):
    grid = [[999_999 for _ in range(WIDTH)] for _ in range(HEIGHT)]
    grid = let_bytes_fall(grid, 1024, tiles)
    shortest_path, _ = dijkstra(grid, (0, 0), (WIDTH - 1, HEIGHT - 1))
    print(f'Result for day 18 Part 1: {len(shortest_path)}')


def part2(tiles):
    # binary search
    low = 1024
    high = len(tiles)
    while low <= high:
        mid = low + (high - low) // 2
        grid = [[999_999 for _ in range(WIDTH)] for _ in range(HEIGHT)]
        grid = let_bytes_fall(grid, mid, tiles)
        shortest_path, _ = dijkstra(grid, (0, 0), (WIDTH - 1, HEIGHT - 1))
        if shortest_path is None:
            high = mid - 1
        else:
            low = mid + 1
    print(f'Result for day 18 Part 2: {tiles[low + (high - low) // 2]}')


def main():
    tiles = get_input()
    part1(tiles)
    part2(tiles)


if __name__ == '__main__':
    main()
