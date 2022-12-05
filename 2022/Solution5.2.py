data = open("Input5.txt", "r")

stacks = [[] for i in range(9)]

for index, line in enumerate(data):
    splitted = line[:-1]
    if index < 8:
        for createIndex in range(9):
            create = splitted[1 + 4 * createIndex]
            if create != ' ':
                stacks[createIndex].append(create)
    elif index == 8:
        for stack in stacks:
            stack.reverse()
    elif index > 9:
        splitted = line.rstrip().split(' ')
        stacks[int(splitted[5]) - 1] += stacks[int(splitted[3]) - 1][-int(splitted[1]):]
        stacks[int(splitted[3]) - 1] = stacks[int(splitted[3]) - 1][:-int(splitted[1])]

tops = ''
for stack in stacks:
    tops += stack[-1]

print(tops)
