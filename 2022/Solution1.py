data = open("Input1.txt", "r")

maxLutin = 0
secondLutin = 0
thirdLutin = 0

currentLutin = 0

for line in data:
    if line is not '\n':
        currentLutin += int(line)
    else:
        if currentLutin > maxLutin:
            maxLutin, secondLutin, thirdLutin = currentLutin, maxLutin, secondLutin
        elif currentLutin > secondLutin:
            secondLutin, thirdLutin = currentLutin, secondLutin
        elif currentLutin > thirdLutin:
            thirdLutin = currentLutin
        currentLutin = 0

print(maxLutin + secondLutin + thirdLutin)

data.close()
