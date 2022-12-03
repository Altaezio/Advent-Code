data = open("Input2.txt", "r")

valueDictionnary = {"A": 1, "B": 2, "C": 3, "X": 1, "Y": 2, "Z":3}

score = 0

for line in data:
    alpha = valueDictionnary[line[0]]
    omega = valueDictionnary[line[2]]
    # score += omega + (omega - alpha + 1) % 3 * 3
    score += (alpha - 1 + omega - 2) % 3 + 1 + (omega - 1) * 3

print(score)
