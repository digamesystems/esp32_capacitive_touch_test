# CapacitiveTouchTest

Playing with the capacitive touch inputs on the ESP32. 
-- Based on the Espressif ESP32 TouchRead example code. 

Adding in de-glitching and digital filtering of the reported values and dynamic baseling tracking.

In this example I use Touch0 ('T0' in the code) which mapped to GPIO 4.

Keywords: ESP32, touchRead, capacitive touch sensor, de-glitch

## Background

The capacitive touch features of the ESP32 seem like a very cool way for users to interact with devices without needing mechanical switches. 

However, the touchRead function in the ESP Arduino API seems to be susceptible to 
noise. A number of people have reported 'glitching' in the signal. (Sharp,
single-point spikes in the data.) 

As an experiment to test this, I connected a piece of copper tape to one of the capacitive touch inputs on` my module and started with the TouchRead example from Espressif. I saw much the same thing. That said, the magnitude of the glitching behavior is quite dependent upon the geometry of the copper tape pad. (I suspect that a bit of hardware filtering might eliminate much of the issue.) 

To solve this in software, I added a simple de-glitching feature and provided the option to smooth the data to reduce noise. 

Noise is filtered using a simple exponential smoothing function where the contribution of a new data point to the current value is determined by a numerical factor ranging from 0 to 1.0. The closer the numerical factor is to 1.0, the less a given point contributes. 

## Hardware Set Up

![Setup using an ESP32 breakout board](/doc/setup.jpg)

## Results

Curves obtained from the SerialPlotter in the Arduino IDE. (Offset for clarity)

1. Red Trace: Raw data from touchRead function
2. Green Trace: Data after de-glitching
3. Blue Trace: Data after smoothing

Touching the copper results in the excursion in the data. 


![Results](/doc/results.jpg)


Feel free to adapt / use as you will. 

Regards, 

John.
