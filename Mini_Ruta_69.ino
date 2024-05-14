#include <Arduino.h>
#include <Wire.h>
#include <Servo.h>
#define SW1 1
#define SW2 12
#define LINE A1
#define DER A2
#define IZQ A4
#define CEN A3
#define START 0


//MOTORES
#define MD1 3
#define MD2 6
#define MI1 9
#define MI2 5

void setup(){
  pinMode(SW1, OUTPUT);
  pinMode(SW2, OUTPUT);
  pinMode(LINE, INPUT);
  pinMode(START, INPUT);
  pinMode(DER, INPUT);
  pinMode(IZQ, INPUT);
  pinMode(CEN, INPUT);
  pinMode(MD1, OUTPUT);
  pinMode(MD2, OUTPUT);
  pinMode(MI1, OUTPUT);
  pinMode(MI2, OUTPUT);
  Serial.begin(9600);
}


byte sensores(){
  byte DERECHA = digitalRead(DER);
  byte IZQUIERDA = digitalRead(IZQ)*2;
  byte CENTRO = digitalRead(CEN)*4;
  byte suma = DERECHA + IZQUIERDA + CENTRO;
  return suma;
}

byte linea(){ 
  byte lin = digitalRead(LINE);
  return lin;
}

void adelante(int a, int b, int t){
  analogWrite(MD1, a);
  digitalWrite(MD2, LOW);
  analogWrite(MI1, b);
  digitalWrite(MI2, LOW);
  delay(t);
}

void atras(int t){
  digitalWrite(MD1, LOW);
  analogWrite(MD2, 255);
  digitalWrite(MI1, LOW);
  analogWrite(MI2, 255);
  delay(t);
}

void derecha(int a, int b, int t){
  digitalWrite(MD1, LOW);
  analogWrite(MD2, a);
  analogWrite(MI1, b);
  digitalWrite(MI2, LOW);
  delay(t);
}

void izquierda(int a, int b, int t){
  analogWrite(MD1, a);
  digitalWrite(MD2, LOW);
  digitalWrite(MI1, LOW);
  analogWrite(MI2, b);
  delay(t);
}

void paro(int t){
  analogWrite(MD1, 255);
  analogWrite(MD2, 255);
  analogWrite(MI1, 255);
  analogWrite(MI2, 255);
  delay(t);
}

void detenido(){
  analogWrite(MD1, LOW);
  analogWrite(MD2, LOW);
  analogWrite(MI1, LOW);
  analogWrite(MI2, LOW);
}

void loop(){

  int start = digitalRead(START);
  Serial.println(start);


  while(digitalRead(START)==1){
    switch(linea()){
      case 0: 
      Serial.println("linea");
      atras(320);
      derecha(255, 255, 170);
      break;

      case 1:
        switch(sensores()){
          case 0:
          adelante(180,180,25);
          Serial.println("Ninguno");
          break;

          case 1: 
          derecha(255, 255, 140);
          Serial.println("Derecha");
          break;

          case 2:
          izquierda(255,255,140);
          Serial.println("Izquierda");
          break;

          case 3:
          atras(25);
          Serial.println("Atras");
          break;

          case 4:
          adelante(255, 255, 140);
          Serial.println("Centro");
          break;

          case 5:
          derecha(200, 200, 100);
          Serial.println("Derecha y centro");
          break;

          case 6:
          izquierda(200, 200, 100);
          Serial.println("Izquierda y centro");
          break;


        }   
        break; 

      }
     }
    if(digitalRead(START)==0){
      detenido();
    }
}