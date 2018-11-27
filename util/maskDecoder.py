from __future__ import print_function
from PIL import Image

im = Image.open("heart.png")

rgbVals = ", ".join(["0x{a:02X}".format(a=a) for a in im.getdata()])

print("byte foo[] = { " + rgbVals + " };\nconst int fooCount = " + str(len(im.getdata())) + ";")

#TODO:
# Use argparse
# Support downsampling?
