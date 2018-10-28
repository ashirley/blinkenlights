from __future__ import print_function
from PIL import Image

im = Image.open("christmasPalette.png")

rgbVals = ", ".join(["0x{r:02X}{g:02X}{b:02X}".format(r=r,g=g,b=b) for (r,g,b) in im.getdata()])

print("CRGB foo[] = { " + rgbVals + " };\nconst int fooCount = " + str(len(im.getdata())) + ";")

#TODO:
# support multi line images
# Use argparse
# Support downsampling / Use DEFINE_GRADIENT_PALETTE?
