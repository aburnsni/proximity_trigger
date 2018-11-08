#include <MIDI.h>

const int sensors = 2;

// defines pins numbers
const int trigPin[sensors] = {7,5};
const int echoPin[sensors] = {6,4};

// notes
const int notes[sensors] = {52,59};
const int channel = 5;

// defines variables

unsigned long lasttrig[sensors];

unsigned long triggap = 1000;
unsigned long range = 1500;

long duration[sensors];
int distance[sensors];

bool DEBUG = 0;

MIDI_CREATE_DEFAULT_INSTANCE();
void setup() {
  for (int i = 0; i < sensors; i++) {
    pinMode(trigPin[i], OUTPUT); // Sets the trigPin1 as an Output
    pinMode(echoPin[i], INPUT); // Sets the echoPin1 as an Input
  }
  MIDI.begin();
  if (DEBUG) {
    Serial.begin(115200);  // needed for hairless midi
  }
  for (int i = 0; i < sensors; i++) {
    lasttrig[i] = millis();
  }
  delay(1000);
  // MIDIsoftreset();  // Midi Reset
}

void loop() {
  for (int i=0; i < sensors; i++) {
    // Clears the trigPin
    digitalWrite(trigPin[i], LOW);
    delayMicroseconds(2);

    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin[i], HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin[i], LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration[i] = pulseIn(echoPin[i], HIGH);

    // Calculating the distance
    distance[i] = duration[i] * 0.034 / 2;

    if (duration[i] < range && (millis() - lasttrig[i] > triggap)) {
      MIDI.sendNoteOn(notes[i], 100, channel);
      lasttrig[i] = millis();
    }
  }
}

void MIDIsoftreset()  // switch off ALL notes on channel 1 to 16
{
  for (int channel = 0; channel < 16; channel++)
  {
    MIDI.sendControlChange(123, 0, channel);
  }
}
