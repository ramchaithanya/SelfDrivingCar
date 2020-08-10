# **Traffic Sign Recognition** 

## Writeup

[//]: # (Image References)


### Data Set Summary & Exploration

#### 1. Provide a basic summary of the data set. In the code, the analysis should be done using python, numpy and/or pandas methods rather than hardcoding results manually.


* The number of examples in training set is 34799
* The number of examples in validation set is 4410
* The number of examples in test set is 12630
* The shape of a traffic sign image is (32, 32, 3)
* The number of unique classes/labels in the data set is 43

#### 2. Include an exploratory visualization of the dataset.

Three charts has been plotted to visualize the data set.
Each individual chart gives information of number of examples available based on different classes.
The charts plotted visualizes training data,validation data and testing data
The plotted image can be found at ./Output/exploration_data_set.png

[image1]: ./Output/exploration_data_set.png "Dataset Exploration"

### Design and Test a Model Architecture

#### 1. Describe how you preprocessed the image data. What techniques were chosen and why did you choose these techniques? Consider including images showing the output of each preprocessing technique. Pre-processing refers to techniques such as converting to grayscale, normalization, etc. (OPTIONAL: As described in the "Stand Out Suggestions" part of the rubric, if you generated additional data for training, describe why you decided to generate additional data, how you generated the data, and provide example images of the additional data. Then describe the characteristics of the augmented training set like number of images in the set, number of images for each class, etc.)

* As a first step, I decided to convert the images to grayscale and then reshaped the image to 32,32,1,i have used skimage rgb2gray to acheive the same.

* On the grayscale images i have applied normalization to rescale the data to have values between 0 and 1

[image2]: ./Output/original_gray_normalized.png "Gray Normalized Image"
 

#### 2. Describe what your final model architecture looks like including model type, layers, layer sizes, connectivity, etc.) Consider including a diagram and/or table describing the final model.

I have followed lenet-5 architecture with some modifications i.e instead of average pooling i choose maxpooling and instead two fully connected layers i have used 3 fully connected layers

My final model consisted of the following layers:

| Layer         		|     Description	        					| 
|:---------------------:|:---------------------------------------------:| 
| Input         		| 32x32x3 RGB image   							| 
| Convolution 3x3     	| 1x1 stride, valid padding, outputs 28x28x12 	|
| Relu					| Relu Activation								|
| Max pooling	      	| 2x2 stride,  outputs 14x14x12, valid padding	|
| Convolution 3x3	    | output 10x10x32								|
| Relu           		| Relu Activation								|
| Max pooling			| 2x2 string,valid padding,outputs 5x5x32		|
| Flatten				| outputs 800									|
| Fully connected		| outputs 120									|
| Relu          		| Relu Activation								|
| Fully connected		| outputs 84									|
| Relu          		| Relu Activation								|
| Fully connected		| outputs 43									|


#### 3. Describe how you trained your model. The discussion can include the type of optimizer, the batch size, number of epochs and any hyperparameters such as learning rate.

I used 50 epochs which gave accuracies as below
training Accuracy = 1.000
Validation Accuracy = 0.957
test Accuracy = 0.942
I used adam optimizer with learning rate of 0.001
I didnt use batch size as i didnt have any memory issues.


#### 4. Describe the approach taken for finding a solution and getting the validation set accuracy to be at least 0.93. Include in the discussion the results on the training, validation and test sets and where in the code these were calculated. Your approach may have been an iterative process, in which case, outline the steps you took to get to the final solution and why you chose those steps. Perhaps your solution involved an already well known implementation or architecture. In this case, discuss why you think the architecture is suitable for the current problem.

If a well known architecture was chosen:
* What architecture was chosen?
I have chosen lenet-5 architecture with some modifications
* Why did you believe it would be relevant to the traffic sign application?
I have read lenet architercure is an excellent first architecture,simple to understand and straightforward.
* How does the final model's accuracy on the training, validation and test set provide evidence that the model is working well?
   My final model results were:
      * training set accuracy of 1.000
      * validation set accuracy of 0.945
      * test set accuracy of 0.939

### Test a Model on New Images

#### 1. Choose five German traffic signs found on the web and provide them in the report. For each image, discuss what quality or qualities might be difficult to classify.

Here are five German traffic signs that I found on the web:

[image4]: ./webimages/60_kmh.jpg "60 kms"
[image5]: ./webimages/stop_sign.jpg "stop_sing"
[image6]: ./webimages/yield_sign.jpg "yield_sign"
[image7]: ./webimages/left_turn.jpg "left_turn"
[image8]: ./webimages/road_work.jpg "road_work"

#### 2. Discuss the model's predictions on these new traffic signs and compare the results to predicting on the test set. At a minimum, discuss what the predictions were, the accuracy on these new predictions, and compare the accuracy to the accuracy on the test set (OPTIONAL: Discuss the results in more detail as described in the "Stand Out Suggestions" part of the rubric).

Here are the results of the prediction:

| Image			        |     Prediction	        					| 
|:---------------------:|:---------------------------------------------:| 
| 60_kmh.jpg      		| Ahead only  									| 
| stop_sign.jpg			| Stop   										|
| yield_sign.jpg		| Yield											|
| left_turn.jpg   		| Keep right					 				|
| road_work.jpg			|General caution      							|


The model was able to correctly guess 2 of the 5 traffic signs, which gives an accuracy of 40%.However,my model test accuracy is 93% which is a huge deviation.

#### 3. Describe how certain the model is when predicting on each of the five new images by looking at the softmax probabilities for each prediction. Provide the top 5 softmax probabilities for each image along with the sign type of each probability. (OPTIONAL: as described in the "Stand Out Suggestions" part of the rubric, visualizations can also be provided such as bar charts)

Below are the 5 softmax probabilities for each image
INFO:tensorflow:Restoring parameters from ./lenet
Image: ./webimages/60_kmh.jpg
Probabilities:
   0.971387 : 35 - Ahead only
   0.028609 : 3 - Speed limit (60km/h)
   0.000004 : 2 - Speed limit (50km/h)
   0.000000 : 5 - Speed limit (80km/h)
   0.000000 : 10 - No passing for vehicles over 3.5 metric tons

Image: ./webimages/stop_sign.jpg
Probabilities:
   1.000000 : 14 - Stop
   0.000000 : 38 - Keep right
   0.000000 : 1 - Speed limit (30km/h)
   0.000000 : 34 - Turn left ahead
   0.000000 : 13 - Yield

Image: ./webimages/yield_sign.jpg
Probabilities:
   1.000000 : 13 - Yield
   0.000000 : 25 - Road work
   0.000000 : 35 - Ahead only
   0.000000 : 3 - Speed limit (60km/h)
   0.000000 : 2 - Speed limit (50km/h)

Image: ./webimages/left_turn.jpg
Probabilities:
   1.000000 : 38 - Keep right
   0.000000 : 34 - Turn left ahead
   0.000000 : 15 - No vehicles
   0.000000 : 13 - Yield
   0.000000 : 32 - End of all speed and passing limits

Image: ./webimages/road_work.jpg
Probabilities:
   1.000000 : 18 - General caution
   0.000000 : 40 - Roundabout mandatory
   0.000000 : 1 - Speed limit (30km/h)
   0.000000 : 0 - Speed limit (20km/h)
   0.000000 : 11 - Right-of-way at the next intersection

