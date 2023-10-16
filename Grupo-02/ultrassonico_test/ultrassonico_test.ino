// Código para a utilização de dois sensores ultrasônicos:

// Definindo as portas echos e triggers

#define echoPin_frente 5
#define trigPin_frente 4

// variáveis sem sinal no intervalo de 0 a 255

unsigned int duracao = 0;
unsigned int distancia = 0;

void setup(){
  
  // Informando as entradas e as saídas
  
  pinMode(echoPin_frente, INPUT);
  pinMode(trigPin_frente, OUTPUT);
  
  // Criando um monitor serial para informar os resultados
  
  Serial.begin(9600);
  
}

void loop(){
  
  // Funcionamento do sensor dianteiro
  
  digitalWrite(trigPin_frente, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_frente, LOW);
  
  // Captação do sinal de onda dianteiro
  
  duracao = pulseIn(echoPin_frente, HIGH);
  
  // Velocidade do som se propagando no ar dada por: "[(343,5 * 100)/10e6]/2 = 0,017175"  
  
  distancia = duracao * 0.017175;

  Serial.print(distancia);
  Serial.println("cm --- Adversario a frente");
  
  
  
}