# Final Project: The Assisted Ab Wheel

#### Example Youtube Video of Proper Ab Wheel Usage

[![](https://github.com/briannaodom/FinalProject/blob/master/images/abwheel.png)](https://www.youtube.com/watch?v=rqiTPdK1c_I)

#### Goal

Create an Ab Wheel that will have an assisted functionality. The user will roll forward extending the arms and body outward on their knees or in a plank position. Once they have reached maximum extension, they will roll back up to their initial position by pressing a button that will cause the wheel to rotate in the direction that is towards their body. This will allow beginner or out of shape users to build their core muscles. Once a user has achieved an optimal core strength, they can use the Ab Wheel manually.

#### Spring Quarter Objectives

1. Computing specs for motor that can handle a load that is dependent on the weight of a user
2. Creating a circuit for hbridge, encoder, and current sensor with Arduino Uno
3. Designing PID controller for current/torque control of the motor
4. Designing a desktop model to simulate a person pushing on an abwheel

More objectives will be added for Winter Quarter at the end of the Spring Quarter

#### Componenents

##### LCD 

The LCD currently displays the PWM value that is computed from the analog pin wired to the potientiometer. When the value of the potientiometer increases from 0 to 255, the motor spins quicker in the forward direction and the LCD displays that value.

Schematic of LCD [link]()
Schematic of potientiometer [link]()
Code for LCD setup [link]()

###### Hbridge

The hbridge DRV3385 chip is currently wired to drive the DC motor in a forward direction when a button is unpressed and in the reverse direction when a button is being pressed. 

The datasheet to wire the hbridge can be found on the Pololu website [here](https://www.pololu.com/product/2135)

Schematic of hbridge [link]()
Schematic of button [link]()
Code for hbridge setup [link]()

##### Youtube Demo of Hbridge Controlling the Motor and LCD Displaying PWM

[![](https://github.com/briannaodom/FinalProject/blob/master/images/BreadboardWHbridge.JPG)](https://www.youtube.com/watch?v=onr-n5QG-nY&feature=youtu.be)




