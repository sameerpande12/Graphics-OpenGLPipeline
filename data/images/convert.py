import numpy as np
from PIL import Image

# im = np.array(Image.open("smiley.jpg"));

# background = im[1001][1001]

# centre = 1999/2
# for i in range(len(im)):
#     for j in range(len(im[0])):
#         if(im[i][j][0] > 10 and im[i][j][1] > 10):
#             im[i][j]=background
#         if( (i-centre)*(i-centre) + (j -centre) * (j - centre) > 900*900 ):
#             im[i][j]=background

# image = Image.fromarray(im)
# image.save("sameer.jpg")

snowtex = np.array(Image.open("snowtex.jpg"));
smiley = np.array(Image.open("smiley.jpg"));
bg = smiley[1001][1001]

for i in range(len(smiley)):
    for j in range(len(smiley[0])):
            smiley[i][j] = snowtex[ i % snowtex.shape[0]][j%snowtex.shape[1]]

rect = np.array(Image.open("newsmiley.jpg"));

be_x = 666
be_y = 1000 - 167

for i in range(666):
    for j in range(333):
        smiley[i+be_x][j+be_y] = rect[i][j]



newimage = Image.fromarray(smiley)
newimage.save("newim.jpg")