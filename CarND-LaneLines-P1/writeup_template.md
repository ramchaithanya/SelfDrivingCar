# **Finding Lane Lines on the Road** 

## Writeup Template

### You can use this file as a template for your writeup if you want to submit it as a markdown file. But feel free to use some other method and submit a pdf if you prefer.

---

**Finding Lane Lines on the Road**

The goals / steps of this project are the following:
* Make a pipeline that finds lane lines on the road
* Reflect on your work in a written report


[//]: # (Image References)

[image1]: ./examples/grayscale.jpg "Grayscale"

---

### Reflection

### 1. Describe your pipeline. As part of the description, explain how you modified the draw_lines() function.

My pipeline consisted of 6 steps.

Step 1:
I converted the images to grayscale.his is done as it is easy for processing
Step 2:
I applied Gluassian Blur on grayscale image
Step 3:
I used canny helper function to find the edges in the image
Step 4:
i created vertices for selecting the region of interests
step 5:
I called houghlines helper function to draw the lines and get the lines.
Step 6:
Finally i used weighted_img helper function to blend lines and original image.

Additionally,extended the drawlines method based on the faq video to draw only straight line at all times.
### 2. Identify potential shortcomings with your current pipeline

1)The lines are slightly moving out of the lane lines.This needs to be improved.
2)As we are drawing a striaght line,we might see issues on a curved road.
3)This changes has not been tested on elevated road,we might potentially see some issues.


### 3. Suggest possible improvements to your pipeline

1)A possible improvement would be to make redlines always stay at the lane lines.
2)Issues seen in challenge video as the lines are intersecting.

Another potential improvement could be to ...
