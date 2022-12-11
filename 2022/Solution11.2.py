import operator

data = open("Input11.txt", "r")

operators = {"+": operator.add, "*": operator.mul}

class Monkey:
    def __init__(self, ID, startingItems, operation, test, monkeyTrue, monkeyFalse):
        self.ID = ID
        self.items = startingItems
        self.operation = operation
        self.test = test
        self.monkeyTrue = monkeyTrue
        self.monkeyFalse = monkeyFalse
        self.totalItemInspected = 0

    def PlayTurn(self):
        for item in self.items:
            left = item
            right = item if self.operation[2] == "old" else int(self.operation[2])
            new = operators[self.operation[1]](left, right) % getSMC()
            #new //= 3
            if new % self.test == 0:
                monkeys[self.monkeyTrue].addItem(new)
            else:
                monkeys[self.monkeyFalse].addItem(new)
            self.totalItemInspected += 1
        self.items = []

    def addItem(self, item):
        self.items.append(item)

    def __str__(self):
        return "Monkey " + str(self.ID) + ": " + str(self.items)

    def IDCard(self):
        return "Monkey " + str(self.ID) + ":\n\tStarting items: " + str(self.items) + "\n\tOperation: new = " + str(self.operation) + "\n\tTest: divisible by " + str(self.test) + "\n\t\tIf true: throw to monkey " + str(self.monkeyTrue) + "\n\t\tIf false: throw to monkey " + str(self.monkeyFalse)

def getSMC():
    SMC = 1
    for monkey in monkeys:
        SMC *= monkey.test
    return SMC

monkeys = []
cMItems = [] # currentMonkey
cMOperation = []
cMTest = 0
cMTrue = 0

for line in data:
    splitted = line.rstrip().split()
    if len(splitted) > 0:
        match splitted[0]:
            case "Starting":
                cMItems = [int(item.strip(',')) for item in splitted[2:]]
            case "Operation:":
                cMOperation = splitted[3:]
            case "Test:":
                cMTest = int(splitted[3])
            case "If":
                match splitted[1]:
                    case "true:":
                        cMTrue = int(splitted[5])
                    case "false:":
                        monkeys.append(Monkey(len(monkeys), cMItems, cMOperation, cMTest, cMTrue, int(splitted[5])))

for monkey in monkeys:
    print(monkey.IDCard() + "\n")

for i in range(10000):
    if i % 100 == 0 :
        print("Round",i)
    for monkey in monkeys:
        monkey.PlayTurn()

totalInspects = sorted([monkey.totalItemInspected for monkey in monkeys])

print(totalInspects[-1] * totalInspects[-2])
