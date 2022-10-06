import imageio as iio
import numpy as np
import os

mapimage = "F:/GitHub/R-Type/assets/Resources/images/background/main-level-test.png"
pic = iio.imread(mapimage)

rows, cols = (pic.shape[0], pic.shape[1])
arr = np.zeros((rows, cols))

i = 0
while i < 1:
	j = 0
	while j < 1:
		
		if pic[i,j,0] == 63 and pic[i,j,1] == 72 and pic[i,j,2] == 204:
			arr[i][j] = 0
		else:
			arr[i][j] = 255
		#
		#

image = iio.imwrite("F:/GitHub/R-Type/assets/Resources/images/background/testing.png", arr)