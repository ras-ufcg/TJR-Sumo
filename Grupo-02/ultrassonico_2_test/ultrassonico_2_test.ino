// Código para a utilização de dois sensores ultrasônicos:

// Definindo as portas echos e triggers

#define echoPin_frente 5
#define trigPin_frente 4
#define echoPin_costas 6
#define trigPin_costas 7

// variáveis sem sinal no intervalo de 0 a 255

unsigned int duracao = 0;
unsigned int distancia = 0;

void setup(){
  
  // Informando as entradas e as saídas
  
  pinMode(echoPin_frente, INPUT);
  pinMode(trigPin_frente, OUTPUT);
  pinMode(echoPin_costas, INPUT);
  pinMode(trigPin_costas, OUTPUT);
  
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
  
  // Localiza se inimigo está visível a frente
  
  if(distancia <= 45){
  
  	Serial.print(distancia);
  	Serial.println("cm --- Adversario a frente");
  	delayMicroseconds(10);
    
  }
  
  else{
  
  	Serial.print(distancia);
  	Serial.println("cm --- Adversario fora de vista");
  	delayMicroseconds(10);
    
    // Funcionamento do sensor traseiro
    
  	digitalWrite(trigPin_costas, HIGH);
  	delayMicroseconds(10);
  	digitalWrite(trigPin_costas, LOW);
    
    // Captação do sinal de onda traseiro
    
    duracao = pulseIn(echoPin_costas, HIGH);
  
  	distancia = duracao * 0.017175;
    
    // Localiza se inimigo está visível atrás
    
    if(distancia <= 45){
  
      Serial.print(distancia);
      Serial.println("cm --- Adversario na retaguarda");
      delayMicroseconds(10);
    
    }
  
  	else{
  
      Serial.print(distancia);
      Serial.println("cm --- Adversario fora de vista");
      delayMicroseconds(10);
    
    }
  
  }
  
}