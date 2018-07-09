#include <Servo.h>
int servoPin = 6;
int PEN_DOWN = 0; 
int PEN_UP = 90;  
Servo penServo;

float wheel_dia=62;     
float wheel_base=111;    
int steps_rev=512; 
int delay_time=2; 

int L_stepper_pins[] = {2, 3, 4, 5};
int R_stepper_pins[] = {8, 9, 10, 11};

int fwd_mask[][4] =  {
    {HIGH,LOW,LOW,HIGH},
    {LOW,LOW,HIGH,HIGH},
   {LOW,HIGH,HIGH,LOW},
   {HIGH,HIGH,LOW,LOW}
  };

int rev_mask[][4] = {
    {HIGH,HIGH,LOW,LOW},
    {LOW,HIGH,HIGH,LOW},
    {LOW,LOW,HIGH,HIGH},
    {HIGH,LOW,LOW,HIGH}
  };



void setup() {
  //Serial.begin(9600);
  for(int pin=0; pin<4; pin++){
    pinMode(L_stepper_pins[pin], OUTPUT);
    digitalWrite(L_stepper_pins[pin], LOW);
    pinMode(R_stepper_pins[pin], OUTPUT);
    digitalWrite(R_stepper_pins[pin], LOW);
  }
  penServo.attach(servoPin);

  
  penup();
  
  delay(1000);
}


void loop(){ 
  pendown();
  //t();
 // a();
  square();
  //triangle();
  penup();
  done();      
  while(1);    
}


int step(float distance){
  int steps = distance * steps_rev / (wheel_dia * 3.1412); 
  /*
  Serial.print(distance);
  Serial.print(" ");
  Serial.print(steps_rev);
  Serial.print(" ");  
  Serial.print(wheel_dia);
  Serial.print(" ");  
  Serial.println(steps);
  delay(1000);*/
  return steps;  
}


void forward(float distance){
  int steps = step(distance);
  //Serial.println(steps);
  for(int step=0; step<steps; step++){
    for(int mask=0; mask<4; mask++){
      for(int pin=0; pin<4; pin++){
        digitalWrite(L_stepper_pins[pin], rev_mask[mask][pin]);
        digitalWrite(R_stepper_pins[pin], fwd_mask[mask][pin]);
      }
      delay(delay_time);
    } 
  }
}


void backward(float distance){
  int steps = step(distance);
  for(int step=0; step<steps; step++){
    for(int mask=0; mask<4; mask++){
      for(int pin=0; pin<4; pin++){
        digitalWrite(L_stepper_pins[pin], fwd_mask[mask][pin]);
        digitalWrite(R_stepper_pins[pin], rev_mask[mask][pin]);
      }
      delay(delay_time);
    } 
  }
}


void right(float degrees){
  float rotation = degrees / 360.0;
  float distance = wheel_base * 3.1412 * rotation;
  int steps = step(distance);
  for(int step=0; step<steps; step++){
    for(int mask=0; mask<4; mask++){
      for(int pin=0; pin<4; pin++){
        digitalWrite(R_stepper_pins[pin], rev_mask[mask][pin]);
        digitalWrite(L_stepper_pins[pin], rev_mask[mask][pin]);
      }
      delay(delay_time);
    } 
  }   
}


void left(float degrees){
  float rotation = degrees / 360.0;
  float distance = wheel_base * 3.1412 * rotation;
  int steps = step(distance);
  for(int step=0; step<steps; step++){
    for(int mask=0; mask<4; mask++){
      for(int pin=0; pin<4; pin++){
        digitalWrite(R_stepper_pins[pin], fwd_mask[mask][pin]);
        digitalWrite(L_stepper_pins[pin], fwd_mask[mask][pin]);
      }
      delay(delay_time);
    } 
  }   
}


void done(){ 
  for(int mask=0; mask<4; mask++){
    for(int pin=0; pin<4; pin++){
      digitalWrite(R_stepper_pins[pin], LOW);
      digitalWrite(L_stepper_pins[pin], LOW);
    }
    delay(delay_time);
  }
}


void penup(){
  delay(250);
  //Serial.println("PEN_UP()");
  penServo.write(PEN_UP);
  delay(250);
}


void pendown(){
  delay(250);  
  //Serial.println("PEN_DOWN()");
  penServo.write(PEN_DOWN);
  delay(250);
}

void t(){
  penup();
  left(90);
  forward(50);
  right(90);
  pendown();
  forward(30);
  backward(15);
  penup();
  right(90);
  pendown();
  forward(50);
  penup();
  left(90);
  forward(35);
  }


void a(){
  penup();
  left(75);
  pendown();
  forward(52);
  penup();
  right(140);
  pendown();
  forward(52);
  penup();
  left(155);
  forward(15);
  left(90);
  pendown();
  forward(30);
  penup();
  left(90);
  forward(15);
  left(90);
  forward(50);
  }

void square()
{
   for(int x=0; x<12; x++){  // SQUARE
    forward(100);
    left(90);
  }
  }

void triangle()
{
   for(int x=0; x<9; x++){  // Triangle
    forward(100);
    left(120);
  }
  }
