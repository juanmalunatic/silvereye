# Silvereye

Silvereye is an IMU based motion capture system for the lower limbs, based on Bosch's BNO055 IMU.

## Overview

In order to capture kinematic data, the main segments of the lower limbs (seven in total) are equipped with an inertial module.
This information is then transmitted wirelessly to a PC, which processes it to perform gait analysis.

See a short demo of the system in action:
[![Silvereye: IMU motion capture for gait analysis, demo](https://img.youtube.com/vi/81BaRLLR5xU/0.jpg)](https://www.youtube.com/watch?v=81BaRLLR5xU)

## Silverapp

Silverapp was developed as a proof of concept, in order to display some capabilities of the physical Silvereye system.
However, the signals provided by the sensors should allow the extraction of several other gait parameters.
Silverapp's current release includes:
- A basic calibration procedure that aligns the coordinate systems between sensors and segments.
- A live display of the lower limb's joint angles on the sagittal plane (flexion/extension).
- A live, 3D display of the user's movements.
- Recording capabilities for both the raw and the processed signals.

## Hardware

The development version of Silvereye depends on three main components:
1. Bosch's BNO055  (Breakout board by Adafruit)
2. Microchip's ARM® Cortex®-M0+ ATSAMD21G18 (Breakout board by Adafruit)
3. Nordic Semiconductor's nRF24L01

These components are assambled into so called "inertial modules", which are attached to the lower limbs via body straps.
The schematics needed to physically build the inertial modules can be found under /PCB/. 
The modules can then be programmed with the code found in /arduino/.

## Thesis

Silvereye was initially developed as Juan Manuel Luna's bachelor thesis. 
This document (written in Spanish) is avaliable under /thesis/, and gives a detailed description of the system's workings.

## Acknowledgments

The development of this system was only possible thanks to [TMRH20's excellent library for the NRF24L01](https://github.com/nRF24/RF24). Thanks for your hard work!

Silverapp was developed in C++ using the [Qt framework](http://qt.io/).
The 3D avatar was created in [MakeHuman](http://www.makehuman.org/) and rendered via the [OGRE engine](http://www.ogre3d.org/), and the joint angles are displayed thanks to [QCustomPlot](http://qcustomplot.com/).