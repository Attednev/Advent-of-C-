import re
from math import sqrt

from helper import get_input


WIDTH = 101
HEIGHT = 103


def quadrant_count(positions):
    quadrants = [[[], []], [[], []]]
    for x, y, _, _ in positions:
        if 2 * x + 1 == WIDTH or 2 * y + 1 == HEIGHT:
            continue
        i = 2 * x // WIDTH
        j = 2 * y // HEIGHT
        quadrants[j][i].append((x, y))
    return len(quadrants[0][0]), len(quadrants[0][1]), len(quadrants[1][0]), len(quadrants[1][1])


def get_robot_positions(data):
    positions = []
    for line in data:
        regex = re.search(r"p=(-?\d+),(-?\d+) v=(-?\d+),(-?\d+)", line)
        p_x, p_y, v_x, v_y = [int(e) for e in regex.groups()]
        positions.append((p_x, p_y, v_x, v_y))
    return positions


def let_time_pass(positions, time):
    for i in range(time):
        new_positions = []
        for p_x, p_y, v_x, v_y in positions:
            new_x = (p_x + v_x + WIDTH) % WIDTH
            new_y = (p_y + v_y + HEIGHT) % HEIGHT
            new_positions.append((new_x, new_y, v_x, v_y))
        positions = new_positions
    return positions


def part1(positions):
    positions = let_time_pass(positions, 100)
    q1, q2, q3, q4 = quadrant_count(positions)
    result = q1 * q2 * q3 * q4
    print(f'Result for day 14 Part 1: {result}')


def part2(positions):
    for i in range(10000):
        positions = let_time_pass(positions, 1)

        # We calculate the distances of all points to their 'expected positions'
        # which is the average over all values.
        # We then calculate the variance for all distances where the average
        # distance is the 'expected value'. That way, we get a measure of how
        # spread out the points are. The higher the variance, the higher the
        # spread. Conversely, the lower the variance, the more concentrated the
        # points are.
        center_x, center_y = 0, 0
        for p_x, p_y, _, _ in positions:
            center_x += p_x
            center_y += p_y

        center_x = center_x / len(positions) - WIDTH // 2
        center_y = center_y / len(positions) - HEIGHT // 2

        distances = []
        for p_x, p_y, _, _ in positions:
            distances.append(sqrt((p_x - center_x) ** 2 + (p_y - center_y) ** 2))
        average_distance = sum(distances) / len(distances)

        variance = 0
        for d_i in distances:
            variance += (d_i - average_distance) ** 2
        variance /= len(distances)

        if variance < 400:
            print(f'Result for day 14 Part 2: {i + 1}')
            break


def main():
    data = get_input()
    positions = get_robot_positions(data)
    part1(positions)
    part2(positions)


if __name__ == '__main__':
    main()
