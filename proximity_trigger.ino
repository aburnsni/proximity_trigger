#include <MIDI.h>

// defines pins numbers
const int trigPin1 = 7;
const int echoPin1 = 6;
const int trigPin2 = 5;
const int echoPin2 = 4;
// defines variables

unsigned long lasttrig1 = millis();
unsigned long lasttrig2 = millis();
unsigned long triggap = 1000;
unsigned long range = 1500;

long duration1;
int distance1;
long duration2;
int distance2;

bool DEBUG = 0;

MIDI_CREATE_DEFAULT_INSTANCE();
void setup() {
  pinMode(trigPin1, OUTPUT); // Sets the trigPin1 as an Output
  pinMode(echoPin1, INPUT); // Sets the echoPin1 as an Input
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  MIDI.begin();
  if (DEBUG) {
    Serial.begin(115200);  // needed for hairless midi
  }
    delay(1000);
  MIDIsoftreset();  // Midi Reset
}

void loop() {
  // Clears the trigPin1
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);

  // Sets the trigPin1 on HIGH state for 10 micro seconds
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

  // Reads the echoPin1, returns the sound wave travel time in microseconds
  duration1 = pulseIn(echoPin1, HIGH);

  // Repeat for sensor 2
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);

  // Calculating the distance1
  distance1 = duration1 * 0.034 / 2;
  distance2 = duration2 * 0.034 / 2;

  if (duration1 < range && (millis() - lasttrig1 > triggap)) {
    MIDI.sendNoteOn(60, 100, 6);
    lasttrig1 = millis();
  }
  if (duration2 < range && (millis() - lasttrig2 > triggap)) {
    MIDI.sendNoteOn(61, 100, 6);
    lasttrig2 = millis();
  }

}

void MIDIsoftreset()  // switch off ALL notes on channel 1 to 16
{
  for (int channel = 0; channel < 16; channel++)
  {
    MIDI.sendControlChange(123, 0, channel);
  }
}
