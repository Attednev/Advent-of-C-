from helper import get_input
from itertools import combinations


def solve(connections):
    clusters = {}
    for connection in connections:
        computers = connection.split('-')
        clusters.setdefault(computers[0], set([computers[0]]))
        clusters.setdefault(computers[1], set([computers[1]]))
        clusters[computers[0]].add(computers[1])
        clusters[computers[1]].add(computers[0])
    
    parties = set()
    superclusters = []
    for k, v in clusters.items():
        for neighbour in v:
            union = v & clusters[neighbour]
            if len(union) < 2:
                continue
            for c in combinations(tuple(sorted(union)), 3):
                if clusters[c[0]] & clusters[c[1]] & clusters[c[2]] == union:
                    parties.add(c)
            s = set()
            for u in union:
                if clusters[u] & union == union:
                    s.add(u)
            superclusters.append(s)

    chief = [p for p in parties if p[0][0] == 't' or p[1][0] == 't' or p[2][0] == 't']
    print(f'Result for day 23 Part 1: {len(chief)}')
   
    largest_lan = max(superclusters, key=len)
    print(f'Result for day 23 Part 2: {','.join(sorted(largest_lan))}')


def main():
    connections = get_input()
    solve(connections)


if __name__ == '__main__':
    main()
