# Network-cable-tester
This project was carried out in the first year of a bachelor's degree in computer science at the Haute école en Hainaut.

The purpose of the project is to check the operating status of a network cable (RJ45).
The cable tester includes the LED module and the PIC module. 
2 versions of the PCB have been made, the first one allows to be engraved only in single layer and the second one in double layer (space saving) .

In terms of PIC programming (PIC16F628A), 3 modes have been implemented: 
1. a short press of the button switches to the next LED
2. a long press speeds up the process by automatically switching to the following LED
3. a longer press lights up all the LEDs at the same time

# Usage

You can test the project with the Proteus simulation software and the right cabling.

![alt text](https://github.com/l-Legacy-l/Network-cable-tester/blob/master/Images/proteus.PNG)

You can also try it in real with a breadboard, the right hardware and MPlab software to upload the code into the PIC.
![alt text](https://github.com/l-Legacy-l/Network-cable-tester/blob/master/Images/breadboard.PNG)

You must use the compiled file NetworkCableTester.hex

For more information, you can consult the report detailing the software and hardware used and more detailed explanations (in French).
