# CarND-Controls-PID

Self-Driving Car Engineer Nanodegree Program

## Project Rubric

### 1. Your code should compile.

### 2. The PID procedure follows what was taught in the lessons.

My PID procedure follows what was taught in the lessons.
In PID.cpp file i have initialized p_error,i_error,d_error with <values> respectively.
The coefficients(Kp,Ki,Kd) chosen for proportional,Integral and Derivative are <value> respectively.The code changes can be found in main.cpp file in line number

### 3. Describe the effect each of the P, I, D components had in your implementation.

Proportional control is equal to cross track error. If we only use Proportional control, then the steering value will be equal to cte times Kp coefficient.So in case we use only P control the car weaves a lot and will go out of track after travelling some distance.The same can be seen in the below gif.

#### Only 'P' Controller
![P](./Data/Only_P.gif)

Integral control 

#### Only 'I' Controller
![I](./Data/Only_I.gif)

#### Only 'D' Controller
![D](./Data/Only_D.gif)

### 4. Describe how the final hyperparameters were chosen.

### 5. The vehicle must successfully drive a lap around the track.




