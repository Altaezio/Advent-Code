data = open("Input4.txt", "r")

total = 0

for line in data:
    splitted = line.split(',')
    a = splitted[0].split('-')
    b = splitted[1].split('-')
    b[1] = b[1][:-1]
    if (int(a[0]) <= int(b[0]) and int(a[1]) >= int(b[1])) or (int(a[0]) >= int(b[0]) and int(a[1]) <= int(b[1])):
        total += 1

print(total)
