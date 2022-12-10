from math import copysign

data = open("Input9.txt", "r")

def sTP():
    tailPositions.add((tailx, taily))

def printState():
    table = [['.' for _ in range(10)] for _ in range(10)]
    offset = 5
    for position in tailPositions:
        table[offset + position[0]][offset + position[1]] = '#'
    table[offset][offset] = 's'
    table[offset + tailx][offset + taily] = 'T'
    table[offset + headx][offset + headx] = 'H'
    for row in table:
        print(row)

headx = heady = tailx = taily = 0

tailPositions = set(())
sTP()

ropeLength = 1

for line in data:
    splitted = line.rstrip().split()
    direction = splitted[0]
    numberMove = int(splitted[1])
    for _ in range(numberMove):
        match direction:
            case 'U':
                heady += 1
            case 'D':
                heady -= 1
            case 'R':
                headx += 1
            case 'L':
                headx -= 1

        if abs(headx - tailx) > ropeLength or abs(heady - taily) > ropeLength:
            if headx - tailx != 0:
                tailx += int((headx - tailx) / abs(headx - tailx))
            if heady - taily != 0:
                taily += int((heady - taily) / abs(heady - taily))
                
            sTP()

#printState()
print(len(tailPositions))
    
            
