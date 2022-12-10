data = open("Input10.txt", "r")

def printScreen():
    for row in screen:
        for pixel in row:
            print(pixel, end='')
        print()

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

values.pop()

screen = [[0 for _ in range(40)] for _ in range(6)]

for drawPosition, spritePosition in enumerate(values):
    screen[drawPosition // 40][drawPosition % 40] = '#' if spritePosition - 1 <= drawPosition % 40 <= spritePosition + 1 else '.'

printScreen()
