#include <Servo.h>
#define servoPin 10
#define buttonPin 11

using namespace std;

Servo servo;

/*This class represents the ultrasonic sensors that are going to be used for the bookshelf rotation. For the sake of the bookshelf rotation, we will be using the constructor with
3 parameters. As you can see, int d is the 3rd parameter in the constructor, which is gonna affect the threshold of the ultrasonic sensor and how far the books should be placed to trigger the servo motor to 
rotate. */
class BookSense {
  public:
    boolean bookCheck(int distance);
    BookSense(int echo, int trig);
    BookSense(int echo, int trig, int d);
    int getDistance();
    int distCheck; /*the actual variable of the distance threshold that int d will be set equal to in the constructor*/
    
  private:
    int echo_pin;
    int trig_pin;
};

   BookSense b1 (2,3,5);
   BookSense b2 (4,5,2);

void setup() {
   // put your setup code here, to run once:
    
   servo.attach(servoPin);
   pinMode(buttonPin, INPUT);

   Serial.begin(9600); 

}

void loop() {
  Serial.print("Distance 1: ");
  Serial.print(b1.getDistance());

  Serial.print("\nDistance 2: ");
  Serial.print(b2.getDistance());
  

  shelfReset();
  
  if (b1.bookCheck(b1.getDistance())&& b2.bookCheck(b2.getDistance())) {
    
    shelfOpen();

    /*while (digitalRead(buttonPin) == HIGH) {
      //do nothing
    }*/

    delay(5000);
  }
}

int BookSense::getDistance() {
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);

  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);
  int duration = pulseIn(echo_pin, HIGH);
  
  return (duration*.0343)/2; 
}

BookSense::BookSense(int echo, int trig) {
      echo_pin = echo;
      trig_pin = trig;
      
      pinMode(trig_pin, OUTPUT);
      pinMode(echo_pin, INPUT);
}

BookSense::BookSense(int echo, int trig, int d) {
      echo_pin = echo;
      trig_pin = trig;
      distCheck = d;
      
      pinMode(trig_pin, OUTPUT);
      pinMode(echo_pin, INPUT);
}

boolean BookSense::bookCheck(int distance) {
  if (distance == distCheck) {
    return true;
  }
  return false;
}

void shelfOpen() {
  servo.write(179);
  delay(1000);
}

void shelfReset() {
  servo.write(0);
  delay(1000);
}
