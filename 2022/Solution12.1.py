data = open("Input12.txt", "r")

class Node:
    def __init__(self, x, y, height, cost, heuristic):
        self.x = x
        self.y = y
        self.height = height
        self.cost = cost
        self.heuristic = heuristic

    def __str__(self):
        return f"({self.x},{self.y}) cost : {self.cost} heuristic : {self.heuristic} height : {self.height}"

def Voisins(node):
    voisins = []
    if node.x - 1 >= 0 and ord(heightMap[node.x - 1][node.y].height) <= ord(node.height) + 1:
        voisins.append(heightMap[node.x - 1][node.y])
    if node.x + 1 < len(heightMap) and ord(heightMap[node.x + 1][node.y].height) <= ord(node.height) + 1:
        voisins.append(heightMap[node.x + 1][node.y])
    if node.y - 1 >= 0 and ord(heightMap[node.x][node.y - 1].height) <= ord(node.height) + 1:
        voisins.append(heightMap[node.x][node.y - 1])
    if node.y + 1 < len(heightMap[node.x]) and ord(heightMap[node.x][node.y + 1].height) <= ord(node.height) + 1:
        voisins.append(heightMap[node.x][node.y + 1])
    return voisins

def Astar(): # A* implementation using Wikipedia
    closedList = []
    openLists = []
    openLists.append(beginning)
    while len(openLists) > 0:
        u = openLists[0]
        openLists = openLists[1:]
        if u.x == end.x and u.y == end.y:
            closedList.append(u)
            print("end")
            return closedList
        for voisin in Voisins(u):
            voisinInClosedList = any([(voisin.x == node.x and voisin.y == node.y) for node in closedList])
            voisinInOpenLists = any([(voisin.heuristic >= node.heuristic and voisin.x == node.x and voisin.y == node.y) for node in openLists])
            if not voisinInClosedList and not voisinInOpenLists:
                openLists.append(Node(voisin.x, voisin.y, voisin.height, u.cost + 1, voisin.cost + abs(end.x - voisin.x) + abs(end.y - voisin.y)))
                openLists.sort(key=lambda node:node.heuristic)
        closedList.append(u)
    print("No path found")
                
def BestVoisinInClosedList(node):
    voisins = []
    if node.x - 1 >= 0 and ord(heightMap[node.x - 1][node.y].height) >= ord(node.height) - 1:
        voisins.append(heightMap[node.x - 1][node.y])
    if node.x + 1 < len(heightMap) and ord(heightMap[node.x + 1][node.y].height) >= ord(node.height) - 1:
        voisins.append(heightMap[node.x + 1][node.y])
    if node.y - 1 >= 0 and ord(heightMap[node.x][node.y - 1].height) >= ord(node.height) - 1:
        voisins.append(heightMap[node.x][node.y - 1])
    if node.y + 1 < len(heightMap[node.x]) and ord(heightMap[node.x][node.y + 1].height) >= ord(node.height) - 1:
        voisins.append(heightMap[node.x][node.y + 1])
    for voisin in voisins:
        for cnode in closedList:
            if voisin.x == cnode.x and voisin.y == cnode.y and cnode.cost == node.cost - 1:
                return cnode

heightMap = []

end = Node(0,0,'z',0,0)
beginning = Node(0,0,'a',0,0)

for rowIndex, line in enumerate(data):
    line = line.rstrip()
    heightMap += [[]]
    for colIndex, height in enumerate(list(line.rstrip())):
        addNode = Node(rowIndex, colIndex, height, -1, 0)
        if height == 'S':
            beginning.x = rowIndex
            beginning.y = line.index('S')
            addNode = beginning
        elif height == 'E':
            end.x = rowIndex
            end.y = line.index('E')
            addNode = end
        heightMap[rowIndex].append(addNode)

beginning.heuristic = abs(end.x - beginning.x) + abs(end.y - beginning.y)

print(beginning, end)

closedList = sorted(Astar(), key=lambda lnode: lnode.cost)

end.cost = closedList[-2].cost + 1 # To have the cost to get to the end

screen = [['.' for _ in row] for row in heightMap]

steps = 0
node = end
while node.x != beginning.x or node.y != beginning.y:
    steps += 1
    screen[node.x][node.y] = node.height
    node = BestVoisinInClosedList(node)

screen[node.x][node.y] = 'S'

for row in screen:
    for pixel in row:
        print(pixel, end='')
    print()

print(steps)
