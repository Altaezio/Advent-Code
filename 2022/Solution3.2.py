data = open("Input3.txt", "r")

prioritySum = 0
lines = [[], [], []]

def Bigger(a, b, c) -> int:
    if a <= b and a <= c:
        return 0
    elif b <= a and b <= c:
        return 1
    elif c <= a and c <= b:
        return 2

for lineIndex, line in enumerate(data):
    lines[lineIndex % 3] = sorted(line)[1:]
    if lineIndex % 3 == 2:
        indexes = [0, 0, 0]
        while len(set([lines[0][indexes[0]], lines[1][indexes[1]], lines[2][indexes[2]]])) != 1:
            indexes[Bigger(lines[0][indexes[0]], lines[1][indexes[1]], lines[2][indexes[2]])] += 1

        item = lines[0][indexes[0]]
        print(item, lines)
        priority = ord(item) - 96 if item >= 'a' else ord(item) - 65 + 27
        prioritySum += priority


print(prioritySum)
