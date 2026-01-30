//preamble
#include <CapacitiveSensor.h> //A library authored by Paul Badger

//settings
CapacitiveSensor Sensor = CapacitiveSensor(4, 7); // declares that the electricity is sent from D4 and read by D7.

//variables
long val; //stores the raw capacitive counts from the sensor
int pos = 0; //keeps track of the LED state (0 = off or 1 = on)
float thresholdTime = 0; // the calibrated trigger point in ms 
#define led 13 //onboard LED pin

//setup - the command that the nano will do at the beginning 
void setup() {
  Serial.begin(9600); // baud rate, 9600 so it's not too fast for the human eye
  pinMode(led, OUTPUT);

  Serial.println("Calibrating baseline... Do not touch!");
  
  float sum = 0;
  for (int i = 0; i < 50; i++) {
    long start = micros();
    Sensor.capacitiveSensor(30);
    long stop = micros();
    sum += (stop - start) / 30.0;
    delay(20);
  }
  
  // Set threshold: Average idle time + a 100us "Touch" buffer
  thresholdTime = (sum / 50.0) + 100.0; 

  Serial.print("Calibration Complete. Threshold set to: ");
  Serial.print(thresholdTime);
  Serial.println(" us");
  Serial.println("Open Serial Plotter (Ctrl+Shift+L) now.");
}

//loop - the commands that the nano will do forever
void loop() {
  // 1. Measure the time it takes to reach the 3.16V finish line
  long startTime = micros();
  val = Sensor.capacitiveSensor(30); // Raw counts for LED logic
  long stopTime = micros();

  // 2. Calculate average Microseconds for a single charge cycle
  float timeInMicros = (stopTime - startTime) / 30.0;

  // 3. Print values formatted for the Serial Plotter
  // First value: The actual measured RC time
  Serial.print("Measured_RC_Time_us:"); 
  Serial.print(timeInMicros);
  Serial.print(","); 
  
  // Second value: The target threshold line
  Serial.print("Target_Threshold:");
  Serial.println(thresholdTime);

  // 4. LED Toggle Logic based on the time threshold
  if (timeInMicros >= thresholdTime && pos == 0) {
    digitalWrite(led, HIGH);
    pos = 1;
    delay(500); 
  } 
  else if (timeInMicros >= thresholdTime && pos == 1) {
    digitalWrite(led, LOW);
    pos = 0;
    delay(500);
  }

  delay(10); 
}
