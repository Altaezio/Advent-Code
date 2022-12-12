import heapq

data = open("test.txt", "r")

class Node:
    def __init__(self, x, y, height, cost, heuristic):
        self.x = x
        self.y = y
        self.height = height
        self.cost = cost
        self.heuristic = heuristic

    def __str__(self):
        return f"({self.x},{self.y}) cost : {self.cost} heuristic : {self.heuristic}"

def Compare(node):
    if node.heuristic < node.heuristic:
        return 1
    if node.heuristic == node.heuristic:
        return 0
    else:
        return -1

def Voisins(node):
    voisins = []
    if node.x - 1 >= 0 && heightMap[node.x - 1][node.y].height <= node.height + 1:
        voisins.append(heightMap[node.x - 1][node.y])
    if node.x + 1 < len(heightMap) && heightMap[node.x + 1][node.y].height <= node.height + 1:
        voisins.append(heightMap[node.x + 1][node.y])
    if node.y - 1 >= 0 && heightMap[node.x][node.y - 1].height <= node.height + 1:
        voisins.append(heightMap[node.x][node.y - 1])
    if node.y + 1 < len(heightMap[node.x]) && heightMap[node.x][node.y + 1].height <= node.height + 1:
        voisins.append(heightMap[node.x][node.y + 1])

def Astar(): # A* implementation using Wikipedia
    closedList = []
    openLists = []
    openList.append(debut)
    while len(openList) > 0:
        u = openList[0]
        openList = openList[1:]
        if u[0] == fin[0] and u[1] == fin[1]:
            # reconstituer le chemin ?
            print('end')
            return
        for voisin in Voisins(u):
            if voisin not in closedList or any(voisin.heuristic < node.heuristic) for node in openLists:
                voisin.cost = u.cost + 1
                voisin.heuristic = voisin.cost + (fin.x - voisin.x) ** 2 + (fin.y - voisin.y) ** 2
                # Ajouter à la file openLists attention à l'ajout, trier avec Compare
        closedLists.append(u)
    print("Pas de chemin trouvé")
                

heightMap = []

fin = Node(0,0,'z',-1,0)
debut = Node(0,0,'a',0,0)

for rowIndex, line in enumerate(data):
    heightMap += []
    for colIndex, height in enumerate(list(line.rstrip())):
        heightMap[rowIndex].append(Node(rowIndex, colIndex, height, -1))
    if 'S' in heightMap[rowIndex]:
        debut.x = rowIndex
        debut.y = heightMap[rowIndex].index('S')
    elif 'E' in heightMap[rowIndex]:
        fin.x = rowIndex
        fin.y = heightMap[rowIndex].index('E')

debut.heuristic = (fin.x - debut.x) ** 2 + (fin.y - debut.y) ** 2

print(debut, fin)

