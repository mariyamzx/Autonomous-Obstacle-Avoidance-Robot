#include <Servo.h>

const int trigPin = 3;
const int echoPin = 6;

Servo myServo;

// L298N Pins
const int T4 = 8;
const int T3 = 9;
const int T2 = 10;
const int T1 = 11;

// ----------------------
// Distance Function
// ----------------------
float getDistance() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);

  if (duration == 0) {
    return 999;   // No echo received
  }

  return duration * 0.0343 / 2;
}

// ----------------------
// Motor Functions
// ----------------------
void stopCar() {
  digitalWrite(T1, LOW);
  digitalWrite(T2, LOW);
  digitalWrite(T3, LOW);
  digitalWrite(T4, LOW);
}

void forward() {
  digitalWrite(T1, LOW);
  digitalWrite(T2, HIGH);

  digitalWrite(T3, LOW);
  digitalWrite(T4, HIGH);
}

void backward() {
  digitalWrite(T1, HIGH);
  digitalWrite(T2, LOW);

  digitalWrite(T3, HIGH);
  digitalWrite(T4, LOW);
}

void turnRight() {
  digitalWrite(T1, LOW);
  digitalWrite(T2, LOW);

  digitalWrite(T3, HIGH);
  digitalWrite(T4, LOW);
}

void turnLeft() {
  digitalWrite(T1, HIGH);
  digitalWrite(T2, LOW);

  digitalWrite(T3, LOW);
  digitalWrite(T4, LOW);
}

// ----------------------
// Setup
// ----------------------
void setup() {

  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(T1, OUTPUT);
  pinMode(T2, OUTPUT);
  pinMode(T3, OUTPUT);
  pinMode(T4, OUTPUT);

  myServo.attach(7);
  myServo.write(90);

  delay(1000);
}

// ----------------------
// Main Loop
// ----------------------
void loop() {

  float frontDistance = getDistance();

  Serial.print("Front: ");
  Serial.println(frontDistance);

  if (frontDistance < 20) {

    stopCar();
    delay(300);

    // Move back slightly
    backward();
    delay(400);

    stopCar();
    delay(300);

    // Look Left
    myServo.write(180);
    delay(1000);

    float leftDistance = getDistance();

    // Look Right
    myServo.write(0);
    delay(1000);

    float rightDistance = getDistance();

    // Return Center
    myServo.write(90);
    delay(500);

    Serial.print("Left: ");
    Serial.println(leftDistance);

    Serial.print("Right: ");
    Serial.println(rightDistance);

    if (leftDistance > rightDistance) {

      Serial.println("Turning Left");

      turnRight();
      delay(500);
    } else {
      Serial.println("Turning Right");
      turnLeft();
      delay(500);
    }
    stopCar();
    delay(300);
  } else { forward(); }
  
  delay(100);
}