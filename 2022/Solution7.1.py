data = open("Input7.txt", "r")

threshold = 100000

class Dir:
    def __init__(self, name, parent):
        self.name = name
        self.parent = parent
        self.subDirFile = []

    def addsub(self, subdirfile):
        self.subDirFile.append(subdirfile)

    def size(self):
        return sum([sub.size() for sub in self.subDirFile])

    def sumFileUnder(self, threshold):
        total = 0
        itSize = self.size()
        if itSize <= threshold:
            total += itSize
        total += sum([sub.sumFileUnder(threshold) for sub in self.subDirFile])
        return total

    def __str__(self):
        return f"- {self.name}\n" + ''.join(['\t' + str(sub) + '\n' for sub in self.subDirFile])

class File:
    def __init__(self, name, parent, fileSize):
        self.name = name
        self.parent = parent
        self.fileSize = fileSize

    def size(self):
        return self.fileSize

    def sumFileUnder(self, threshold):
        return 0

    def __str__(self):
        return f"\t- {self.name}, size={self.fileSize}"

def FindMatchDirFile(dirToLookInto, name):
    index = 0
    matchingDirFile = dirToLookInto.subDirFile[index]
    while matchingDirFile.name != name:
        index += 1
        matchingDirFile = dirToLookInto.subDirFile[index]
    return matchingDirFile

root = Dir('/', None)

currentDirFile = root

for line in data:
    splitted = line.rstrip().split(' ')
    match splitted[0]:
        case '$':
            match splitted[1]:
                case 'cd':
                    match splitted[2]:
                        case '/':
                            currentDirFile = root
                        case '..':
                            currentDirFile = currentDirFile.parent
                        case _:
                            currentDirFile = FindMatchDirFile(currentDirFile, splitted[2])
                case 'ls':
                    pass
        case 'dir':
            currentDirFile.addsub(Dir(splitted[1], currentDirFile))
        case _:
            currentDirFile.addsub(File(splitted[1], currentDirFile, int(splitted[0])))

print(root.sumFileUnder(threshold))
