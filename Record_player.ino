#include <Stepper.h>

#define photoPin A5

#define stepsPerRev 2038
#define A_pin 6
#define B_pin 5
#define C_pin 4
#define D_pin 3
#define G_pin 7

/*to include: stepper motor, 7 segment display*/

int lightCal, lightVal, flag = 0;

int melody[] = {262, 262, 392, 392, 440, 440, 392, 349, 349, 330, 330, 294, 294,262,392,392,349,349,330,330,294,392,392,349,349,330,330,294, 262, 262, 392, 392, 440, 440, 392, 349, 349, 330, 330, 294, 294,262};
int count[] = {4,4,4,4,4,4,8,4,4,4,4,4,4,8,4,4,4,4,4,4,8,4,4,4,4,4,4,8,4,4,4,4,4,4,8,4,4,4,4,4,4,8};

const int duration = sizeof(melody)/sizeof(int);

Stepper stepper(stepsPerRev, 10, 11, 12, 13);

void setup() {
  // put your setup code here, to run once:

  lightCal = analogRead(photoPin);
  
  pinMode(A_pin, OUTPUT);
  pinMode(B_pin, OUTPUT);
  pinMode(C_pin, OUTPUT);
  pinMode(D_pin, OUTPUT);
  pinMode(G_pin, OUTPUT);

  pinMode(3,OUTPUT); //speaker
  
  stepper.setSpeed(4);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (checkPhotoresistor() && checkPhotoresistor() && checkPhotoresistor() && flag == 0) {
    lightUp();
    playMusic();
    flag++;
  }
}

boolean checkPhotoresistor() {
  boolean b = false;
  
  lightVal = analogRead(photoPin);

  Serial.println(lightVal);
  delay(1000);
  Serial.println(lightCal);

  if (lightVal < (lightCal - 115)) {
    b = true;
  }
  Serial.println(b);
  delay(1000);
  return b;
}

void lightUp() {
  //lights up the number 3 as the track num
  digitalWrite(A_pin, HIGH);
  digitalWrite(B_pin, HIGH);
  digitalWrite(C_pin, HIGH);
  digitalWrite(D_pin, HIGH);
  digitalWrite(G_pin, HIGH);

}

void playMusic() {
  delay(2000);
  for (int i = 0; i < duration; i++) {
    revolve();
    tone(2,melody[i], (100*count[i]));
    revolve();
    delay(250);
  }
}

void revolve() {
  //stepper.step(stepsPerRev/16);
  stepper.step(25);
}
