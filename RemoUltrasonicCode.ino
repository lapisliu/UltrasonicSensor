#include <Ultrasonic.h>

const int joyX = 0;
const int joyY = 1;


const int FWD_X = 682;
const int FWDLEFT_Y = 170;
const int FWDRIGHT_Y = 852;
const int MIDPNT = 1024/2;


const int trigPinRight = 2; // Ultrasonic sensor Trig pin
const int echoPinRight = 3; // Ultrasonic sensor Echo pin
const int buzzer1 = 8; // LED pin


const int trigPinFront = 4; // Ultrasonic sensor Trig pin
const int echoPinFront = 5; // Ultrasonic sensor Echo pin
const int buzzer2 = 11; // LED pin


const int trigPinLeft = 7; // Ultrasonic sensor Trig pin
const int echoPinLeft = 6; // Ultrasonic sensor Echo pin
const int buzzer3 = 12; // LED pin






void setup() {
  pinMode(trigPinRight, OUTPUT);
  pinMode(echoPinRight, INPUT);
  pinMode(buzzer1, OUTPUT);
  pinMode(trigPinFront, OUTPUT);
  pinMode(echoPinFront, INPUT);
  pinMode(buzzer2, OUTPUT);
  pinMode(trigPinLeft, OUTPUT);
  pinMode(echoPinLeft, INPUT);
  pinMode(buzzer3, OUTPUT);
  Serial.begin(9600);
}


float measure(int trigPin, int echoPin){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2;


  return distance;
}


void resetBuzzer(int buzzer){
  analogWrite(buzzer,0);
}


void loop() {
  int xValue = analogRead(joyX);
  int yValue = analogRead(joyY);


  float distanceRight = measure(trigPinRight,echoPinRight);
  float distanceFront = measure(trigPinFront,echoPinFront);
  float distanceLeft = measure(trigPinLeft,echoPinLeft);


  while(xValue<540 && xValue>480 &&
     yValue<540 && yValue>480){
       xValue = analogRead(joyX);
       yValue = analogRead(joyY);
       resetBuzzer(buzzer1);
       resetBuzzer(buzzer2);
       resetBuzzer(buzzer3);
       //the joystick is at the center. Do nothing
     }


     
  if (xValue>FWD_X && (yValue>FWDLEFT_Y && yValue<=FWDRIGHT_Y)){
    Serial.print("Distance Front: ");
  Serial.print(distanceFront);
  Serial.println(" cm");  
     analogWrite(buzzer2,distanceFront>200?0:200-distanceFront);
  }else{
    resetBuzzer(buzzer2);
  }
 
  if(xValue<=FWD_X && yValue<=MIDPNT){  
      Serial.print("Distance Left: ");
      Serial.print(distanceLeft);
      Serial.println(" cm");
        analogWrite(buzzer3,distanceLeft>200?0:200-distanceLeft);    


   distanceLeft = measure(trigPinLeft,echoPinLeft);


        xValue = analogRead(joyX);
       yValue = analogRead(joyY);
    }else{
      resetBuzzer(buzzer3);
    }
   
  if(xValue<=FWD_X && yValue>MIDPNT){
      Serial.print("Distance Right: ");
      Serial.print(distanceRight);
      Serial.println(" cm");
      analogWrite(buzzer1,distanceRight>200?0:200-distanceRight);

      distanceRight = measure(trigPinRight,echoPinRight);

      xValue = analogRead(joyX);
       yValue = analogRead(joyY);    
    }else{
resetBuzzer(buzzer1);
    }


  Serial.print("X:");
  Serial.println(analogRead(joyX));
  Serial.print("\t");
  Serial.print("Y:");
  Serial.println(analogRead(joyY));
 
  delay(100);
}
