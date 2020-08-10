# **Behavioral Cloning** 

## Writeup Template

### You can use this file as a template for your writeup if you want to submit it as a markdown file, but feel free to use some other method and submit a pdf if you prefer.

---

**Behavioral Cloning Project**

The goals / steps of this project are the following:
* Use the simulator to collect data of good driving behavior
* Build, a convolution neural network in Keras that predicts steering angles from images
* Train and validate the model with a training and validation set
* Test that the model successfully drives around track one without leaving the road
* Summarize the results with a written report


[//]: # (Image References)

[image1]: ./examples/placeholder.png "Model Visualization"
[image2]: ./examples/placeholder.png "Grayscaling"
[image3]: ./examples/placeholder_small.png "Recovery Image"
[image4]: ./examples/placeholder_small.png "Recovery Image"
[image5]: ./examples/placeholder_small.png "Recovery Image"
[image6]: ./examples/placeholder_small.png "Normal Image"
[image7]: ./examples/placeholder_small.png "Flipped Image"

## Rubric Points
### Here I will consider the [rubric points](https://review.udacity.com/#!/rubrics/432/view) individually and describe how I addressed each point in my implementation.  

---
### Files Submitted & Code Quality

#### 1. Submission includes all required files and can be used to run the simulator in autonomous mode

My project includes the following files:
* model.py containing the script to create and train the model
* drive.py for driving the car in autonomous mode
* model.h5 containing a trained convolution neural network 
* writeup_report.md or writeup_report.pdf summarizing the results

#### 2. Submission includes functional code
Using the Udacity provided simulator and my drive.py file, the car can be driven autonomously around the track by executing 
```sh
python drive.py model.h5
```

#### 3. Submission code is usable and readable

The model.py file contains the code for training and saving the convolution neural network. The file shows the pipeline I used for training and validating the model, and it contains comments to explain how the code works.

### Model Architecture and Training Strategy

#### 1. An appropriate model architecture has been employed

I have used the model provided by NVIDIA.The model has total of 5 convolutional layers.The first 3 layers has 2*2 stride and 5*5 kernel and remaining 2 layers are non strided convulution layer with 3*3 kernel.


#### 2. Attempts to reduce overfitting in the model

The model contains dropout layers in order to reduce overfitting a dropout layer has been added with probability 0.2

#### 3. Model parameter tuning

The model used an adam optimizer with learning rate of 0.0001.
No of EPOCHS = 3
Validation data Split = 0.2
Batch Size = 32
loss = mse

#### 4. Appropriate training data

I have used dataset provided by udacity to train my model.

### Model Architecture and Training Strategy

#### 1. Solution Design Approach


#### 2. Final Model Architecture

Model: "sequential"

_________________________________________________________________
lambda_3 (Lambda)            (None, 160, 320, 3)       0         
_________________________________________________________________
cropping2d_3 (Cropping2D)    (None, 66, 240, 3)        0         
_________________________________________________________________
conv2d_15 (Conv2D)           (None, 31, 118, 24)       1824      
_________________________________________________________________
conv2d_16 (Conv2D)           (None, 14, 57, 36)        21636     
_________________________________________________________________
conv2d_17 (Conv2D)           (None, 5, 27, 48)         43248     
_________________________________________________________________
conv2d_18 (Conv2D)           (None, 3, 25, 64)         27712     
_________________________________________________________________
conv2d_19 (Conv2D)           (None, 1, 23, 64)         36928     
_________________________________________________________________
dropout_3 (Dropout)          (None, 1, 23, 64)         0         
_________________________________________________________________
flatten_3 (Flatten)          (None, 1472)              0         
_________________________________________________________________
dense_12 (Dense)             (None, 100)               147300    
_________________________________________________________________
dense_13 (Dense)             (None, 50)                5050      
_________________________________________________________________
dense_14 (Dense)             (None, 10)                510       
_________________________________________________________________


#### 3. Creation of the Training Set & Training Process

I have used Udacity provided dataset for training set.
