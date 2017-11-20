#include <Wire.h>
#include <ZumoMotors.h>

#define ID 3 

int number = 0;

ZumoMotors motors;

union miDato{
   int   val;
   byte  b[2];
} motorR, motorL;

void moveR(int speed){
  motors.setLeftSpeed(speed);
  motors.setRightSpeed(speed);
}

void moveR(int speedR, int speedL){
  motors.setRightSpeed(speedR);
  motors.setLeftSpeed(speedL);
}

void setup(){
  Serial.begin (9600);
  Wire.begin(ID);                // join i2c bus with address #3
  Wire.onReceive(receiveData);
  
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop(){
  moveR(motorR.val, motorL.val);
}

// callback for received data
void receiveData(int byteCount){

    Serial.print("byte count: ");
    Serial.println(byteCount);
  
  while(Wire.available()) {
    number = Wire.read();
    motorR.b[1] = Wire.read();
    motorR.b[0] = Wire.read();
    motorL.b[1] = Wire.read();
    motorL.b[0] = Wire.read();
    
    Serial.print(" data received: ");
    Serial.print(number);

    Serial.print(" data received R: ");
    Serial.print(motorR.val);

    Serial.print(" data received L: ");
    Serial.println(motorL.val);
    
//    if (number == 1){
//      
//    }
  }
}
