const int sendPin = 9;     
const int measurePin = A0; 

void setup() {
  // We keep it at 115200 to ensure the data is smooth
  Serial.begin(115200);
  pinMode(sendPin, OUTPUT);
}

void loop() {
  // --- PHASE 1: THE CHARGE (Watch it climb) ---
  digitalWrite(sendPin, HIGH); 
  pinMode(measurePin, INPUT); 

  // 400 points at 2ms each = ~0.8 seconds of "UP" time
  for (int i = 0; i < 400; i++) {
    int rawValue = analogRead(measurePin);
    float voltage = (rawValue * 5.0) / 1023.0;
    
    Serial.print("Limit:5.0,"); 
    Serial.print("Voltage_V:");
    Serial.println(voltage);
    
    // This is the "Brake Pedal" - slowing down the horizontal speed
    delayMicroseconds(2000); 
  }

  // --- PHASE 2: THE DISCHARGE (Watch it fall) ---
  digitalWrite(sendPin, LOW);
  pinMode(measurePin, OUTPUT);
  digitalWrite(measurePin, LOW);

  // 400 points at 2ms each = ~0.8 seconds of "DOWN" time
  for (int i = 0; i < 400; i++) {
    int rawValue = analogRead(measurePin);
    float voltage = (rawValue * 5.0) / 1023.0;
    
    Serial.print("Limit:5.0,");
    Serial.print("Voltage_V:");
    Serial.println(voltage);
    
    delayMicroseconds(2000);
  }
}