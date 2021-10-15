// include the library code:
#include <string.h>
#include <stdio.h>
#include <LiquidCrystal.h>
#include <IRremote.h>

#define dotDelay 200
#define dashDelay dotDelay * 3
#define ledPin 9
#define buzzerPin 10
#define buttonA 8
#define RECEIVER_PIN 13

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//this string array contains the morse code alphabet
//each index represents the alphabetical order - 1
const char* code[]={
// A to I
".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",
// J to R 
".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",
// S to Z
"...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.." 
};

//this is the message that will be signaled in morse code
//can be modified to fit the desired clue
char message[20] = {'c', 'l', 'o', 'c', 'k', '\0'};

void setup() {
  //light and buzzer
  pinMode(ledPin, OUTPUT);
  pinMode(buttonA, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.

  Serial.begin(9600);
  IrReceiver.begin(RECEIVER_PIN, ENABLE_LED_FEEDBACK);
}

void loop() {
  
  while(digitalRead(buttonA) == HIGH) {
    //do nothing
  }
  
  for (int i = 0; i < strlen(message); i++) {
      //calls the method for which the argument is the morse code string associated with the index of the 
      //letter - 1
      lightUp(code[message[i] - 'a']);
  }
  
  int p = 0;
  p += passwordInput() * 1000;
  p += passwordInput() * 100;
  p += passwordInput() * 10;
  p += passwordInput();

  passwordChecker(p);
}

int buttonCheck () {

  int i;  
  switch (IrReceiver.decodedIRData.decodedRawData) {
    
    case (3910598400):
      Serial.println("0");
      lcd.print("0");
      i = 0;
      break;
    case (4077715200):
      Serial.println("1");
      lcd.print("1");
      i = 1;
      break;
    case (3877175040):
      Serial.println("2");
      lcd.print("2");
      i = 2;
      break;
    case (2707357440):
      Serial.println("3");
      lcd.print("3");
      i = 3;
      break;
    case (4144561920):
      Serial.println("4");
      lcd.print("4");
      i = 4;
      break;
    case (3810328320):
      Serial.println("5");
      lcd.print("5");
      i = 5;
      break;
    case (2774204160):
      Serial.println("6");
      lcd.print("6");
      i = 6;
      break;
    case (3175284480):
      Serial.println("7");
      lcd.print("7");
      i = 7;
      break;
    case (2907897600):
      Serial.println("8");
      lcd.print("8");
      i = 8;
      break;
    case (3041591040):
      Serial.println("9");
      lcd.print("9");
      i = 9;
      break;
    case (3141861120):
      Serial.println("Back");
      lcd.clear();
      lcd.setCursor(16,0);
      break;
    default:
      Serial.println("Button Not Mapped or Error Reading Button");
    
  }
  return i;
}

int passwordInput() {
  int p = 0;

  while (!IrReceiver.decode()) {
    //do nothing
  }

    //calls the method and returns whatever the user enters on the remote
    p = buttonCheck();
    delay(800);
    IrReceiver.resume();
    
  return p;
}

void passwordChecker(int p) {
  if (p == 1234) {
    lcd.print(" Next clue");
    Serial.println("Next clue");
  }
  else {
    lcd.print(" Wrong");
    Serial.println(" Wrong");
  }
  delay(5000);
  lcd.clear();
  lcd.setCursor(16, 0);
  lcd.begin(16,2);
}

//light and buzzer
void lightUp(char* sequence) {
  int i = 0;
  for (int i = 0; i < strlen(sequence); i++) {
    flash(sequence[i]);
  }
  delay(1000);
}

void flash(char dotDash) {
  digitalWrite(ledPin, HIGH);
  digitalWrite(buzzerPin, HIGH);
  
  if (dotDash == '.') {
    delay(dotDelay);
  }
  else {
    delay(dashDelay);
  }

  digitalWrite(ledPin, LOW);
  digitalWrite(buzzerPin, LOW);
  delay(100);
}
