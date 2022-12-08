data = open("Input8.txt", "r")

forest = []

for line in data:
    forest.append(list(line.rstrip()))

print(forest)

totalVisibleTrees = 0

for i, row in enumerate(forest):
    if i == 0 or i == len(forest) - 1:
        totalVisibleTrees += len(forest)
        continue
    for j, height in enumerate(row):
        if j == 0 or j == len(row) - 1:
            totalVisibleTrees += 1
        else:
            isVisible = False
            if height > sorted(row[:j])[-1] or height > sorted(row[j+1:])[-1]:
                isVisible = True
            if height > sorted([_row[j] for _row in forest[:i]])[-1] or height > sorted([_row[j] for _row in forest[i+1:]])[-1]:
                isVisible = True
            if isVisible:
                totalVisibleTrees += 1

print(totalVisibleTrees)                                                
            
