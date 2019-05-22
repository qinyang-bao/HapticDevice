# HapticDevice
2A URA, a device to provide haptic feedback

This project aims to control 6 vibration motors individually to construct different haptic feedback patterns, using an Arduino.  
  
This is achieved by leveraging the power of drv2603 haptic driver, which takes a PWM signal as input and convert it to appropriate signals
for ERM/LRA vibration motors. The challenge is that the PWM signal needs to be at least 10 kHz, which is much faster than the analogWrite (a easy way to simulate PWM signals). Therefore, one must fiddle with the timer registers and use fast PWM. Also, since there are 3 timers on the ATmega328P processor each able to control 2 outputs, a total of 6 motors might be controlled separately.    

Currently, the software aspect (first version) of this project has been developped and tested. The next step is to finish and verify
the electrical and mechanical designs.    

The CAD of individual enclosing for the 307-100 vibration motor and the KiCad files for the breakout board for the drv2603 are also included in this repo.
