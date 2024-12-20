from collections import deque

from helper import get_input
from day16 import parse_maze, WALL
from day18 import dijkstra


def get_reachable_positions(x, y, min_steps, max_steps):
    visited = set()
    queue = deque([(x, y, 0)])
    walk = dict()
    while queue:
        c_x, c_y, steps = queue.popleft()
        if steps >= max_steps:
            continue
        for dx, dy in [(0, 1), (1, 0), (0, -1), (-1, 0)]:
            n_x, n_y = c_x + dx, c_y + dy
            if (n_x, n_y) not in visited:
                queue.append((n_x, n_y, steps + 1))
                visited.add((n_x, n_y))
                walk[(n_x, n_y)] = steps + 1
    return [(x, y, walk[(x, y)]) for x, y in list(visited) if walk[(x, y)] >= min_steps]


def find_shortcuts(maze, steps=2):
    shortcuts = []
    for y in range(len(maze)):
        for x in range(len(maze[y])):
            if maze[y][x] == WALL:
                continue
            neighbours = get_reachable_positions(x, y, 2, steps)
            for n_x, n_y, i in neighbours:
                if not (0 <= n_y < len(maze) and 0 <= n_x < len(maze[0])):
                    continue
                if maze[n_y][n_x] == WALL:
                    continue
                if maze[n_y][n_x] > maze[y][x] - i:
                    continue
                shortcuts.append((maze[y][x] - maze[n_y][n_x] - i, (x, y), (n_x, n_y)))
    return shortcuts


def solve(maze, start, end):
    _, maze = dijkstra(maze, end, start)

    shortcuts = find_shortcuts(maze)
    result = len([s for s, _, _ in shortcuts if s >= 100])
    print(f'Result for day 20 Part 1: {result}')

    filtered = {}
    for s, f, t in find_shortcuts(maze, 20):
        filtered.setdefault((f, t), s)
        filtered[(f, t)] = max(filtered[(f, t)], s)

    result = len([s for _, s in filtered.items() if s >= 100])
    print(f'Result for day 20 Part 2: {result}')


def main():
    data = get_input()
    maze, start, end = parse_maze(data)
    solve(maze, start, end)


if __name__ == '__main__':
    main()

