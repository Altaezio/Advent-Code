data = open("test.txt", "r")

def toList(packet):
    #print("traitement de :",packet)
    totalList = []
    depthStack = [0]
    currentList = totalList
    numberStr = ''
    for carac in packet[1:]:
        #print("carac :",carac)
        match carac:
            case '[':
                currentList.append([])
                depthStack.append(0)
                currentList = currentList[-1]
            case ']':
                if numberStr != '':
                    currentList.append(int(numberStr))
                numberStr = ''
                currentList = totalList
                depthStack.pop()
                for index in depthStack[:-1]:
                    currentList = currentList[index]
                if len(depthStack) > 0:
                    depthStack[-1] += 1
            case ',':
                if numberStr != '':
                    currentList.append(int(numberStr))
                    numberStr = ''
                depthStack[-1] += 1
            case _:
                numberStr += carac
    return totalList
                
def areInOrder(list1, list2):
    if len(list1) > len(list2):
        return False
    print("are they in order ? :",list1, "and",list2)
    

packets = []
indexSum = 0

for lineIndex, line in enumerate(data):
    line = line.rstrip()
    if len(line) == 0:
        packets = []
        continue
    packets.append(list(line))
    if len(packets) == 2:
        #print(packets)
        list1 = toList(packets[0])
        list2 = toList(packets[1])

        if areInOrder(list1, list2):
            indexSum += 2 * lineIndex - 1

print(indexSum)    
