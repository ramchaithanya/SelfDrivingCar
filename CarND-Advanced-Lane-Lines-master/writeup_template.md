## Writeup Template

### You can use this file as a template for your writeup if you want to submit it as a markdown file, but feel free to use some other method and submit a pdf if you prefer.

---

**Advanced Lane Finding Project**

The goals / steps of this project are the following:

* Compute the camera calibration matrix and distortion coefficients given a set of chessboard images.
* Apply a distortion correction to raw images.

* Use color transforms, gradients, etc., to create a thresholded binary image.

* Apply a perspective transform to rectify binary image ("birds-eye view").

* Detect lane pixels and fit to find the lane boundary.

* Determine the curvature of the lane and vehicle position with respect to center.

* Warp the detected lane boundaries back onto the original image.
* Output visual display of the lane boundaries and numerical estimation of lane curvature and vehicle position.


[//]: # (Image References)

[image1]: ./examples/undistort_output.png "Undistorted"
[image2]: ./test_images/test1.jpg "Road Transformed"
[image3]: ./examples/binary_combo_example.jpg "Binary Example"
[image4]: ./examples/warped_straight_lines.jpg "Warp Example"
[image5]: ./examples/color_fit_lines.jpg "Fit Visual"
[image6]: ./examples/example_output.jpg "Output"
[video1]: ./project_video.mp4 "Video"

## [Rubric](https://review.udacity.com/#!/rubrics/571/view) Points

### Here I will consider the rubric points individually and describe how I addressed each point in my implementation.  

---

### Writeup / README

#### 1. Provide a Writeup / README that includes all the rubric points and how you addressed each one.  You can submit your writeup as markdown or pdf.  [Here](https://github.com/udacity/CarND-Advanced-Lane-Lines/blob/master/writeup_template.md) is a template writeup for this project you can use as a guide and a starting point.  

You're reading it!

### Camera Calibration

#### 1. Briefly state how you computed the camera matrix and distortion coefficients. Provide an example of a distortion corrected calibration image.
The code for this is available in 3 cell of FindingLaneLines.ipynb.
1) First i checked the corners in the example images present in "camera_cal/"
2)I have noticed majority of the images are having 6*9 corners(2 images has 5*9 corners)
3)I followed the method explained in "Calibrating Camera" in the course and implemented chess board corners and calibrating the camera.Using the mtx and dst coefficients got from calibrateCamera opencv function undistorted the image.
4)Images can be found in "output_images/"
 

![alt text][image1]

### Pipeline (single images)

#### 1. Provide an example of a distortion-corrected image.
Using the previously caluculated mtx and distortion coefficients from chessboard images. Undistoreted the image.
The image can be found in ./output_images/test1_undistort.jpg
![alt text][./output_images/test1_undistort.jpg]
#### 2. Describe how (and identify where in your code) you used color transforms, gradients or other methods to create a thresholded binary image.  Provide an example of a binary image result.
1. Initially only i took Saturation part of HLS image(as i could see lane line visibily) and created a binary output by using only saturation values however when i applied the same on the video face issues.
2.I made a combined binary image consits of magnititude threshold,direction threshold,S part of hls and absolute sobel threshold.
3. The threshold parameters i found by trail and error method
#### 3. Describe how (and identify where in your code) you performed a perspective transform and provide an example of a transformed image.

1.Manually calculated source and destination points using below formula
```python
src = np.float32(
    [[(img_size[0] / 2) - 55, img_size[1] / 2 + 100],
    [((img_size[0] / 6) - 10), img_size[1]],
    [(img_size[0] * 5 / 6) + 60, img_size[1]],
    [(img_size[0] / 2 + 55), img_size[1] / 2 + 100]])
dst = np.float32(
    [[(img_size[0] / 4), 0],
    [(img_size[0] / 4), img_size[1]],
    [(img_size[0] * 3 / 4), img_size[1]],
    [(img_size[0] * 3 / 4), 0]])
```
and got source and destination as below


