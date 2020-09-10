# CarND-Path-Planning-Project
Self-Driving Car Engineer Nanodegree Program
  
## Project Rubric

###  The code compiles correctly.
The code has compiled correctly and compilation output can be seen below.

![Compilation](./Images/compilation.png)

### The car is able to drive at least 4.32 miles without incident.

With my changes the car was able to drive more than 4.32 miles infact 7+ miles without any incidents. The below image depicts the same.

![Path_Planning](./Images/Path_planning.png)

### The car drives according to the speed limit.

I set the speed limit to 49.9 and during the whole 4.32 mile drive there was no instance of car driving above the speed limit

### Max Acceleration and Jerk are not Exceeded.

I set the max accelaration to 0.224 and during the whole 4.32 mile drive there was no instance of car driving above the max acceleration limit

### Car does not have collisions.

There was no instance of collision during the 4.32 mile drive

### The car stays in its lane, except for the time between changing lanes.

The car stays always in the lane and only change lanes when required.

### The car is able to change lanes

Whenever there is a car ahead which is driving slow and there are no cars in any of the other lanes the car is able to change the lanes.

### There is a reflection on how to generate paths.

* After capturing Sensor fusion data in a two dimensional vector, using a range based for loop iterated through the vector,found in which lane all the observed car is in i.e if the sensor fusion value is in between 0-3 then the observed car would be in lane 0 and if the value is in between 4-7 then the observed car would be in lane 1 and if the value is in between 8-11 then the observed car would be in lane 2(function getObservedCarLane,line no 20-39).Later gathered the velocity along x and y axis. Using the velocity gathered,calculated speed,estimated the car position and using the function getCarPosition(line no 41-66) found the whether the car is "AHEAD","LEFT","RIGHT" and stored in a set.

* Using the set of all the cars around, checked whether the ego car has to stay in the lane or go left or right or go in reduced speed,so that the ego car will not collide the car ahead of it i.e if there is a car ahead either we have to go left or right or slow down.This decision is based on by checking in the set previously populated and whether lane is > 0 or lane != 2 also whether the car is in the range of + or - 30 i.e 30meters infront or 30 meters behind.(function getCarBehavior,line no 68-86)

* Trajectory is totally inspired by Q&A video provided by Udacity coursework.Using the car_x,car_y,car_yaw, i have calcualted previous points if there are less than 2 previous points othewise i have used the last two points(from line no 198-222).After that i have set 3 future waypoints using car positions,lane and waypoints of x,y and s. I have used getXY helper function as car_s is having frenet cordinates.later i have converted to car local co-ordinates(line no 225-241).As mentioned in the Q & A video i have used spline for trajectory generation and initialized the spline with ptsx and ptsy. Next, i have added the previous points for continuity to the future path(line no 248-252).Target point has been set ahead of 30ms to the current point,passing x to spline gives y point.Finally, i had calculated x,y's along the spline and for the same x,y's i have rotated and shifted back to global coordinates and added to next x,y value vector.

### Additional Points

* I have observed in some cases, where the car in the left lane suddenly move to right line(the car is almost side by side with ego car) i have observed a collision.To avoid this we might need addition sensor data to detect it and use that information to avoid the collision.