#include <CapacitiveSensor.h> 

CapacitiveSensor Sensor = CapacitiveSensor(4, 7); 

long val; 
int pos = 0; 
float thresholdTime = 0; 
#define led 13 

void setup() {
  Serial.begin(9600); 
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
  
  thresholdTime = (sum / 50.0) + 100.0; 

  Serial.print("Calibration Complete. Threshold set to: ");
  Serial.print(thresholdTime);
  Serial.println(" us");
  Serial.println("Open Serial Plotter (Ctrl+Shift+L) now.");
}

void loop() {

  long startTime = micros();
  val = Sensor.capacitiveSensor(30); // Raw counts for LED logic
  long stopTime = micros();

  float timeInMicros = (stopTime - startTime) / 30.0;

  Serial.print("Measured_RC_Time_us:"); 
  Serial.print(timeInMicros);
  Serial.print(","); 
  Serial.print("Target_Threshold:");
  Serial.println(thresholdTime);

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
