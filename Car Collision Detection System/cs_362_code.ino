#include <LiquidCrystal.h>
#include <Servo.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int green_led = 6; 
int yellow_led = 7;
int red_led = 8;

Servo servo;

int buzzer = 13;

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
  Serial.begin(9600);
  servo.attach(A0);
}

void loop() {
  lcd.clear();
  lcd.setCursor(0,0);
  digitalWrite(trig , HIGH);
  digitalWrite(trig , LOW);

  duration = pulseIn(echo , HIGH);
  distance = (duration/2) / 28.5 ;

  if( distance < 0){
    Serial.print("d");
    delay(300);
    for(int i=0;i<5;i++)
    {
      tone(buzzer, 1100);
      delay(500);
      tone(buzzer, LOW, 500);
      delay(150);
    }
    exit(0);
    // the system has to be restarted manually by the car mechanic in case of an accident.
  }
    
  if ( distance <= 7 )
  {
    digitalWrite(red_led, HIGH);
    lcd.setCursor(0,1);
    lcd.print("WARNING");
  }
  else {
    digitalWrite(red_led, LOW);
  }

  
  if ( distance <= 15 )
  {
    digitalWrite(yellow_led, HIGH);    
    lcd.setCursor(0,1);
    lcd.print("KEEP DISTANCE");
  }
   else
  {
    digitalWrite(yellow_led, LOW);
  }
  
  if ( distance <= 25 )
  {
    digitalWrite(green_led, HIGH);
    lcd.setCursor(0,1);
    lcd.print("SAFE");
  }
  else
  {
    digitalWrite(green_led, LOW);
    Serial.print("n");
    delay(300);
  }
  lcd.setCursor(0,0);
  lcd.print("Distance: ");
  lcd.print(distance);
  

  servo.write(0);
  delay(500);
  servo.write(90);
  delay(500);
  servo.write(180);
  delay(500);
  servo.write(90);
  delay(500);
  servo.write(0);
  delay(500);
}