| Source        | Destination   | 
|:-------------:|:-------------:| 
| 585, 460      | 320, 0        | 
| 203.33, 720   | 320, 720      |
| 1126.666, 720 | 960, 720      |
| 695, 460      | 960, 0        |
2.I used these source and destination to apply perspective transformation and warp the image

![alt text][image4]

#### 4. Describe how (and identify where in your code) you identified lane-line pixels and fit their positions with a polynomial?

1.Took lower part of warped image and calculated histogram
2.Took two highest points from histogram as a starting point to determine where the lane pixels are
3.Iterated through 9 windows to track curvature and followed the steps mentioned in the course Finding the Lines:Sliding Windows
4.Was able to fit polynomial using polyfit function

![alt text][image5]

#### 5. Describe how (and identify where in your code) you calculated the radius of curvature of the lane and the position of the vehicle with respect to center.
1. The radius of curvature of the vehicle is calculated by following classroom material.I have used pixel to meter transformation and recomputed the fit again.Below code demonstrates the radius of curvature calculation
```python
    ym_per_pix = 30/720 # meters per pixel in y dimension
    xm_per_pix = 3.7/700 # meters per pixel in x dimension
    y_eval = np.max(ploty)
    #ploty = np.linspace(0, 719, num=720)# to cover same y-range as image
    quadratic_coeff = 3e-4 # arbitrary quadratic coefficient
    leftx = leftx[::-1]  # Reverse to match top-to-bottom in y
    rightx = rightx[::-1]  # Reverse to match top-to-bottom in y
    left_fit_cr = np.polyfit(ploty*ym_per_pix, leftx*xm_per_pix, 2)
    right_fit_cr = np.polyfit(ploty*ym_per_pix, rightx*xm_per_pix, 2)
    left_curverad = ((1 + (2*left_fit_cr[0]*y_eval*ym_per_pix + left_fit_cr[1])**2)**1.5) / np.absolute(2*left_fit_cr[0])
    right_curverad = ((1 + (2*right_fit_cr[0]*y_eval*ym_per_pix + right_fit_cr[1])**2)**1.5) / np.absolute(2*right_fit_cr[0])
    curvature = (left_curverad + right_curverad)/2
```
2.I have used mean of the pixels closest to car to calcualte the center of lane.The center of the image gives postion of the car.The difference between mean of the pixels and the center of the image gives the position of the vehicle with respect to center.



#### 6. Provide an example image of your result plotted back down onto the road such that the lane area is identified clearly.

1.Using perspective transform and reversing the source and destination values was able to warp the image back to original image.

![alt text][./output_images/final_transformed_image.jpg]

---

### Pipeline (video)

#### 1. Provide a link to your final video output.  Your pipeline should perform reasonably well on the entire project video (wobbly lines are ok but no catastrophic failures that would cause the car to drive off the road!).

1.Applied the pipeline to the video and result is below

Here's a [link to my video result](./project_video_output.mp4)
(./challenge_video_output1.mp4)
(./arder_challenge_video_output.mp4)

---

### Discussion

#### 1. Briefly discuss any problems / issues you faced in your implementation of this project.  Where will your pipeline likely fail?  What could you do to make it more robust?

Although applying the pipeline on the project video gave satisfactory results,however when i applied the same pipeline on challengevideo and harderchallengevideo, the lanes lines were not detected properly.The reason could be bumpy road,shadows on lanes.
Finding the right thresholding image was the harder part.Finally i combined all the binary images(magnitude,direction,absolutesobel,S part of HLS) to form a combined binary. Although i was not satisfied the combined thresholding image i used the same as my assignment was due for a long time.
Choosing a smaller section can help in finding the proper lanes for harder challenge video.Choosing better thresholding image can help in challeng video(lane lines was not detected underbridge and shadows is affecting lane lines)
