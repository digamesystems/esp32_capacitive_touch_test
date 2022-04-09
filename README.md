# CapacitiveTouchTest

Playing with the capacitive touch inputs on the ESP32
 
 Based on the Espressif ESP32 TouchRead example code. Adding in de-glitching 
 and smoothing of the reported values and dynamic baseling tracking.

 Touch0 is T0 which is on GPIO 4.

 J. Price, 2022. -- Based on the Espressif ESP32 TouchRead example code.

 The touchRead function in the ESP Arduino API seems to be susceptible to 
 noise. A number of people have reported 'glitching' in the signal. (Sharp,
 single-point spikes in the data.) This code adds a simple de-glitching 
 feature and provides the option to smooth the data to reduce noise. 

 Feel free to play with the smoothing constants to fit your application. 
