
def transfer_to_next_stage_part2(working_set, translation, start_index=0):
    length = len(working_set)
    for idx in range(start_index, length, 2):
        for s, (o, e) in translation.items():
            if working_set[idx] + working_set[idx + 1] <= s or working_set[idx] >= e:
                continue
            if working_set[idx] < s:
                working_set.append(working_set[idx])
                working_set.append(s - working_set[idx])
                working_set[idx + 1] -= s - working_set[idx]
                working_set[idx] = s + o
            if e < working_set[idx] + working_set[idx + 1]:
                working_set.append(e)
                working_set.append(working_set[idx] + working_set[idx + 1] - e)
                working_set[idx + 1] -= working_set[idx] + working_set[idx + 1] - e
                working_set[idx] += o
            break
    if len(working_set) != length:
        transfer_to_next_stage_part2(working_set, translation, length)
    return working_set


def transfer_to_next_stage_part1(working_set, translation):
    for idx in range(0, len(working_set)):
        for s, (o, e) in translation.items():
            if s <= working_set[idx] <= e:
                working_set[idx] += o
                break
    return working_set


def parse_input(lines):
    mode = 0
    seeds = [int(x) for x in lines[0].split(':')[1].split()]
    maps = [{}, {}, {}, {}, {}, {}, {}]
    for line in lines[1::]:
        if len(line) <= 1:
            continue
        if "map" in line:
            mode += 1
            continue
        splits = line.split()
        destination_range_start = int(splits[0])
        source_range_start = int(splits[1])
        range_length = int(splits[2])
        maps[mode - 1][source_range_start] = [destination_range_start - source_range_start, source_range_start + range_length]
    return seeds, maps


def solve(lines):
    seeds, maps = parse_input(lines.split('\n'))
    working_set = seeds.copy()
    for i in range(0, 7):
        working_set = transfer_to_next_stage_part1(working_set, maps[i])
    print(f"1) The closest location is {min(working_set)}")
    working_set = seeds.copy()
    for i in range(0, 7):
        working_set = transfer_to_next_stage_part2(working_set, maps[i])
    print(f"2) The closest location is {min(working_set[::2])}")


if __name__ == '__main__':
    with open("day05_input", "r") as file:
        solve(file.read())
