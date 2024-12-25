from helper import get_input_unfiltered


def parse_data(data):
    keys = []
    locks = []
    current = []
    for line in data:
        if len(line) > 0:
            current.append(line)
            continue
        if current[0][0] == '.':
            keys.append(current)
        else:
            locks.append(current)
        current = []
    return keys, locks


def get_height_map(keys, locks):
    k = []
    l = []
    for key in keys:
        current = []
        for i in range(len(key[0])):
            pins = 0
            for j in range(len(key) - 1):
                if key[j][i] == '#':
                    pins += 1
            current.append(pins)
        k.append(current)
    for lock in locks:
        current = []
        for i in range(len(lock[0])):
            pins = 0
            for j in range(1, len(lock)):
                if lock[j][i] == '#':
                    pins += 1
            current.append(pins)
        l.append(current)
    return k, l, max(len(keys[0]), len(locks[0])) - 1


def solve(keys, locks, max_height):
    result = 0
    for key in keys:
        for lock in locks:
            m = max([sum(x) for x in zip(key, lock)])
            if m < max_height:
                result += 1
    print(f'Result for day 25: {result}')


def main():
    data = get_input_unfiltered()
    keys, locks = parse_data(data)
    keys, locks, max_height = get_height_map(keys, locks)
    solve(keys, locks, max_height)


if __name__ == '__main__':
    main()
