#include <SoftwareSerial.h>

#include <SoftwareSerial.h>

#include<SoftwareSerial.h>
#include<Servo.h>
#include<Wire.h>
#include<LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
SoftwareSerial BTserial(10, 11);
// Define LCD display
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define parking slots and IR sensors
int Slot = 4; // Total number of parking slots
int flag1 = 0;
int flag2 = 0;
String a="Empty";
String b="Empty";
String c="Empty";
String d="Empty";
Servo myservo1; // create servo object to control a servo (entrance gate)
Servo myservo2; // create servo object to control a servo (exit gate)


int parking1_slot3_ir_s = 6;

int parking2_slot1_ir_s = 7;
int parking2_slot2_ir_s = 8;
int parking2_slot3_ir_s = 9;

int entrance_gate = 5;
int exit_gate = 12;

int pos1 = 90; // variable to store the servo position (entrance gate)
int pos2 = 90; // variable to store the servo position (exit gate)

String sensor3;
String sensor4;
String sensor5;
String sensor6;

String cdata = ""; // complete data, consisting of sensors values*/

void setup() {
 // Serial.begin(9600);

  BTserial.begin(9600);
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("     ARDUINO    ");
  lcd.setCursor(0, 1);
  lcd.print(" PARKING SYSTEM ");
  delay(2000);
  lcd.clear();

  pinMode(parking1_slot3_ir_s, INPUT);
  pinMode(parking2_slot1_ir_s, INPUT);
  pinMode(parking2_slot2_ir_s, INPUT);
  pinMode(parking2_slot3_ir_s, INPUT);
  pinMode(entrance_gate, INPUT);
  pinMode(exit_gate, INPUT);

  myservo1.attach(13); // attaches the servo on pin 13 to the servo object
  myservo2.attach(3); // attaches the servo on pin 3 to the servo object
   myservo2.write(0);
    myservo1.write(0);
  BTserial.print(a);  
  BTserial.print(",");  
  BTserial.print(b);  
  BTserial.print(",");  
  BTserial.print(c);  
  BTserial.print(",");  
  BTserial.print(d);  
  BTserial.print(";");
  delay(20);
}

void loop() {


  p1slot3();
  p2slot1();
  p2slot2();
  p2slot3();

  gates();
  
  digitalWrite(parking1_slot3_ir_s, HIGH);
  digitalWrite(parking2_slot1_ir_s, HIGH);
  digitalWrite(parking2_slot2_ir_s, HIGH);
  digitalWrite(parking2_slot3_ir_s, HIGH);
  digitalWrite(entrance_gate, HIGH);
  digitalWrite(exit_gate, HIGH);

  lcdprint();
}

void p1slot3() {
  if (digitalRead(parking1_slot3_ir_s) == LOW) {
    sensor3 = "255";
    
    delay(200);
    a="Full";

  BTserial.print(a);  
  BTserial.print(",");  
  BTserial.print(b);  
  BTserial.print(",");  
  BTserial.print(c);  
  BTserial.print(",");  
  BTserial.print(d);  
  BTserial.print(";");
  delay(20);

  }
  if (digitalRead(parking1_slot3_ir_s) == HIGH) {
    sensor3 = "0";
  a="Empty";
    delay(200);
 
  BTserial.print(a);  
  BTserial.print(",");  
  BTserial.print(b);  
  BTserial.print(",");  
  BTserial.print(c);  
  BTserial.print(",");  
  BTserial.print(d);  
  BTserial.print(";");
  delay(20);
  }
}

