data = open("test.txt", "r")

def toList(packet):
    totalList = []
    depthStack = [0]
    currentList = totalList
    for carac in packet[1:]:
        match carac:
            case '[':
                currentList.append([])
                depthStack.append(0)
                currentList = currentList[-1]
            case ']':
                depthStack.pop()
                currentList = totalList
                for index in depthStack:
                    currentList = currentList[index]
            case ','

packets = []

for lineIndex, line in enumerate(data):
    line = line.rstrip()
    if len(line) == 0:
        packets = []
        continue
    packets.append(list(line))
    if len(packets) == 2:
        list1 = toList(packets[0])
        list2 = toList(packets[1])
    
