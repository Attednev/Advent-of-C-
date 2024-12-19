from math import floor, ceil

from helper import get_input

WALL = float('-inf')
EMPTY = float('inf')

RIGHT = 0
UP = 1
LEFT = 2
DOWN = 3


def parse_maze(data):
    maze = []
    start = None
    end = None
    for i in range(len(data)):
        current = []
        for j in range(len(data[i])):
            current.append(WALL if data[i][j] == '#' else EMPTY)
            if data[i][j] == 'S':
                start = (j, i)
            if data[i][j] == 'E':
                end = (j, i)
        maze.append(current)
    return maze, start, end


def solve(maze, start, end, starting_direction):
    next_pos = [(start[0], start[1], starting_direction)]
    maze[start[1]][start[0]] = 0
    while len(next_pos) > 0:
        c_x, c_y, direction = next_pos.pop(0)
        neighbours = [(c_x + 1, c_y, RIGHT), (c_x, c_y + 1, DOWN), (c_x - 1, c_y, LEFT), (c_x, c_y - 1, UP)]
        for n_x, n_y, n_d in neighbours:
            if n_y < 0 or n_x < 0 or n_y >= len(maze) or n_x >= len(maze[n_y]):
                continue
            if ((direction == UP and n_d == DOWN) or (direction == DOWN and n_d == UP) or
                    (direction == LEFT and n_d == RIGHT) or (direction == RIGHT and n_d == LEFT)):
                continue
            score = maze[c_y][c_x] + (1 if direction == n_d else 1001)
            if score < maze[n_y][n_x]:
                maze[n_y][n_x] = score
                next_pos = [t for t in next_pos if not (t[0] == n_x and t[1] == n_y)]
                next_pos.append((n_x, n_y, n_d))

    return maze[end[1]][end[0]]


def part1(maze, start, end):
    result = solve(maze, start, end, RIGHT)
    print(f'Result for day 16 Part 1: {result}')


def part2(maze, start, end, maze_part1):
    solve(maze, end, start, DOWN)
    min_path = set()
    for i in range(len(maze)):
        for j in range(len(maze[i])):
            if maze[i][j] == WALL or (maze[i][j] == EMPTY and maze_part1[i][j] == EMPTY):
                continue
            maze[i][j] += maze_part1[i][j]
            if maze[i][j] == maze_part1[end[1]][end[0]] or maze[i][j] + 1000 == maze_part1[end[1]][end[0]]:
                min_path.add((j, i))

    print(f'Result for day 16 Part 2: {len(min_path)}')


def main():
    data = get_input()
    maze_part1, start, end = parse_maze(data)
    part1(maze_part1, start, end)
    maze_part2, start, end = parse_maze(data)
    part2(maze_part2, start, end, maze_part1)


if __name__ == '__main__':
    main()
