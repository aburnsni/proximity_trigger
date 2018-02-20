/*
  Ultrasonic Sensor HC-SR04 and Arduino Tutorial

  Crated by Dejan Nedelkovski,
  www.HowToMechatronics.com

*/

// defines pins numbers
const int trigPin1 = 7;
const int echoPin1 = 6;
const int trigPin2 = 5;
const int echoPin2 = 4;
// defines variables

unsigned long lasttrig1 = millis();
unsigned long lasttrig2 = millis();
unsigned long triggap = 1000;

bool trig1 = 0;
bool trig2 = 0;

long duration1;
int distance1;
long duration2;
int distance2;

void setup() {
  pinMode(trigPin1, OUTPUT); // Sets the trigPin1 as an Output
  pinMode(echoPin1, INPUT); // Sets the echoPin1 as an Input
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  Serial.begin(9600); // Starts the serial communication
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

  if (duration1 < 5000 && (millis() - lasttrig1 > triggap)) {
   trig1 = 1;
    lasttrig1 = millis();
  }
  if (duration2 < 5000 && (millis() - lasttrig2 > triggap)) {
trig2 = 1;
    lasttrig2 = millis();
  }
  // Prints the distance1 on the Serial Monitor
  Serial.print(trig1);
  Serial.print(" ");
  Serial.println(trig2);
  trig1 = 0;
  trig2 = 0;
}
