data = open("Input4.txt", "r")

total = 0

for line in data:
    splitted = line.rstrip().split(',')
    a = splitted[0].split('-')
    b = splitted[1].split('-')
    if len(set(range(int(a[0]), int(a[1]) + 1)).intersection(set(range(int(b[0]), int(b[1]) + 1)))) > 0:
        total += 1

print(total)
