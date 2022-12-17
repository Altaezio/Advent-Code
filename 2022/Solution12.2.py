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

def Astar(beginning): # A* implementation using Wikipedia
    closedList = []
    openLists = []
    openLists.append(beginning)
    while len(openLists) > 0:
        u = openLists.pop(0)
        if u.x == end.x and u.y == end.y:
            closedList.append(u)
            #print("end with", u)
            return closedList
        for voisin in Voisins(u):
            voisinInClosedList = any([(voisin.x == node.x and voisin.y == node.y) for node in closedList])
            voisinInOpenLists = any([(voisin.heuristic >= node.heuristic and voisin.x == node.x and voisin.y == node.y) for node in openLists])
            if not voisinInClosedList and not voisinInOpenLists:
                openLists.append(Node(voisin.x, voisin.y, voisin.height, u.cost + 1, 0))
                openLists.sort(key=lambda node:node.heuristic)
        closedList.append(u)
        #if len(closedList) % 100 == 0:
            #PrintScreen()
    #print("No path found")
    return []
                
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

def PrintScreen():
        screen = [['.' for _ in row] for row in heightMap]

        for node in closedList:
            screen[node.x][node.y] = node.height

        show = ''

        for row in screen:
            for pixel in row:
                show += pixel
            show+='\n'
        print(show)
    

heightMap = []

end = Node(0,0,'z',0,0)
#beginning = Node(0,0,'a',0,0)
beginnings = []

for rowIndex, line in enumerate(data):
    line = line.rstrip()
    heightMap += [[]]
    for colIndex, height in enumerate(list(line.rstrip())):
        addNode = Node(rowIndex, colIndex, height, -1, 0)
        if height == 'S' or height == 'a':
            beginnings.append(Node(rowIndex, colIndex, 'a', 0, 0))
            addNode = beginnings[-1]
        elif height == 'E':
            end.x = rowIndex
            end.y = line.index('E')
            addNode = end
        heightMap[rowIndex].append(addNode)

allSteps = []

print(len(beginnings), "a")

for index, beginning in enumerate(beginnings):
    closedList = Astar(beginning)

    if len(closedList) == 0:
        continue
    
    end = closedList[-1]

    steps = end.cost
    allSteps.append(steps)
    print(index * 100 / len(beginnings), ", steps", steps)

print(sorted(allSteps)[0])
