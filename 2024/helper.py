
def get_input():
    file = open('input.txt', 'r')
    lines = file.read().split('\n')
    file.close()
    return lines
