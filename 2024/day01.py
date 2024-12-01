from helper import get_input


def input_to_lists(lines):
    left = []
    right = []
    for line in lines:
        splits = line.split('   ')
        if len(splits) <= 1:
            break

        left.append(int(splits[0]))
        right.append(int(splits[1]))

    left.sort()
    right.sort()

    return left, right


def part1(left, right):
    result = 0
    for i in range(len(left)):
        result += abs(left[i] - right[i])

    print(f'Result for day 1 Part 1: {result}')


def part2(left, right):
    result = 0
    right_index = 0
    for left_index in range(len(left)):
        count = 0
        while right_index < len(right) and right[right_index] < left[left_index]:
            right_index += 1
        while right_index < len(right) and right[right_index] == left[left_index]:
            right_index += 1
            count += 1
        result += left[left_index] * count
    print(f'Result for day 1 Part 2: {result}')


def main():
    lines = get_input()
    left, right = input_to_lists(lines)
    part1(left, right)
    part2(left, right)


if __name__ == '__main__':
    main()
