data = open("Input3.txt", "r")

prioritySum = 0

for line in data:
    comp1 = line[:int((len(line) - 1)/2)]
    comp2 = line[int((len(line) - 1)/2):]
    typeIndex1 = 0
    typeIndex2 = 0
    while comp1[typeIndex1] != comp2[typeIndex2]:
        if typeIndex2 + 1 == len(comp2):
            typeIndex1 += 1
            typeIndex2 = 0
        else:
            typeIndex2 += 1
    item = comp1[typeIndex1]
    priority = ord(item) - 96 if item >= 'a' else ord(item) - 65 + 27
    prioritySum += priority

print(prioritySum)
