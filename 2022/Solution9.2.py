data = open("Input9.txt", "r")

def sTP(x,y):
    tailPositions.add((x, y))

def printState():
    table = [['.' for _ in range(27)] for _ in range(27)]
    offset = 5
    for position in tailPositions:
        table[offset + position[1]][offset + position[0]] = '#'
    table[offset][offset] = 's'
    for index, node in enumerate(nodes):
        table[offset + node[1]][offset + node[0]] = str(index)
    for row in table:
        print(row)

nodes = [[0,0] for _ in range(10)]

tailPositions = set(())
sTP(nodes[-1][0], nodes[-1][1])

ropeLength = 1

for line in data:
    splitted = line.rstrip().split()
    direction = splitted[0]
    numberMove = int(splitted[1])
    for _ in range(numberMove):
        match direction:
            case 'U':
                nodes[0][1] += 1
            case 'D':
                nodes[0][1] -= 1
            case 'R':
                nodes[0][0] += 1
            case 'L':
                nodes[0][0] -= 1

        for nodeIndex, node in enumerate(nodes[1:]):
            head = nodes[nodeIndex]

            if abs(head[0] - node[0]) > ropeLength or abs(head[1] - node[1]) > ropeLength:
                if head[0] - node[0] != 0:
                    node[0] += int((head[0] - node[0]) / abs(head[0] - node[0]))
                if head[1] - node[1] != 0:
                    node[1] += int((head[1] - node[1]) / abs(head[1] - node[1]))
            sTP(nodes[-1][0], nodes[-1][1])
        

#printState()
                
print(len(tailPositions))
    
            
