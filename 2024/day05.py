from helper import get_input


def data_to_ordering_and_updates(data):
    index = 0
    ordering = {}
    while index < len(data) and data[index] != '':
        splits = data[index].split('|')
        if splits[1] not in ordering.keys():
            ordering[splits[1]] = []
        ordering[splits[1]].append(splits[0])
        index += 1
    updates = []
    index += 1
    while index < len(data) and data[index] != '':
        updates.append(data[index].split(','))
        index += 1
    return ordering, updates


def test_order(number, ordering, update, finished):
    if number not in ordering:
        finished.append(number)
        return True
    requirements = list(set(ordering[number]) & set(update) - set(finished))
    if len(requirements) == 0:
        finished.append(number)
        return True
    return False


def part1(ordering, updates):
    result = 0
    for update in updates:
        finished = []
        valid = True
        for number in update:
            if not test_order(number, ordering, update, finished):
                valid = False
                break
        if valid:
            result += int(update[len(update) // 2])

    print(f'Result for day 1 Part 1: {result}')


def part2(ordering, updates):
    result = 0
    for update in updates:
        finished = []
        valid = True
        for index in range(len(update)):
            # Try all subsequent number to find the next one in order
            for next_index in range(index + 1, len(update) + 1):
                if test_order(update[index], ordering, update, finished):
                    break
                valid = False
                # Swap current index with the next in line
                tmp_update = update[:index] + [update[next_index]] + update[(index + 1):next_index] + [update[index]]
                if next_index + 1 < len(update):
                    tmp_update += update[(next_index + 1):]
                update = tmp_update
        # Now we only count center numbers of updates that were invalid
        if not valid:
            result += int(update[len(update) // 2])

    print(f'Result for day 1 Part 2: {result}')


def main():
    data = get_input()
    ordering, updates = data_to_ordering_and_updates(data)
    part1(ordering, updates)
    part2(ordering, updates)


if __name__ == '__main__':
    main()
