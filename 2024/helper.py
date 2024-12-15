
def get_input():
    file = open('input.txt', 'r')
    lines = file.read().split('\n')
    file.close()
    return list(filter(None, lines))


def get_input_unfiltered():
    file = open('input.txt', 'r')
    lines = file.read().split('\n')
    file.close()
    return lines


def get_input_as_str():
    file = open('input.txt', 'r')
    lines = file.read()
    file.close()
    return lines
