#include <Ultrasonic.h>

//********************Definição dos pinos********************
// Pinos vão mudar de acordo com a nescessidade 
#define trigger A2
#define echo   A3
#define sensor1 A4
#define sensor2 A5
#define sensor3 A6
#define sensor4 A7
//********************Criação dos objetos********************
Ultrasonic ultrasonic(trigger, echo);
//********************Função de configuração******************
void setup() {
  //Configuração de velocidade dos motores
  //Pinos para o motor prescisão ser colocados em portas analógicas
  Serial.begin(9600);//Habilita a comunicação serial
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(sensor1, INPUT);//Configura o pino do sensor 1 como entrada
  pinMode(sensor2, INPUT);//Configura o pino do sensor 2 como entrada
  pinMode(sensor3, INPUT);//Configura o pino do sensor 3 como entrada
  pinMode(sensor4, INPUT);//Configura o pino do sensor 4 como entrada
}
//********************Função de principal********************
void loop() {
  //Cálculo e conversão da leitura do sensor ultrassônico
  long microsec = ultrasonic.timing();
  float distancia = ultrasonic.convert(microsec, Ultrasonic::CM);
  //Mostra as leitura dos sensores
  //Quando for ler remova o /* */
  /*
    Serial.print("A distancia: ");
    Serial.println(distancia);
    Serial.print("Sensor da frente: ");
    Serial.println(digitalRead(sensor1));
    Serial.print("Sensor da tras: ");
    Serial.println(digitalRead(sensor2));
    delay(1000);
  */
  //Verifica se tem alguma coisa na sua frente e se os sensor estão no branco
  if (distancia > 20 && digitalRead(sensor1) == 0 && digitalRead(sensor2) == 0 && digitalRead(sensor3) == 0 && digitalRead(sensor4) == 0) {
    Serial.println("procurando oponente");
    girar();//Fica Girando
    
  }
  //Se caso encontrar algo na sua frente
  if (distancia < 20 && distancia > 0 && digitalRead(sensor1) == 0 && digitalRead(sensor2) == 0 && digitalRead(sensor3) == 0 && digitalRead(sensor4) == 0) {
    while (digitalRead(sensor1) == 0 && digitalRead(sensor2) == 0) { //Prende na condição até o sensor encotrar a borda da arena
      Serial.println("achei o oponente");
      frente();//Movimenta para frente
    }
    
  }
  //Se caso encontre a borda e não o oponente
  if (digitalRead(sensor1) == 1 || digitalRead(sensor2) == 1) {
    Serial.println("Sensor da frente achou borda");
    stop();
    delay(1);
    re();
    delay(300);
    stop();
    delay(1);
    girar();
    
  }
  if (digitalRead(sensor3) == 1 || digitalRead(sensor4) == 1) {
    Serial.println("Sensor de tras achou borda");
    frente();
  }
}
//********************Movimenta do robô********************
void re() {
Serial.println("Re");
analogWrite(5, 0);
analogWrite(6, 200);
analogWrite(9, 0);
analogWrite(10, 200);
}
void frente() {
Serial.println("Frente");
analogWrite(5, 200);
analogWrite(6, 0);
analogWrite(9, 200);
analogWrite(10, 0);
}
void girar() {
Serial.println("Girando");
analogWrite(5, 0);
analogWrite(6, 200);
analogWrite(9, 200);
analogWrite(10, 0);
}
void stop() {
Serial.println("parado");
analogWrite(5, 0);
analogWrite(6, 0);
analogWrite(9, 0);
analogWrite(10, 0);
}