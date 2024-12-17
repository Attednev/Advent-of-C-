import re

from helper import get_input


ip = 0
registers = {'A': 0, 'B': 0, 'C': 0}


def parse_data(data):
    global registers
    registers['A'] = int(re.search(r"Register A: (\d+)", data[0]).group(1))
    registers['B'] = int(re.search(r"Register B: (\d+)", data[1]).group(1))
    registers['C'] = int(re.search(r"Register C: (\d+)", data[2]).group(1))
    return [int(op) for op in re.findall(r"\d+", data[3])]


def get_combo(operand):
    global registers
    if 0 <= operand <= 3:
        return operand
    if operand == 4:
        return registers['A']
    if operand == 5:
        return registers['B']
    if operand == 6:
        return registers['C']
    if operand == 7:
        print(f'Invalid Program: Reserved operand used!')
        exit(1)
    print(f'Invalid Program: Combo operand does nothing!')
    exit(1)


def run(program, max_cycles=999999):
    global registers, ip

    output = ''
    while ip + 1 < len(program) and max_cycles > 0:
        max_cycles -= 1

        opcode = program[ip]
        operand = program[ip + 1]

        if opcode == 0:
            registers['A'] //= 2 ** get_combo(operand)
        if opcode == 1:
            registers['B'] ^= operand
        if opcode == 2:
            registers['B'] = get_combo(operand) % 8
        if opcode == 3:
            if registers['A'] != 0:
                ip = operand
            continue
        if opcode == 4:
            registers['B'] ^= registers['C']
        if opcode == 5:
            output += f'{get_combo(operand) % 8},'
        if opcode == 6:
            registers['B'] = registers['A'] // (2 ** get_combo(operand))
        if opcode == 7:
            registers['C'] = registers['A'] // (2 ** get_combo(operand))

        ip += 2

    return output[:-1]


def part1(program):
    print(f'Result for day 1 Part 1: {run(program, 100)}')


def part2(program):
    global registers
    program_string = ','.join(str(op) for op in program)
    initial_b = registers['B']
    initial_c = registers['C']

    def find_rec(term, A):
        global registers

        if term < 0:
            registers = {'A': A, 'B': initial_b, 'C': initial_c}
            return A if run(program, 750) == program_string else None

        while True:
            registers = {'A': A, 'B': initial_b, 'C': initial_c}
            output = run(program, 750)
            if term + 1 < len(program) and not len(output) == 0 and int(output[2 * term + 2]) != program[term + 1]:
                return None
            if len(output) == len(program_string) and int(output[2 * term]) == program[term]:
                found = find_rec(term - 1, A)
                if found is not None:
                    return found
            # This varies depending on the program.
            # This is the number required to change the term-th number in the output sequence
            # In this case the program changes A in the following: A = A // 8
            # So in order to get a change in the term-th iteration, A needs to increase by 8 ** term
            A += 8 ** term

    print(f'Result for day 1 Part 2: {find_rec(15, 0)}')


def main():
    data = get_input()
    part1(parse_data(data))
    part2(parse_data(data))


if __name__ == '__main__':
    main()
