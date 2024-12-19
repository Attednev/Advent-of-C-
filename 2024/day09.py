from helper import get_input


EMPTY = ' '


def checksum(numbers, id_to_num):
    result = 0
    for i in range(len(numbers)):
        if not numbers[i].startswith(EMPTY):
            result += i * id_to_num[numbers[i]]
    return result


def get_disk_layout(number):
    numbers = []
    id_to_num = {}
    id = '0'
    id_num = 0
    for i in range(0, len(number), 2):
        numbers.append(id * int(number[i]))
        id_to_num[id] = id_num
        id = chr(ord(id) + 1)
        id_num += 1
        if i + 1 >= len(number):
            break
        if number[i + 1] != '0':
            numbers.append(EMPTY * int(number[i + 1]))
    return numbers, id_to_num


def get_free_index(l, i):
    for j in range(len(l)):
        if l[j].startswith(EMPTY) and len(l[j]) >= i:
            return j
    return -1


def part1(number):
    numbers, id_to_num = get_disk_layout(number)
    numbers = ''.join(numbers)

    next_index = 0
    for i in range(len(numbers) - 1, 0, -1):
        if numbers[i] == EMPTY:
            continue
        while next_index < len(numbers) and numbers[next_index] != EMPTY:
            next_index += 1
        if next_index >= i:
            break
        numbers = numbers[:next_index] + numbers[i] + numbers[next_index + 1:i]

    print(f'Result for day 9 Part 1: {checksum(numbers, id_to_num)}')


def part2(number):
    numbers, id_to_num = get_disk_layout(number)

    i = len(numbers)
    while i > 0:
        i -= 1
        if numbers[i] == EMPTY:
            continue
        index = get_free_index(numbers, len(numbers[i]))
        if 0 <= index < i:
            if len(numbers[index]) == len(numbers[i]):
                numbers[index], numbers[i] = numbers[i], numbers[index]
            else:
                numbers = numbers[:index] + [numbers[i]] + [EMPTY * (len(numbers[index]) - len(numbers[i]))] + numbers[index + 1:i] + [EMPTY * len(numbers[i])] + numbers[i + 1:]
                i += 1
            if i + 1 < len(numbers) and numbers[i + 1].startswith(EMPTY):
                numbers[i] += numbers[i + 1]
                numbers = numbers[:i + 1] + numbers[i + 2:]
            if i > 0 and numbers[i - 1].startswith(EMPTY):
                numbers[i] += numbers[i - 1]
                numbers = numbers[:i - 1] + numbers[i:]

    print(f'Result for day 9 Part 2: {checksum(''.join(numbers), id_to_num)}')


def main():
    data = get_input()
    number = data[0]
    part1(number)
    part2(number)


if __name__ == '__main__':
    main()
