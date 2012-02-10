import Image
import ImageChops
import hashlib

#filenameA="E:/dev/Autodesk/maya/myplugin/project/liquid_/test/image_diff/check12.bmp"
#filenameB="E:/dev/Autodesk/maya/myplugin/project/liquid_/test/image_diff/check12_2.bmp"
#diffFilename="E:/dev/Autodesk/maya/myplugin/project/liquid_/test/image_diff/dif_12_12.bmp"
filenameA="E:/dev/Autodesk/maya/myplugin/project/liquid_/test/image_diff/check12.bmp"
filenameB="E:/dev/Autodesk/maya/myplugin/project/liquid_/test/image_diff/check15.bmp"
diffFilename="E:/dev/Autodesk/maya/myplugin/project/liquid_/test/image_diff/dif_12_15.bmp"

dataA = open(filenameA, 'rb').read()
dataB = open(filenameB, 'rb').read()

if hashlib.md5(dataA).hexdigest() != hashlib.md5(dataB).hexdigest():
  imageA = Image.open(filenameA)
  imageB = Image.open(filenameB)
  diff = ImageChops.difference(imageA, imageB)
  diff.save( diffFilename )
else:
  print "two images are equal.\n."
