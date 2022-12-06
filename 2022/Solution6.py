data = open("Input6.txt", "r")

line = data.readline()
lenMarker = 14
markerIndex = lenMarker

while len(marker) != lenMarker:
    marker = set((line[markerIndex - lenMarker: markerIndex]))
    markerIndex += 1

print(markerIndex - 1)
