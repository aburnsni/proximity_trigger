#include <Arduino.h>
#include <MIDI.h>

const int sensors = 4;

// defines pins numbers
const int trigPin[sensors] = {2, 4, 6, 8};
const int echoPin[sensors] = {3, 5, 7, 9};
bool playing[sensors];

// notes
const int notes[sensors] = {52, 54, 56, 59};
const int channel = 5;

// defines variables

unsigned long lasttrig[sensors];

unsigned long triggap = 1000;
unsigned long range = 1500;
unsigned long maxduration = 12000;

unsigned long duration[sensors];
int distance[sensors];

bool DEBUG = 0;

MIDI_CREATE_DEFAULT_INSTANCE();

// void MIDIsoftreset();

void setup() {
  for (int i = 0; i < sensors; i++) {
    pinMode(trigPin[i], OUTPUT); // Sets the trigPin1 as an Output
    pinMode(echoPin[i], INPUT); // Sets the echoPin1 as an Input
    playing[i] = false;
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
  for (int i = 0; i < sensors; i++) {
    // Clears the trigPin
    digitalWrite(trigPin[i], LOW);
    delayMicroseconds(2);

    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin[i], HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin[i], LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration[i] = pulseIn(echoPin[i], HIGH);
    if (duration[i] > maxduration) {
      duration[i] = maxduration;
    }
    // Calculating the distance
    distance[i] = duration[i] * 0.034 / 2;


    if (DEBUG && (millis() - lasttrig[i] > 10)) {
      Serial.print(duration[0]);
      Serial.print("\t");
      Serial.println(duration[1]);
      lasttrig[i] = millis();
    } else {
      if ((duration[i] > 100) && (duration[i] < range) && (playing[i] == false) && (millis() - lasttrig[i] > triggap)) {
        MIDI.sendNoteOn(notes[i], 100, channel);
        playing[i] = true;
        lasttrig[i] = millis();
      }
      if ((duration[i] > range)) {
        MIDI.sendNoteOff(notes[i],100,channel);
        playing[i] = false;
      }
    }
  }
}

// void MIDIsoftreset()  // switch off ALL notes on channel 1 to 16
// {
//   for (int channel = 0; channel < 16; channel++)
//   {
//     MIDI.sendControlChange(123, 0, channel);
//   }
// }
