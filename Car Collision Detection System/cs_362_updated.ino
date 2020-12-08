#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int green_led = 6; 
int yellow_led = 7;
int red_led = 8;

// ultrasonic sensor
const int trig = 9;
const int echo = 10;

// for keeping track of the distance
int duration = 0;
int distance = 0;

void setup() {
  lcd.begin(16,2);
  pinMode(green_led, OUTPUT);
  pinMode(yellow_led, OUTPUT);
  pinMode(red_led, OUTPUT);

  pinMode(trig , OUTPUT);
  pinMode(echo , INPUT);
 
}

void loop() {
  lcd.clear();
  lcd.setCursor(0,0);
  digitalWrite(trig , HIGH);
  digitalWrite(trig , LOW);


  duration = pulseIn(echo , HIGH);
  distance = (duration/2) / 28.5 ;
  Serial.println(distance);

  if ( distance <= 5 )
  {
      digitalWrite(red_led, HIGH);
      lcd.setCursor(0,0);
      lcd.print(distance);
  }
  else
  {
    digitalWrite(red_led, LOW);
  }
  if ( distance <= 7 )
  {
    lcd.setCursor(0,0);
    lcd.print(distance);
  }
  if ( distance <= 10 )
  {
    lcd.setCursor(0,0);
    lcd.print(distance);
    digitalWrite(yellow_led, HIGH);
  }
   else
  {
    digitalWrite(yellow_led, LOW);
  }
  if ( distance <= 15 )
  {    
    lcd.setCursor(0,0);
    lcd.print(distance);
  }
 
  if ( distance <= 17 )
  {
    lcd.setCursor(0,0);
    lcd.print(distance);
  }
  if ( distance <= 20 )
  {
    lcd.setCursor(0,0);
    lcd.print(distance);
  }
  if ( distance <= 25 )
  {
    lcd.setCursor(0,0);
    lcd.print(distance);
    digitalWrite(green_led, HIGH);
  }
  else
  {
    digitalWrite(green_led, LOW);
  }
  delay(300);
}
