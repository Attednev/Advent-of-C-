from helper import get_input
import sys


def get_perimeter(region, index=None):
    if index is None:
        index = 0
    if index == len(region):
        return 0, []

    b, corners = get_perimeter(region, index + 1)

    x, y = region[index]
    borders = [(x + 1, y) not in region,    # RIGHT
               (x, y + 1) not in region,    # DOWN
               (x - 1, y) not in region,    # LEFT
               (x, y - 1) not in region]    # UP

    # Bottom right corner on field
    if borders[0] and borders[1]:
        corners.append((x, y))
    # Bottom left corner between fields
    elif borders[0] and (x + 1, y + 1) in region:
        corners.append((x, y))

    # Top right corner on field
    if borders[0] and borders[3]:
        corners.append((x, y))
    # Top right corner between fields
    elif borders[3] and (x + 1, y - 1) in region:
        corners.append((x, y))

    # Bottom left corner on field
    if borders[2] and borders[1]:
        corners.append((x, y))
    # Top left corner between fields
    elif borders[1] and (x - 1, y + 1) in region:
        corners.append((x, y))

    # Top left corner on field
    if borders[2] and borders[3]:
        corners.append((x, y))
    # Bottom right corner between fields
    elif borders[2] and (x - 1, y - 1) in region:
        corners.append((x, y))

    return sum(borders) + b, corners


def find_region(garden, x, y, visited, region=None, crop_type=None):
    if region is None:
        region = []
    if crop_type is None:
        crop_type = garden[y][x]

    if x < 0 or y < 0 or x >= len(garden[0]) or y >= len(garden):
        return region, visited

    if visited[y][x]:
        return region, visited

    if garden[y][x] != crop_type:
        return region, visited

    visited[y][x] = True
    region.append((x, y))
    region, visited = find_region(garden, x + 1, y, visited, region, crop_type)
    region, visited = find_region(garden, x, y + 1, visited, region, crop_type)
    region, visited = find_region(garden, x - 1, y, visited, region, crop_type)
    region, visited = find_region(garden, x, y - 1, visited, region, crop_type)

    return region, visited


def solve(garden):
    visited = [[False for _ in range(len(garden[0]))] for _ in range(len(garden))]
    result_part1 = 0
    result_part2 = 0
    for y in range(len(garden)):
        for x in range(len(garden[y])):
            if visited[y][x]:
                continue
            region, visited = find_region(garden, x, y, visited)
            perimeter, corners = get_perimeter(region)

            result_part1 += perimeter * len(region)
            result_part2 += len(corners) * len(region)
            print(f'Region at {x} {y} with content {garden[y][x]} has {len(corners)} sides with corners {corners}')

    print(f'Result for day 1 Part 1: {result_part1}')
    print(f'Result for day 1 Part 2: {result_part2}')


def main():
    garden = get_input()
    solve(garden)


if __name__ == '__main__':
    sys.setrecursionlimit(5000)
    main()
