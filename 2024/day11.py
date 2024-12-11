from helper import get_input


def add_to_even_or_other(even, other, element, count):
    if len(element) % 2 == 0:
        even[element] = even.setdefault(element, 0) + count
    else:
        other[element] = other.setdefault(element, 0) + count
    return even, other


def blink(stones):
    new_zeros = 0
    new_even = {}
    new_other = {} if stones['ZERO'] == 0 else {'1': stones['ZERO']}
    for n, v in stones['OTHER'].items():
        n = str(int(n) * 2024)
        new_even, new_other = add_to_even_or_other(new_even, new_other, n, v)
    for n, v in stones['EVEN'].items():
        left = str(int(n[:(len(n) // 2)]))
        right = str(int(n[(len(n) // 2):]))
        if right == '0':
            new_zeros += v
        else:
            new_even, new_other = add_to_even_or_other(new_even, new_other, right, v)
        new_even, new_other = add_to_even_or_other(new_even, new_other, left, v)

    stones['ZERO'] = new_zeros
    stones['EVEN'] = new_even
    stones['OTHER'] = new_other

    return stones


def blink_n_times(stones_dict, n):
    for i in range(n):
        stones_dict = blink(stones_dict)
    return stones_dict


def stones_to_dict(stones):
    stones_dict = {'ZERO': 0, 'EVEN': {}, 'OTHER': {}}
    for s in stones:
        if s == '0':
            stones_dict['ZERO'] += 1
        else:
            stones_dict['EVEN'], stones_dict['OTHER'] = add_to_even_or_other(stones_dict['EVEN'], stones_dict['OTHER'], s, 1)
    return stones_dict


def part1(stones):
    stones_dict = blink_n_times(stones_to_dict(stones), 25)
    result = stones_dict['ZERO'] + sum(stones_dict['EVEN'].values()) + sum(stones_dict['OTHER'].values())
    print(f'Result for day 1 Part 1: {result}')


def part2(stones):
    stones_dict = blink_n_times(stones_to_dict(stones), 75)
    result = stones_dict['ZERO'] + sum(stones_dict['EVEN'].values()) + sum(stones_dict['OTHER'].values())
    print(f'Result for day 1 Part 2: {result}')


def main():
    stones = get_input()[0].split(' ')
    part1(stones)
    part2(stones)


if __name__ == '__main__':
    main()
