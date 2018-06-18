# Final Project: The Assisted Ab Wheel

### Example Youtube Video of Proper Ab Wheel Usage

[![](https://github.com/briannaodom/FinalProject/blob/master/images/abwheel.png)](https://www.youtube.com/watch?v=rqiTPdK1c_I)

### Goal

Create an Ab Wheel that will have an assisted functionality. The user will roll forward extending the arms and body outward on their knees or in a plank position. Once they have reached maximum extension, they will roll back up to their initial position by pressing a button that will cause the wheel to rotate in the direction that is towards their body. This will allow beginner or out of shape users to build their core muscles. Once a user has achieved an optimal core strength, they can use the Ab Wheel manually.

### Spring Quarter Objectives

1. Computing specs for motor that can handle a load that is dependent on the weight of a user
2. Creating a circuit for hbridge, encoder, and current sensor with Arduino Uno
3. Designing PID controller for current/torque control of the motor
4. Designing a desktop model to simulate a person pushing on an abwheel

More objectives will be added for Summer Quarter at the end of the Spring Quarter

### Supplies

1. Hbridge Driver in this case the DVR8835
2. 2 Potientiometers- one to setup hbridge, one to control LCD lighting
3. LCD to display desired values such as PWM, current, and rotation angle of the motor
4. Battery Pack in this case 6V
5. Encoder Chip
6. Current Sensor Chip
7. DC Motor
8. Arduino Uno

### Componenents

#### LCD 

The LCD currently displays the PWM value that is computed from the analog pin wired to the potientiometer. When the value of the potientiometer increases from 0 to 255, the motor spins quicker in the forward direction and the LCD displays that value.

Useful for LCD and potientiometer setup: 

1. Schematic of LCD and potientiometer [link](https://github.com/briannaodom/FinalProject/blob/master/images/LCD_POT.png)
2. Code for LCD setup [link](https://github.com/briannaodom/FinalProject/blob/master/src/lcdsetup.ino)

#### Hbridge

The hbridge DRV3385 chip is currently wired to drive the DC motor in a forward direction when a button is unpressed and in the reverse direction when a button is being pressed. 

The datasheet to wire the hbridge can be found on the Pololu website [here](https://www.pololu.com/product/2135).

Useful for hbridge and button setup:

1. Schematic of hbridge [link](https://github.com/briannaodom/FinalProject/blob/master/images/hbridge.png)
2. Schematic of button [link]()
3. Code for hbridge setup [link](https://github.com/briannaodom/FinalProject/blob/master/src/hbridgesetup.ino)

#### Current Sensor 

Useful for current sensor setup:

1. Schematic of current sensor [link](https://github.com/briannaodom/FinalProject/blob/master/images/currentsensor.png)
2. Code for current sensor setup [link](https://github.com/briannaodom/FinalProject/blob/master/src/currentsensorsetup.ino)

#### Encoder 

Useful for encoder setup:
1. Schematic of encoder [link](https://github.com/briannaodom/FinalProject/blob/master/images/encoder.png)
2. Code for encoder setup [link](https://github.com/briannaodom/FinalProject/blob/master/src/encodersetup.ino)

#### Youtube Demo of Hbridge Controlling the Motor and LCD Displaying PWM

[![](https://github.com/briannaodom/FinalProject/blob/master/images/BreadboardWHbridge.JPG)](https://www.youtube.com/watch?v=onr-n5QG-nY&feature=youtu.be)

### Measurements for Desktop Model

Currently taking measurements to build a model of a person in push up position with knees on the ground holding the ab wheel that will be guided by a motor. The measurements have come from my cohort. I'd like to get at least 10-15 subjects before I take an average of each measurement. 

This will have to be redone as the second measurement should be from shoulder to knee. 
For the sake of the desktop model, the third and fourth columns respectfully will have a ration of 1:4, as I did not get these measurements from people in my cohort.

|shoulder to arms  | shoulder to hip   | side of hip to side of hip  | side of arm to side of arm
|------------------|-------------------|-----------------------------|----------------------------|
| 24"              | 18"               |                             |                            |
| 25"              | 18"               |                             |                            |
| 25.5"            | 19"               |                             |                            |
| 27"              | 20"               |                             |                            |
| 27"              | 21"               |                             |                            |
| 26"              | 20"               |                             |                            |
| 24"              | 18"               |                             |                            |


I ended up making the [arm one](https://github.com/briannaodom/FinalProject/blob/master/onShapeDocs/Arm1ForAbWheel.png) and [arm two](https://github.com/briannaodom/FinalProject/blob/master/onShapeDocs/Arm2.png) about 8" with a 6" distance between holes in OnShape. If I ever make a more complex model, I'd use the measurements above or at least a 2:1 or 3:1 ratio between arms and body for the desktop model.

### Measurements for onShape Modeling

Sketch and extrude pictures of all the parts used to build the desktop version of the ab wheel can be found under [OnshapeDocs](https://github.com/briannaodom/FinalProject/tree/master/onShapeDocs)

A future assembly through OnShape will be done showing the whole model put together. However, here is a picture of the current model of my build. The [hub](https://github.com/briannaodom/FinalProject/blob/master/onShapeDocs/HubExtrude.png) is directly attached to the motor and wheel which sits on [slots](https://github.com/briannaodom/FinalProject/blob/master/onShapeDocs/SlotBoxExtrude.png) allowing the motor to move back and forth, when it rotates. 

Due to an error in measurement of the height of the slot box, a second [track](https://github.com/briannaodom/FinalProject/blob/master/onShapeDocs/Track.png) was made with for the wheel to sit on so it is not hovering. I used two extra hubs glued between the tracks to help bridge the distance.

[![](https://github.com/briannaodom/FinalProject/blob/master/images/DesktopAbWheel.jpg)]()

### Current Control 

My main code is [motorandspringsetup](https://github.com/briannaodom/FinalProject/blob/master/src/motorandspringsetup_ino/motorandspringsetup_ino.ino). 

Basically, a potentiometer is hooked up to control k the spring constant. The higher k, the stronger or harder the spring, thus the higher the resistance of the motor. Under the currentController function, we are keeping track of the encoder moving away from 0, the point we want the wheel to be at. Thus our desired current is k times the error of the distance of the motor from its original starting position. 

Next, a second error is calculated which is the error between the desired current and the actual current being measured from the motor with the current sensor. PD gains are given to get the motor to add resistance and keep the wheel in line in the CW direction of the rotation of the motor, which calculates a new pwm value that is sent to the motor. Anti-windup limits the new pwm values. 

### Issues/Limitations

The current motor I am using could only go up to 11V, thus even at the highest voltage and with two bolts holding the motor down in the slots, the motor had a hard time being moved. Thus, it was hard to figure out the proper gains for the PID of the [currentcontroller](https://github.com/briannaodom/FinalProject/blob/master/src/motorandspringsetup_ino/motorandspringsetup_ino.ino).

Therefore, for now, I provided a link to a video that shows the wheel moving in a CW rotation, 
which is basically the wheel trying to go back to 0. A little oscillation at the end of the wheel rotating occurs, so a higher or better derivative gain needs to be found.   

For now, a motor that can provide a higher torque needs to be bought for the desktop model.

### Future Goals

Fine tune the PD gains better with matlab, as what I currently have is by eye. 

Do measurements for a motor that would provide enough torque to handle a human body.

Create a new circuit and design a pcb board that includes an on/off switch.

Create a bigger model in onshape and buy the parts to put it all together.


