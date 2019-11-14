#include <Servo.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd (8, 9, 10, 11, 12, 13);

const int trigPin = 4;
const int echoPin = 5;

const int trigPin2 = 3;
const int echoPin2 = 2;

Servo myservo;
Servo myservo2;
int pos = 0;
int pos2 = 0;
int lugares = 4;
int casa = 1;

void setup() {
  lcd.begin (16, 2);

  Serial.begin(9600);
  myservo.attach(7);
  myservo2.attach(6);
}

void loop() {

  lcd.setCursor(0, 0);
  lcd.print ("Bienvenido");
  lcd.setCursor(0, 1);
  lcd.print ("Lugares:");
  lcd.setCursor(9, 1);
  lcd.print (lugares);

  // Medidas Primer Servo
  long duration, inches, cm;
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  // Medidas Segundo Servo
  long duration2, inches2, cm2;
  pinMode(trigPin2, OUTPUT);
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  pinMode(echoPin2, INPUT);
  duration2 = pulseIn(echoPin2, HIGH);
  inches2 = microsecondsToInches(duration2);
  cm2 = microsecondsToCentimeters(duration2);

  Serial.print("Primer Ultrasonico , ");
  Serial.print(inches);
  Serial.print(" pulg. , ");
  Serial.print(cm);
  Serial.print(" cm");
  Serial.println();

  Serial.print("Segundo Ultrasonico , ");
  Serial.print(inches2);
  Serial.print(" pulg. , ");
  Serial.print(cm2);
  Serial.print(" cm");
  Serial.println();

  Serial.print("Lugares libres : ");
  Serial.print(lugares);
  Serial.print(" , ");
  Serial.println();
  Serial.println("---------------------------------------------------------------------------------------------");

  if (lugares <= 0) {
    myservo.write(0);
  }
  else {
    if (cm <= 5) {
      myservo.write(90);
      delay(3000);
      lugares--;
    }

    else if (cm >= 5) {
      myservo.write(0);
    }
  }

  if (cm2 <= 5) {
    myservo2.write(90);
    delay(3000);
    lugares++;
  }

  else if (cm2 >= 5) {
    myservo2.write(0);
  }

  delay(10);
}

/////////////////////////////////////////////////////////////
long microsecondsToInches(long microseconds)
{
  return microseconds / 74 / 2;
}
long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}
