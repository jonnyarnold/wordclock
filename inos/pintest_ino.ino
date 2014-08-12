int pins[] = {
  0,
  1,
  2,
  3,
  4,
  5,
  6,
  7,
  8,
  9,
  10,
  11,
  12,
  13,
  18, // A0
  19,
  20,
  21,
  22,
  23
};
int numberOfPins = 20;
int onPin = 0;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  for(int pinIdx = 0; pinIdx < numberOfPins; pinIdx++) {
    pinMode(pins[pinIdx], OUTPUT);   
    digitalWrite(pins[pinIdx], HIGH);  
  }
}

// the loop routine runs over and over again forever:
void loop() {
}
