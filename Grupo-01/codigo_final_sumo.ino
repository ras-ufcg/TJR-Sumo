

#include <Ultrasonic.h>


//********************Definição dos pinos********************
// Pinos vão mudar de acordo com a nescessidade 
#define trigger 14
#define echo   15
#define triggeresq 16
#define echoesq   17
#define triggerdir 18
#define echodir   19
#define sensor1 2
#define sensor2 3
#define sensor3 4
#define sensor4 5
//********************Criação dos objetos********************
Ultrasonic ultrasonic(trigger, echo);
Ultrasonic ultrasonicesq(triggeresq, echoesq);
Ultrasonic ultrasonicdir(triggerdir, echodir);
int var = 0;
int a = 0;
int b = 1;
//********************Função de configuração******************
void setup() {
  //Configuração de velocidade dos motores
  //Pinos para o motor prescisão ser colocados em portas analógicas
  Serial.begin(9600);//Habilita a comunicação serial
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(sensor1, INPUT);//Configura o pino do sensor 1 como entrada
  pinMode(sensor2, INPUT);//Configura o pino do sensor 2 como entrada

  
  //pinMode(sensor3, INPUT);//Configura o pino do sensor 3 como entrada
  //pinMode(sensor4, INPUT);//Configura o pino do sensor 4 como entrada
}
//********************Função de principal********************
void loop() {
  //Cálculo e conversão da leitura do sensor ultrassônico
  long microsec = ultrasonic.timing();
  long microsecesq = ultrasonicesq.timing();
  long microsecdir = ultrasonicdir.timing();

  float distancia = ultrasonic.convert(microsec, Ultrasonic::CM);
  float distanciaesq = ultrasonicesq.convert(microsecesq, Ultrasonic::CM);
  float distanciadir = ultrasonicdir.convert(microsecdir, Ultrasonic::CM);

  
  //Mostra as leitura dos sensores
  //Quando for ler remova o /* */
    /*
    Serial.print("A distancia: ");
    Serial.print(distancia);
    Serial.print("\t");
    Serial.print("Sensor da frente: ");
    Serial.println(digitalRead(sensor1));
    //Serial.print("Sensor da tras: ");
    //Serial.println(digitalRead(sensor2));
    Serial.print("A distancia 2: ");
    Serial.print(distanciaesq);
    Serial.print("\t");
    Serial.print("A distancia 3: ");
    Serial.println(distanciadir);
    //delay(1000);
    //delay(1000);
  */
  //Verifica se tem alguma coisa na sua frente e se os sensor estão no branco
  if (distancia > 20 && distanciadir > 20 && distanciaesq > 20 && digitalRead(sensor1) == a && digitalRead(sensor2) == a ) {
    Serial.println("procurando oponente");
      if (var == 0){
        girar();//Fica Girando
      }

  }
  //Se caso encontrar algo na sua frente
  if ((distancia < 20 && distancia > 0) && distanciadir > 20 && distanciaesq > 20 && digitalRead(sensor1) == a && digitalRead(sensor2) == a ) {
    Serial.println("achei o oponente");
    frente();//Movimenta para frente

    
  }
  if ((distanciaesq < 20 && distanciaesq > 0) && distanciadir > 20 && distancia > 20 && digitalRead(sensor1) == a && digitalRead(sensor2) == a ) {
    Serial.println("achei o oponente ESQUERDA");

    giraresq();//Movimenta para esquerda
    var = 1;
    
  }
  if ((distanciadir < 20 && distanciadir > 0) && distanciaesq > 20 && distancia > 20 && digitalRead(sensor1) == a && digitalRead(sensor2) == a) {
    Serial.println("achei o oponente DIREITA");
    girar();//Movimenta para esquerda 
    var = 0;
  }
  //Se caso encontre a borda e não o oponente
  if (digitalRead(sensor1) == b || digitalRead(sensor2) == b) {
    Serial.println("Sensor da frente achou borda 1");
    stop();
    delay(1);
    re();
    delay(300);
    stop();
    
  }
  /*if (digitalRead(sensor3) == 1 ||digitalRead(sensor4) == 1 ) {
    Serial.println("Sensor da traseira achou borda 3");
    frente();
  }*/
  
}
//********************Movimenta do robô********************
void re() {
Serial.println("Re");
digitalWrite(6, LOW);
digitalWrite(7, HIGH);
digitalWrite(9, LOW);
digitalWrite(10, HIGH);
}
void frente() {
Serial.println("Frente");
digitalWrite(6, LOW);
digitalWrite(7, HIGH);
digitalWrite(9, LOW);
digitalWrite(10, HIGH);
}
void giraresq() {
Serial.println("Girando");
digitalWrite(6, LOW);
digitalWrite(7, HIGH);
digitalWrite(9, HIGH);
digitalWrite(10, LOW);
}
void girar() {
Serial.println("Girando");
digitalWrite(6, HIGH);
digitalWrite(7, LOW);
digitalWrite(9, LOW);
digitalWrite(10, HIGH);
}
void stop() {
Serial.println("parado");
digitalWrite(6, LOW);
digitalWrite(7, LOW);
digitalWrite(9, LOW);
digitalWrite(10, LOW);
}
