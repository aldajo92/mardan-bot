#include <Wire.h>

boolean A_set;
boolean B_set;

boolean flag = false;
boolean flag1 = false;

union miDato{
   int   val;
   byte  b[2];     // Array de bytes de tamaño igual al tamaño de la primera variable: int = 2 bytes, float = 4 bytes
} myEncoder;

int number = 0;

void setup()
{
  Serial.begin (9600);
  Wire.begin(3);                // join i2c bus with address #3
  Wire.onRequest(requestEvent); // register event
  Wire.onReceive(receiveData);
  
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop()
{
  digitalWrite(13, flag);
  myEncoder.val = 0;
//  Serial.print("Index:"); Serial.print(encoder0Pos, DEC); Serial.println();
  flag = !flag;
  
  delay(100);
}

void requestEvent()
{
  Wire.write(myEncoder.b,sizeof(myEncoder.val));
  digitalWrite(13, flag1);
  flag1 = !flag1;
}

// callback for received data
void receiveData(int byteCount){
  while(Wire.available()) {
    number = Wire.read();

    Serial.print("byteCount received: ");
    Serial.print(byteCount);
    
    Serial.print(" data received: ");
    Serial.println(number);
    
//    if (number == 1){
//      
//    }
  }
}
