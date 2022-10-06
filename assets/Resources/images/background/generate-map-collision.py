import imageio.v2 as iio
import numpy as np
import os
import cv2
import imutils

mapimage = "C:/Users/Alexa/Documents/GitHub/R-Type/assets/Resources/images/background/testing_original.png"
pic = iio.imread(mapimage)

rows, cols = (pic.shape[0], pic.shape[1])
arr = np.zeros((rows, cols))

i = rows -1
while i >= 0:
	j = cols -1
	while j >= 0:
		if pic[i,j,0] == 63 and pic[i,j,1] == 72 and pic[i,j,2] == 204:
			arr[i][j] = 0
		else:
			arr[i][j] = 255
			#if (i + 1 < rows and arr[i+1][j] == 255) or (j + 1 < cols and arr[i][j+1] == 255):
			#	arr[i][j] = 5
			#elif (i + 1 < rows and arr[i+1][j] == 5) or (j + 1 < cols and arr[i][j+1] == 5):
			#	arr[i][j] = 255
		j -= 1
	i -= 1
	print((i / rows ) * 100, "%")

image = iio.imwrite("C:/Users/Alexa/Documents/GitHub/R-Type/assets/Resources/images/background/testing.png", arr)

image = cv2.imread("C:/Users/Alexa/Documents/GitHub/R-Type/assets/Resources/images/background/testing.png")
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

#create a binary thresholded image from gray image
ret,thresh = cv2.threshold(gray,127,255,0)

#find contours in the thresholded image
contours,hierarchy = cv2.findContours(thresh,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)

#for all countours get an approximated inscribed rectangle
for cnt in contours:
	rect = cv2.minAreaRect(cnt)
	box = cv2.boxPoints(rect)
	box = np.int0(box)
	cv2.drawContours(image,[box],0,(0,0,255),2)



# show the image
cv2.imshow("thresh", thresh)
cv2.imshow("Image", image)
cv2.waitKey(0)