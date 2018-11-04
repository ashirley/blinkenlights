from __future__ import print_function

numLeds = 50
width = 4

length = (numLeds -width + 2) / 2

locStr = "Location ledLocations[] = {" + (", ".join(
    ["Location({}, 1)".format(x) for x in range(1, length + 1)] +
    ["Location({}, {})".format(length, y) for y in range(2, width)] +
    ["Location({}, {})".format(x, width) for x in range(length, 0, -1)]
)) + "};"

print(locStr);