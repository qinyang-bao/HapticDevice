# HapticDevice
2A URA, a device to provide haptic feedback

This project aims to control 6 vibration motors individually to construct different haptic feedback patterns, using an Arduino.  
  
This is achieved by leveraging the power of drv2603 haptic driver, which takes a PWM signal as input and convert it to appropriate signals
for ERM/LRA vibration motors. Also, since there are 3 timers on the ATmega328P processor each able to control 2 outputs, a total of 6 motors
might be controlled separately.    

Currently, the software aspect (first version) of this project has been developped and tested. The next step is to finish and verify
the electrical and mechanical designs.
