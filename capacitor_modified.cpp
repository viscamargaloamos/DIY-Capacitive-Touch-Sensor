const int sendPin = 9;     
const int measurePin = A0; 

void setup() {
  Serial.begin(115200);
  pinMode(sendPin, OUTPUT);
  
  Serial.println("Voltage_V,Charge_Percentage,Threshold_50pct");
}

void loop() {
  pinMode(sendPin, OUTPUT);
  digitalWrite(sendPin, LOW);
  delay(5); 
  
  digitalWrite(sendPin, HIGH);

  for(int i = 0; i < 100; i++) {
    int rawValue = analogRead(measurePin);
    
    float voltage = (rawValue * 5.0) / 1023.0;
    
    float chargePercent = (rawValue / 1023.0) * 100.0;

    Serial.print("Voltage(V):");
    Serial.print(voltage);
    Serial.print(",");
    Serial.print("Charge(%):");
    Serial.print(chargePercent);
    Serial.print(",");
    Serial.println("MidPoint:50"); // Fixed reference line at 50% charge
  }

 
  digitalWrite(sendPin, LOW);
  delay(100); 