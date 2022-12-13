data = open("test.txt", "r")

packets = []

for lineIndex, line in enumerate(data):
    line = line.rstrip()
    if len(line) == 0:
        packets = []
        continue
    packets.append(line)
    if len(packets) == 2:
        
    
