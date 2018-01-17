# CarND-Controls-PID

## Reflection

Objective of the project is to build a PID controller that can provide steer and throttle commands to the simulator in such a way that the vehcile can reliably drive around the track. The simulator provides the required 'cross track error', 'velocity' and 'steering angle' for the controller to use as inputs and to arrive at commands to pass back to the simulator. 

The proportional component (P) of the P-I-D controller obviously has the direct and observable effect on the vehicles behavior and it ensures the vehicle is counter steered to offset the cross track error. However using the P-Component alone will always end up in overshooting the center of the lane and will have a wave like effect causing motion sickness to the passengers of the vehicle. In order to deal with this situation, a Differential (D) component has to be introduced. The D-Component will ensure the vehicle approaches the center more smoothly. Also to counteract the inherent bias, we will have to introduce an 'I' (Integral) component that aims at reducing the overall error accumulated over a period while the vehicle tries to steer towards the center. This components can be very helpful especially around the curves and bends on the track

## Project Rubric Discussion Points 

At first,I started with just one PID controller to control the steering value. In order to arrive at the optimal starting value for 'P','I' and 'D' , I have implemented a twiddle with starting values as zeros for all three components . But I was unsuccessful at arriving at the optimal values using twiddle as the vehicle immediately steered away from the track and was never able to get back on the track. After many unsuccessful attempts trying to fine tune the step size values for incrementing and decrementing the initial values , i have finally decided to manually arrive at the optimal values.

Once i computed the approximate values manually, i then fine tuned them using 'twiddle' but with a very small step size. Using these values, the vehicle was successfull in going around the track smoothly (ofcourse, not smooth enough to die for). The output of the PID controller - controlling the steering value alone can be seen below.

Here's a [link to my video result](./videos/PID_Control_Steer_Only_480.mov)
(or)
https://youtu.be/WjcG2Kdrb4Q

The project also made a mention of increasing the speed limit to 100 MPH from the earlier 30 MPH limit. To try this out,  I used another controller to control the speed at which the vehicle can travel.This controllers takes in the earlier computed steering value as input(from the prior controller) and reduces the speed whenever the steering value is large. This is similar to the PID controller used to reduce the cross track error, however in this case we are just proportionally reducing the speed based on the steering value. While implementing the controller, i ran into 'twiddling' problems similar to what i have explained earlier and had to manually arrive at the approximate intial values. Unfortunately none of the values i used worked well when the speed limit was set to 100 MPH. So, i started reducing the speed limit until the vehicle was able to go around  without having to leave the track. At a speed limit of 60 MPH , i was able to obtain satisfactory results. I later fine tuned the P-I-D values for both steering and throttle control when both were in effect.  The output of the PID controller - controlling the steering value and throttle  can be seen below. Unfortunately the video is not of the highest quality as i believe due to the simulator taking away the system resources from the screen capture application i used. Also, the vehicle barely was able to stay on the track and can be further fine tuned by applying forecasting techinques (ability to predict future steering values...).

Here's a [link to my video result](./videos/PID_Control_Steer_Throttle_480.mov)
(or)
https://youtu.be/bk3ScC4Q864



