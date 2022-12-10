data = open("Input10.txt", "r")

lines = data.readlines()

x = 1

values = [x]

for line in lines:
    splitted = line.rstrip().split()
    if splitted[0] == 'addx':
        values += [x]
        x += int(splitted[1])
        values += [x]
    else:
        values += [x]

signalStrength = 0

for cycleIndex in range(6):
    signalStrength += values[cycleIndex * 40 + 19] * (cycleIndex * 40 + 20)

print(signalStrength)
