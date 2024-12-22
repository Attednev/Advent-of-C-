from helper import get_input


def next_secret(secret):
    new_secret = secret ^ (secret * 64)
    new_secret = new_secret & ((1 << 24) - 1)
    
    new_secret = new_secret ^ (new_secret // 32)
    new_secret = new_secret & ((1 << 24) - 1)

    new_secret = new_secret ^ (new_secret * 2048)
    new_secret = new_secret & ((1 << 24) - 1)
    return new_secret


def solve(data):
    result = 0
    total = {}
    for secret in data:
        visited = set()
        cdiff = []
        price = []
        for _ in range(2000):
            new_secret = next_secret(secret)
            cdiff.append((new_secret % 10) - (secret % 10))
            price.append(new_secret % 10)
            secret = new_secret
        result += secret
        for i in range(len(cdiff) - 4):
            key = tuple(cdiff[i:i+4])
            if key in visited:
                continue
            visited.add(key)
            total.setdefault(key, 0)
            total[key] += price[i + 3]
    key_max = None
    for k, v in total.items():
        if key_max is None or v > total[key_max]:
            key_max = k
    print(f'Result for day 22 Part 1: {result}')
    print(f'Result for day 22 Part 2: {total[key_max]}')


def main():
    data = get_input()
    data = [int(d) for d in data]
    solve(data)


if __name__ == '__main__':
    main()
