data = open("Input8.txt", "r")

forest = []

for line in data:
    forest.append(list(line.rstrip()))

bestScore = 0

for i, row in enumerate(forest):
    if i == 0 or i == len(forest) - 1:
        continue
    for j, height in enumerate(row):
        if j == 0 or j == len(row) - 1:
            continue
        height = int(height)
        viewNorth = 0
        if i > 0:
            viewedTreeHeight = 0
            northIndex = 1
            while viewedTreeHeight < height and i-northIndex >= 0:
                viewedTreeHeight = int(forest[i-northIndex][j])
                northIndex += 1
                viewNorth += 1
        if viewNorth == 0:
            viewNorth = 1

        viewSouth = 0
        if i < len(forest) - 1:
            viewedTreeHeight = 0
            southIndex = 1
            while viewedTreeHeight < height and i+southIndex < len(forest):
                viewedTreeHeight = int(forest[i+southIndex][j])
                southIndex += 1
                viewSouth += 1
        if viewSouth == 0:
            viewSouth = 1

        viewWest = 0
        if j > 0:
            viewedTreeHeight = 0
            westIndex = 1
            while viewedTreeHeight < height and j-westIndex >= 0:
                viewedTreeHeight = int(row[j-westIndex])
                westIndex += 1
                viewWest += 1
        if viewWest == 0:
            viewWest = 1
            

        viewEast = 0
        if j < len(row) - 1:
            viewedTreeHeight = 0
            eastIndex = 1
            while viewedTreeHeight < height and j+eastIndex < len(row):
                viewedTreeHeight = int(row[j+eastIndex])
                eastIndex += 1
                viewEast += 1
        if viewEast == 0:
            viewEast = 1

        treeScore = viewNorth * viewSouth * viewEast * viewWest
        if treeScore > bestScore:
            bestScore = treeScore
            
print(bestScore)
            
