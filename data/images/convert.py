import numpy as np
from PIL import Image

im = np.array(Image.open("smiley.jpg"));

background = im[1001][1001]

centre = 1999/2
for i in range(len(im)):
    for j in range(len(im[0])):
        if(im[i][j][0] > 10 and im[i][j][1] > 10):
            im[i][j]=background
        if( (i-centre)*(i-centre) + (j -centre) * (j - centre) > 900*900 ):
            im[i][j]=background

image = Image.fromarray(im)
image.save("sameer.jpg")