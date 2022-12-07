data = open("Input7.txt", "r")

class Dir:
    def __init__(self, name, parent):
        self.name = name
        self.parent = parent
        self.subDirFile = []

    def addsub(self, subdirfile):
        self.subDirFile.append(subdirfile)

    def size(self):
        return sum([sub.size() for sub in self.subDirFile])

    def __str__(self):
        return print(f"- {self.name}\n", print(sub for sub in self.subDirFile))

class File:
    def __init__(self, name, parent, fileSize):
        self.name = name
        self.parent = parent
        self.fileSize = fileSize

    def size(self):
        return self.fileSize

    def __str__(self):
        return print(f"- {self.name}, size={self.fileSize}")

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
            currentDirFile.addsub(File(splitted[1], currentDirFile, splitted[0]))

print(root)

print(totalSize)
