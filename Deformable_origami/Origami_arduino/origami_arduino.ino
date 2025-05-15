// Pin assignments for the sensors
const int flexPin1 = A0;  // First flex sensor
const int flexPin2 = A1;  // Second flex sensor
const int flexPin3 = A2;  // Third flex sensor
const int forcePin = A3;  // Force-sensitive resistor (FSR)

// Variables to store raw sensor values
int value1, value2, value3, forceValue;

/**
 * Curve mapping function (exponential curve).
 * Maps an input value from 0–1023 to a non-linear curve,
 * controlled by an exponent parameter.
 * The result is returned as an integer in the same range (0–1023).
 */
int curvedMap(int input, float exponent) {
  float norm = constrain(input, 0, 1023) / 1023.0;  // Normalize to 0.0–1.0
  float curved = pow(norm, exponent);              // Apply exponential curve
  return int(curved * 1023);                       // Rescale back to 0–1023
}

void setup() {
  Serial.begin(115200); // Initialize serial communication at 115200 baud
}

void loop() {
  // Read raw analog values from each sensor
  value1 = analogRead(flexPin1);
  value2 = analogRead(flexPin2);
  value3 = analogRead(flexPin3);
  forceValue = analogRead(forcePin);

  // Apply exponential curve mapping
  int mapped1 = curvedMap(value1, 2.5);     // Adjust exponent to shape the response curve
  int mapped2 = curvedMap(value2, 2.5);
  int mapped3 = curvedMap(value3, 2.5);
  int mappedForce = curvedMap(forceValue, 2.0);

  // Send mapped values over Serial as space-separated integers
  // Format: "<val1> <val2> <val3> <force>\n"
  // This format is compatible with Max/MSP 'unpack' or similar objects
  Serial.print(mapped1); Serial.print(" ");
  Serial.print(mapped2); Serial.print(" ");
  Serial.print(mapped3); Serial.print(" ");
  Serial.println(mappedForce); // End the line with newline character

  delay(100); // Wait 100 milliseconds before the next reading
}
