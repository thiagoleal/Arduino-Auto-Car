#include "Servo.h"
#include "Ultrasonic.h"

// Define os pinos de utilização do Driver L298.
int motorA1  = 3;
int motorA2  = 9;
int motorB1  = 11;
int motorB2  = 10;

int trigPin  = 4;
int echoPin  = 5; 

const int servoPin  = 7;

int speedR = 250;
int speedL = 255;

Ultrasonic ultrasonic(trigPin,echoPin);
Servo servo;

void setup() {
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);

  servo.attach(servoPin);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
   servo.write(90);

  int dist = distance();
  
  if (dist < 25) {
    
    move('S');
    
    servo.write(0);
    delay(400);
    
    int distR = distance();
  
    servo.write(180);
    delay(400);
    int distL = distance();
    servo.write(90);
    
    if(distR > distL) {
      if (dist < 10){
        move('H');  
      } else {
        move('R');
      }
      delay(420);
    } else {
        if (dist < 10){
        move('J');  
      } else {
        move('L');
      }

     delay(280);
    }
    move('S');
  } else {
    move('F');
  }
  
  delay(50); 
}

void move (char state) {
    // Se o estado recebido for igual a 'F', o carro se movimenta para frente.
  if (state == 'F') {
    analogWrite(motorB1, speedR);
    analogWrite(motorA1, speedL);
    analogWrite(motorA2, 0);
    analogWrite(motorB2, 0);
  }

    else if (state == 'I') {  // Se o estado recebido for igual a 'I', o carro se movimenta para Frente Esquerda.
    analogWrite(motorA1, speedL); 
    analogWrite(motorA2, 0);
    analogWrite(motorB1, 100);    
    analogWrite(motorB2, 0);
  }

    else if (state == 'G') {   // Se o estado recebido for igual a 'G', o carro se movimenta para Frente Direita.
    analogWrite(motorA1, 100); 
    analogWrite(motorA2, 0);
    analogWrite(motorB1, speedR);      
    analogWrite(motorB2, 0);
  }

  else if (state == 'B') { // Se o estado recebido for igual a 'B', o carro se movimenta para trás.
    analogWrite(motorA1, 0);
    analogWrite(motorB1, 0);
    analogWrite(motorB2, 255);
    analogWrite(motorA2, 255);
  }

   else if (state == 'H') {  // Se o estado recebido for igual a 'H', o carro se movimenta para Trás Esquerda.
    analogWrite(motorA1, 0);   
    analogWrite(motorA2, 255);
    analogWrite(motorB1, 0); 
    analogWrite(motorB2, 255);
  }
  
  else if (state == 'J') {  // Se o estado recebido for igual a 'J', o carro se movimenta para Trás Direita.
    analogWrite(motorA1, 0);   
    analogWrite(motorA2, 255);
    analogWrite(motorB1, 0);   
    analogWrite(motorB2, 255);
  }

  else if (state == 'L') {   // Se o estado recebido for igual a 'L', o carro se movimenta para esquerda.
    analogWrite(motorA1, 0);
    analogWrite(motorA2, speedL);
    analogWrite(motorB1, speedR);
    analogWrite(motorB2, 0);
  }
  else if (state == 'R') {   // Se o estado recebido for igual a 'R', o carro se movimenta para direita.
    analogWrite(motorA1, speedL);
    analogWrite(motorA2, 0);
    analogWrite(motorB1, 0);
    analogWrite(motorB2, speedR);
  }
  else if (state == 'S') {   // Se o estado recebido for igual a 'S', o carro permanece parado.
    analogWrite(motorA1, 0);
    analogWrite(motorA2, 0);
    analogWrite(motorB1, 0);
    analogWrite(motorB2, 0);
  }
}

int distance() {
  return ultrasonic.convert(ultrasonic.timing(), Ultrasonic::CM);
}
