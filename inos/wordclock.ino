// WORDCLOCK.INO
// Use the Arduino as a word clock.

// CONFIGURATION

// currentHourPinIndex keeps track of which hour pin (as defined in hourPins) is lit
// 0 = "one", 1 = "two", etc.
int currentHourPinIndex = 8;

// currentMinutePinsIndex does a similar job to currentHourPinsIndex.
// 0 = "o'clock", 1 = "five past", ... , 
// 5 = "twenty five past", 6 = "half past", 7 = "twenty five to", etc.
int currentMinuteSequenceIndex = 1;

// CONSTANTS

// This constant is used as a 'null';
// The code will ignore this value when it is found
int pinNoPin = -1;

// Pin numbers (specific to each Arduino)
int pinMinFive = 5;
int pinMinTen = 1;
int pinMinQuarter = 7;
int pinMinTwenty = 3;
int pinMinHalf = 8;
int pinMinOClock = 13;

int pinPast = 9;
int pinTo = 2;

int pinHourOne = 10;
int pinHourTwo = 4;
int pinHourThree = 11;
int pinHourFour = 21;
int pinHourFive = 23;
int pinHourSix = 22;
int pinHourSeven = 19;
int pinHourEight = 20;
int pinHourNine = 0;
int pinHourTen = 18;
int pinHourEleven = 6;
int pinHourTwelve = 12;

// All pins (used to clear clock face)
int allPins[] = {pinMinFive,
pinMinTen,
pinMinQuarter,
pinMinTwenty,
pinMinHalf,
pinMinOClock,
pinPast,
pinTo,
pinHourOne,
pinHourTwo,
pinHourThree,
pinHourFour,
pinHourFive,
pinHourSix,
pinHourSeven,
pinHourEight,
pinHourNine,
pinHourTen,
pinHourEleven,
pinHourTwelve};
int numberOfPins = 20;

// The hour pins array gives the order that the pins need to be lit up.
// (Length: 12)
int hourPins[] = {
  pinHourOne,
  pinHourTwo,
  pinHourThree,
  pinHourFour,
  pinHourFive,
  pinHourSix,
  pinHourSeven,
  pinHourEight,
  pinHourNine,
  pinHourTen,
  pinHourEleven,
  pinHourTwelve
};
int numberOfHourPins = 12;

// Minute pins are more tricky. The following array shows the sequence of minute pins
// to light up. pinNoPin is used to fill out the arrays, and should be ignored when
// looping over them.
int minuteSequence[][3] = {
  { pinMinOClock, pinNoPin, pinNoPin },
  { pinMinFive, pinPast, pinNoPin },
  { pinMinTen, pinPast, pinNoPin },
  { pinMinQuarter, pinPast, pinNoPin },
  { pinMinTwenty, pinPast, pinNoPin },
  { pinMinTwenty, pinMinFive, pinPast },
  { pinMinHalf, pinPast, pinNoPin },
  { pinMinTwenty, pinMinFive, pinTo },
  { pinMinTwenty, pinTo, pinNoPin },
  { pinMinQuarter, pinTo, pinNoPin },
  { pinMinTen, pinTo, pinNoPin },
  { pinMinFive, pinTo, pinNoPin }
};
int numberOfMinuteSequences = 12;

// Change the hour when the minute hits the following index
int hourChangeIndex = 7;

void setup() {
  // Setup all pins as output
  for(int i = 0; i < numberOfPins; i++) {
    pinMode(allPins[i], OUTPUT);
  }
  
  turnOn(minuteSequence[currentMinuteSequenceIndex]);
  turnOn(hourPins[currentHourPinIndex]);
}

void loop() {
  // Wait 5 minutes = 300000 ms
  delay(300000);
  
  // Move the minutes onto the next step
  turnOff(minuteSequence[currentMinuteSequenceIndex]);
  currentMinuteSequenceIndex++;
  
  // If we hit the end of the minutePins array, add one to the hour index
  if(currentMinuteSequenceIndex >= numberOfMinuteSequences) {
    currentMinuteSequenceIndex = 0;
  }
  
  turnOn(minuteSequence[currentMinuteSequenceIndex]);
  
  // Check for hour change
  if(currentMinuteSequenceIndex == hourChangeIndex) {
    turnOff(hourPins[currentHourPinIndex]);
    currentHourPinIndex++;
    
    // If we hit the end of the hourPins array, go back to 0
    if(currentHourPinIndex >= numberOfHourPins) {
      currentHourPinIndex = 0;    
    }
    turnOn(hourPins[currentHourPinIndex]);
  }
}

void turnOn(int pins[]) {
  int arrayLength = 3; // Assumed
  for(int i = 0; i < arrayLength; i++) {
    turnOn(pins[i]);
  }
}

void turnOn(int pin) {
  digitalWrite(pin, HIGH);
}

void turnOff(int pins[]) {
  int arrayLength = 3; // Assumed
  for(int i = 0; i < arrayLength; i++) {
    turnOff(pins[i]);
  }
}

void turnOff(int pin) {
  digitalWrite(pin, LOW);
}
