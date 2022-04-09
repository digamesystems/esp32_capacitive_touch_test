/*****************************************************************************
 CapacitiveTouchTest: Playing with the capacitive touch inputs on the ESP32
 
 Based on the Espressif ESP32 TouchRead example code. Adding in de-glitching 
 and smoothing of the reported values and dynamic baseling tracking.

 Touch0 is T0 which is on GPIO 4.

 J. Price, 2022. -- Based on the Espressif ESP32 TouchRead example code.

 The touchRead function in the ESP Arduino API seems to be susceptible to 
 noise. A number of people have reported 'glitching' in the signal. (Sharp,
 single-point spikes in the data.) This code adds a simple de-glitching 
 feature and provides the option to smooth the data to reduce noise. 

 Feel free to play with the smoothing constants to fit your application. 
 
*****************************************************************************/

float p1=0.0, p2=0.0, p3=0.0;  // 3-Point history
float raw = 0.0; // Current reading
float baseline = 0.0;
float smoothed = 0.0;
unsigned long count=0; 

// Smoothing factors. The closer to one (1.0) the smoother the data. Smoothing 
// introduces a delay. 
const float dataSmoothingFactor = 0.95;       
const float baselineSmoothingFactor = 0.9995;


/*****************************************************************************/
void setup()
{
  Serial.begin(115200);
  delay(1000); // give me time to bring up serial monitor
  Serial.println("Smoothed Raw De-Glitched");

  // Intialize history and smoothed value to an average of a few readings
  for (int i = 0; i<100; i++){
    raw += touchRead(T0);
    delay(10);
  }
  raw = raw /100;
  p3 = raw;
  p2 = raw;
  p1 = raw;
  smoothed = raw;
  baseline = raw;
}


/*****************************************************************************/
void loop()
{
  // Current value
  raw = touchRead(T0);
  
  p1 = raw; // Latest point in the history
  
  // Glitch detector
  if (abs(p3-p1) < 5) {   // The latest point and the two points back are pretty close 
    if (abs(p2-p3) > 3) { // The point in the middle is too different from the adjacent points -- ignore
      p2 = p3;
    }
  }

  // Smooth the de-glitched data to take out some noise
  smoothed = p3 * (1 - dataSmoothingFactor) + smoothed * dataSmoothingFactor;

  // Dynamic baseline tracking -- a much longer view of the de-glitched data
  if ( count > 50 ){ 
   baseline = p3 * (1 - baselineSmoothingFactor) + baseline * baselineSmoothingFactor;
  }

  // Shift the history
  p3 = p2;
  p2 = p1;
  
  Serial.println( String(smoothed - baseline) + "," + String(raw - baseline + 20) + "," + String(p3 - baseline + 10) );  // get value using T0

  delay(30);
}
