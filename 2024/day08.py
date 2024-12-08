import operator

from helper import get_input


def find_antennas(data):
    antennas = {}
    for y in range(len(data)):
        for x in range(len(data[y])):
            if data[y][x] != '.':
                if data[y][x] not in antennas:
                    antennas[data[y][x]] = []
                antennas[data[y][x]].append((x, y))
    return antennas


def part1(antennas, max_x, max_y):
    antinodes = set()
    for _, l in antennas.items():
        for current in range(len(l)):
            for next in range(current + 1, len(l)):
                c_x, c_y = l[current]
                n_x, n_y = l[next]

                dx = n_x - c_x
                dy = n_y - c_y

                c_antinode = (c_x - dx, c_y - dy)
                n_antinode = (n_x + dx, n_y + dy)

                if 0 <= c_antinode[0] < max_x and 0 <= c_antinode[1] < max_y:
                    antinodes.add(c_antinode)

                if 0 <= n_antinode[0] < max_x and 0 <= n_antinode[1] < max_y:
                    antinodes.add(n_antinode)

    print(f'Result for day 1 Part 1: {len(antinodes)}')


def part2(antennas, max_x, max_y):
    antinodes = set()
    for _, l in antennas.items():
        for current in range(len(l)):
            for next in range(current + 1, len(l)):
                c_x, c_y = l[current]
                n_x, n_y = l[next]

                dx = n_x - c_x
                dy = n_y - c_y

                for i in range(max(max_x, max_y)):
                    c_antinode = (c_x - i * dx, c_y - i * dy)
                    n_antinode = (n_x + i * dx, n_y + i * dy)

                    if 0 <= c_antinode[0] < max_x and 0 <= c_antinode[1] < max_y:
                        antinodes.add(c_antinode)

                    if 0 <= n_antinode[0] < max_x and 0 <= n_antinode[1] < max_y:
                        antinodes.add(n_antinode)

    print(f'Result for day 1 Part 2: {len(antinodes)}')
    return antinodes


def main():
    data = get_input()
    antennas = find_antennas(data)
    part1(antennas, len(data[0]), len(data))
    part2(antennas, len(data[0]), len(data))


if __name__ == '__main__':
    main()
