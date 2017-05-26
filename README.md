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

1. Schematic of LCD [link]()
2. Schematic of potientiometer [link]()
3. Code for LCD setup [link](https://github.com/briannaodom/FinalProject/blob/master/src/lcdsetup.ino)

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
1. Schematic of encoder [link]()
2. Code for encoder setup [link](https://github.com/briannaodom/FinalProject/blob/master/src/encodersetup.ino)

#### Youtube Demo of Hbridge Controlling the Motor and LCD Displaying PWM

[![](https://github.com/briannaodom/FinalProject/blob/master/images/BreadboardWHbridge.JPG)](https://www.youtube.com/watch?v=onr-n5QG-nY&feature=youtu.be)

### Measurements for Desktop Model

Currently taking measurements to build a model of a person in push up position with knees on the ground holding the ab wheel that will be guided by a motor. The measurements have come from my cohort. I'd like to get at least 10-15 subjects before I take an average of each measurement. 

shoulder to arms    shoulder to hip     side of hip to side of hip      side of arm to side of arm
1. 24"              18"
2. 25"              18"
3. 25.5"            19"
3. 27"              20" 
4. 27"              21"
5. 26"              20"
6. 24"              18"




