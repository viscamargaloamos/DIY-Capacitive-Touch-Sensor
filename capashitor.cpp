//DIY Capacitive Touch Sensor
//Performance Task in General Physics 2 
//Members: Cerro, Ganade, Gueco, Mosqueda, Parnes, Plazos

// This .cpp file contains the instructions for the DIY Capacitive Touch Sensor. 

// PART A: SETTING THE CONSTANTS

const int sendPin = 9;     // This part instructs the system to set D9 as the "gateway."
const int measurePin = A0; // This part instructs the system to set A0 as the "observer." 
// Dw about the D9 not being D9, it's just Arduino conventions. lol

// Pin Configuration Logic:
// 1. GATEWAY (D9): Set as a Digital Output to act as a "pump." 
//    It forcefully pushes (HIGH) or drains (LOW) electricity into the system.
// 2. OBSERVER (A0): Set as an Analog Input to act as a "reader." 
//    Unlike digital pins that just see "On/Off," A0 reads the exact voltage 
//    levels (0-1023) so we can watch the capacitor charge in real-time (indirectly though because we 
//    still need to solve for the capacitance using the RC time constant formula (we can just do this point by point)).

// PART B: THE VOID SETUP
// - Basically, this part instructs the system how to start, hence the word SETUP. The 115200 here is the Baud rate, which refers to 
// the speed of data transmission measured in symbols per second (baud), representing how many times a signal changes 
// its state (like voltage or phase) on a communication line each second. This Baud rate is fast-perfect for real-time graphing.
// - The pinMode(sendPin, OUTPUT); basically instructs the system to drain the electricity out of the circuit. 
// In a sense, the default instructions is to drain electricity out of the circuit.

void setup() {
  Serial.begin(115200);
  pinMode(sendPin, OUTPUT);
}

// PART C: THE VOID LOOP
// Basically, this part instructs the system what to do repeatedly, which is divided into four (4) parts. 

void loop() {
  // STEP 1: DRAIN THE CIRCUIT
  // We set D9 to LOW to drain electricity out of the circuit.
  digitalWrite(sendPin, LOW);
  delay(5); // We give the system 5 ms for the circuit to be fully empty. 
  
  // STEP 2: START CHARGING
  // We set D9 to HIGH to push 5 V of electricity into the circuit.
  digitalWrite(sendPin, HIGH);

  // STEP 3: SERIAL PLOTTING
  // We take 100 snapshots very fast to draw voltage-time curve.
  for(int i = 0; i < 100; i++) {
    int val = analogRead(measurePin);
    Serial.print("Min:0,Max:1023,Voltage:");  // We print "Min" and "Max" so the Serial Plotter stays zoomed out.
    Serial.println(val); 
  }

  // STEP 4: COOL DOWN
  // We set a small pause so the graph doesn't fly off the screen too fast for 50 ms.
  delay(50); 
}

// This is what the system will do for the rest of its life. What changes here is the voltage-time graph as we touch the 
// aluminum foil + and the recording stops as we close the serial plotter.

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// INSTRUCTIONS FOR THE DATA COLLECTION

// A. SETUP
// 1. Load the code onto the microcontroller.
// 2. Open the Serial Plotter. Make sure it’s set to 115200 baud.

// B. NO TOUCH
// 3. Hands Off. Don't touch the foil yet. Let the plotter run for 3–5 seconds so the viewer sees what "Normal" looks like (the sharp, fast spikes).
// THIS WILL BE OUR DATA FOR THE NO TOUCH.

// C. WITH TOUCH
// 4. Hover First. Bring your hand slowly toward the foil but don't touch it. If the resistor is doing its job, we can see the spikes start to lean or "jitter" slightly. This shows the sensor is sensitive.
// 5. The Big Touch. Firmly press your finger to the aluminum. You want to see that "mountain" flatten out significantly on the graph.
// 6. Hold it. Keep your finger there for 2 seconds so the recording captures a steady "Touch" state.
// 7. Release. Pull your hand away quickly so the viewer sees the graph "snap" back to the sharp spikes instantly.
// THIS WILL BE OUR DATA FOR THE WITH TOUCH.

// D. RECORDING
// 8. Close the Plotter window.
// 9. Check the recording. Are the "No-Touch" peaks hitting the Max (1023)? If they aren't, your foil might be a bit loose.
// 10. Take a HQ screenshot of the "No-Touch" spike next to a "Touch" curve for comparison.

// E. TROUBLESHOOTING
// If you start recording and the graph looks like a solid block of static:
// 11. Use your other hand to touch the outer metal shell of your laptop or the Arduino's USB plug. This stabilizes your body's electrical charge and makes the graph look clean.