from __future__ import print_function

# ----  |   height + 2
# |  |  |   height + 1
# |  |  |   2
# |  ----   1
#
# numLeds = 16
# width = 4
# turn = 2
# => height = 2

numLeds = 200
width = 2
turns = 15

height = (numLeds -(width * turns) - 2) / (turns + 1)

#initialise with first upwards height (with an extra led in the bottom as there is no width coming in)
down = True
currX = 1
locs = ["Location(1, {})".format(y) for y in range(1, height + 2)]
for i in range(turns):
    if down:
        locs += ["Location({}, {})".format(x, height + 2) for x in range(currX, currX + width)]
        locs += ["Location({}, {})".format(currX + width - 1, y) for y in range(height + 1, 1, -1)]
    else:
        locs += ["Location({}, {})".format(x, 1) for x in range(currX, currX + width)]
        locs += ["Location({}, {})".format(currX + width - 1, y) for y in range(2, height + 2)]
    down = not down
    currX += width - 1

if down:
    locs += ["Location({}, {})".format(currX, height + 2)]
else:
    locs += ["Location({}, {})".format(currX, 1)]

leftOver = numLeds - (2 + height * (turns + 1) + width * turns)

locStr = "Location ledLocations[] = {" + (", ".join(locs)) + "};\n#leftOver = " + str(leftOver)

print(locStr);