void p2slot1() {
  if (digitalRead(parking2_slot1_ir_s) == LOW) {
    sensor4 = "255";
    delay(200);
    b="Full";

  BTserial.print(a);  
  BTserial.print(",");  
  BTserial.print(b);  
  BTserial.print(",");  
  BTserial.print(c);  
  BTserial.print(",");  
  BTserial.print(d);  
  BTserial.print(";");
  delay(20);
  }
  if (digitalRead(parking2_slot1_ir_s) == HIGH) {
    sensor4 = "0";
    delay(200);
    b="Empty";
 
  BTserial.print(a);  
  BTserial.print(",");  
  BTserial.print(b);  
  BTserial.print(",");  
  BTserial.print(c);  
  BTserial.print(",");  
  BTserial.print(d);  
  BTserial.print(";");
  delay(20);
  }
}

void p2slot2() {
  if (digitalRead(parking2_slot2_ir_s) == LOW) {
    sensor5 = "255";
    delay(200);
    c="Full";
  
  BTserial.print(a);  
  BTserial.print(",");  
  BTserial.print(b);  
  BTserial.print(",");  
  BTserial.print(c);  
  BTserial.print(",");  
  BTserial.print(d);  
  BTserial.print(";");
  delay(20);
  }
  if (digitalRead(parking2_slot2_ir_s) == HIGH) {
    sensor5 = "0";
    delay(200);
    c="Empty";
   
  BTserial.print(a);  
  BTserial.print(",");  
  BTserial.print(b);  
  BTserial.print(",");  
  BTserial.print(c);  
  BTserial.print(",");  
  BTserial.print(d);  
  BTserial.print(";");
  delay(20);
  }
}

void p2slot3() {
  if (digitalRead(parking2_slot3_ir_s) == LOW) {
    sensor6 = "255";
    delay(200);
    d="Full";
 
  BTserial.print(a);  
  BTserial.print(",");  
  BTserial.print(b);  
  BTserial.print(",");  
  BTserial.print(c);  
  BTserial.print(",");  
  BTserial.print(d);  
  BTserial.print(";");
  delay(20);
  }
  if (digitalRead(parking2_slot3_ir_s) == HIGH) {
    sensor6 = "0";
    delay(200);
    d="Empty";
 
  BTserial.print(a);  
  BTserial.print(",");  
  BTserial.print(b);  
  BTserial.print(",");  
  BTserial.print(c);  
  BTserial.print(",");  
  BTserial.print(d);  
  BTserial.print(";");
  delay(20);
  }
}

void gates() {
  if (digitalRead(exit_gate) == LOW) {
    for (pos2 = 0; pos2 <= 90; pos2 +=1) { 
      myservo2.write(pos2);
      delay(15);
    }
    delay(2000);
    for (pos2 = 90; pos2 >= 0; pos2 -=1) {
      myservo2.write(pos2);
      delay(15);
    }
    if (Slot < 4) {
      Slot++;
    }
  }

  if (digitalRead(entrance_gate) == LOW && (digitalRead(parking1_slot3_ir_s) == HIGH || digitalRead(parking2_slot1_ir_s) == HIGH || digitalRead(parking2_slot2_ir_s) == HIGH || digitalRead(parking2_slot3_ir_s) == HIGH)) {
    if (Slot > 0) {
      for (pos1 = 0; pos1 <= 90; pos1 +=1) {
        myservo1.write(pos1);
        delay(15);
      }
      delay(2000);
      for (pos1 = 90; pos1 >= 0; pos1 -=1) {
        myservo1.write(pos1);
        delay(15);
      }
      Slot--;
      if(Slot==0){
        lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("    SORRY :(    ");
      lcd.setCursor(0, 1);
      lcd.print("  Parking Full  ");
      delay(3000);
      lcd.clear();}
    } else {
      if(Slot==0){
      lcd.print("    SORRY :(    ");
      lcd.setCursor(0, 1);
      lcd.print("  Parking Full  ");
      delay(3000);
      lcd.clear();}
    }
  }
}

void lcdprint() {
  lcd.setCursor(0, 0);
  lcd.print("    WELCOME!    ");
  lcd.setCursor(0, 1);
  lcd.print("Slot Left: ");
  lcd.print(Slot);
  lcd.print("   ");
}

