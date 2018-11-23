// Configurações de linha
int preto = 200; // Quanto menor, mais sensível

// Configurações de velocidade
int velocidade_reta = 120;
int velocidade_curva1 = 150;
int velocidade_curva2 = 190;

// Configurações obstáculo
int distancia_obstaculo = 4;
int obstaculo1_delay_direita = 430;
int obstaculo2_delay_reta = 500;
int obstaculo3_delay_esquerda = 420;
int obstaculo4_delay_reta = 550;
int obstaculo5_delay_esquerda = 420;
int obstaculo6_delay_reta = 150;

// Pinos
int pin_motor_a_e = 2; // Ponte H - En 1
int pin_motor_a_0 = 4; // Ponte H - In 1
int pin_motor_a_1 = 5; // Ponte H - In 2
int pin_motor_b_e = 3; // Ponte H - En 2
int pin_motor_b_0 = 6; // Ponte H - In 3
int pin_motor_b_1 = 7; // Ponte H - In 4

int pin_ultrassonico_echo = 25;
int pin_ultrassonico_trigger = 24;

void setup() {

  // Inicializa o monitor serial com a velocidade de 9600
  Serial.begin(9600);

  // Define os pinos do motor como saída
  pinMode(pin_motor_a_e, OUTPUT);
  pinMode(pin_motor_a_0, OUTPUT);
  pinMode(pin_motor_a_1, OUTPUT);
  pinMode(pin_motor_b_e, OUTPUT);
  pinMode(pin_motor_b_0, OUTPUT);
  pinMode(pin_motor_b_1, OUTPUT);

  pinMode(pin_ultrassonico_echo, INPUT);
  pinMode(pin_ultrassonico_trigger, OUTPUT);

  // Se true a função será executada
  TesteGeral(false);
}

void loop() {
  // Detecção da linha preta
  // Sensores internos
  // - o - - -
  if (sensor(A1)) {
    MotorA(velocidade_curva1, -1);
    MotorB(velocidade_curva1, 1);
  }
  // - - - o -
  if (sensor(A3)) {
    MotorA(velocidade_curva1, 1);
    MotorB(velocidade_curva1, -1);
  }

  // Sensores Extremos
  // o - - - -
  if (sensor(A0)) {
    MotorA(velocidade_curva2, -1);
    MotorB(velocidade_curva2, 1);
  }
  // - - - - o
  if (sensor(A4)) {
    MotorA(velocidade_curva2, 1);
    MotorB(velocidade_curva2, -1);
  }

  // Encruzilhada direita
  if ((sensor(A3) and sensor(A4)) or
      (sensor(A2) and sensor(A3) and sensor(A4))) {
    // Anda reto
    MotorA(velocidade_reta, 1);
    MotorB(velocidade_reta, 1);
    delay(150);

    // Vira direita até encontrar a linha
    while (!sensor(A2)) { // enquanto for branco
      MotorA(velocidade_curva1, 1);
      MotorB(velocidade_curva1, -1);
    }
  }

  // Encruzilhada esquerda
  if ((sensor(A1) and sensor(A0)) or
      (sensor(A2) and sensor(A1) and sensor(A0))) {
    // Anda reto
    MotorA(velocidade_reta, 1);
    MotorB(velocidade_reta, 1);
    delay(150);

    // Vira direita até encontrar a linha
    while (!sensor(A2)) { // enquanto for branco
      MotorA(velocidade_curva1, -1);
      MotorB(velocidade_curva1, 1);
    }
  }

  // Todos sensores branco
  if (!sensor(A0) and !sensor(A1) and !sensor(A3) and !sensor(A4)) {
    MotorA(velocidade_reta, 1);
    MotorB(velocidade_reta, 1);
  }

  // Obstáculo a frente
  if (obstaculo(pin_ultrassonico_trigger, pin_ultrassonico_echo, distancia_obstaculo)) {
    // Vira direita
    MotorA(velocidade_curva1, 1);
    MotorB(velocidade_curva1, -1);
    delay(obstaculo1_delay_direita);

    // Segue reto
    MotorA(velocidade_curva1, 1);
    MotorB(velocidade_curva1, 1);
    delay(obstaculo2_delay_reta);

    // Vira esquerda
    MotorA(velocidade_curva1, -1);
    MotorB(velocidade_curva1, 1);
    delay(obstaculo3_delay_esquerda);

    // Segue reto
    MotorA(velocidade_curva1, 1);
    MotorB(velocidade_curva1, 1);
    delay(obstaculo4_delay_reta);

    // Vira esquerda
    MotorA(velocidade_curva1, -1);
    MotorB(velocidade_curva1, 1);
    delay(obstaculo5_delay_esquerda);

    // Anda reto até encontrar a linha
    while (!sensor(A2)) { // enquanto for branco
      MotorA(velocidade_curva1, 1);
      MotorB(velocidade_curva1, 1);
    }

    // Anda reto
    MotorA(velocidade_curva1, 1);
    MotorB(velocidade_curva1, 1);
    delay(obstaculo6_delay_reta);

    // Vira direita até encontrar a linha
    while (!sensor(A2)) { // enquanto for branco
      MotorA(velocidade_curva1, 1);
      MotorB(velocidade_curva1, -1);
    }
  }
}

// Função para detectar se for linha
bool sensor(int pin) {
  if (analogRead(pin) > preto) {
    return true; // retorna verdadeiro se for preto
  } else {
    return false; // retorna falso se for branco
  }
}

// Função para controlar o motor A
// Parametros: velocidade (0 a 255) e o sentido (-1 trás, 0 para, 1 frente)
// Retorno: vazio (não há necessidade de retorno)
void MotorA(int velocidade, int sentido) {
  analogWrite(pin_motor_b_e, velocidade);
  if (sentido == 1) {
    digitalWrite(pin_motor_b_0, 1);
    digitalWrite(pin_motor_b_1, 0);
  } else if (sentido == -1) {
    digitalWrite(pin_motor_b_0, 0);
    digitalWrite(pin_motor_b_1, 1);
  } else {
    digitalWrite(pin_motor_b_0, 0);
    digitalWrite(pin_motor_b_1, 0);
  }
}

// Função para controlar o motor B
// Parametros: velocidade (0 a 255) e o sentido (-1 trás, 0 para, 1 frente)
// Retorno: vazio (não há necessidade de retorno)
void MotorB(int velocidade, int sentido) {
  analogWrite(pin_motor_a_e, velocidade);
  if (sentido == 1) {
    digitalWrite(pin_motor_a_0, 0);
    digitalWrite(pin_motor_a_1, 1);
  } else if (sentido == -1) {
    digitalWrite(pin_motor_a_0, 1);
    digitalWrite(pin_motor_a_1, 0);
  } else {
    digitalWrite(pin_motor_a_0, 0);
    digitalWrite(pin_motor_a_1, 0);
  }
}

// Função para detectar um obstáculo utilizando o sensor ultrassônico HC-SR04
// Retorno: verdadeiro se encontrar um obstáculo
// Parâmetros: pino de Trigger (emissor), Echo (receptor) e a distância máxima a ser detectada
bool obstaculo(int trigger, int echo, int distancia) {
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);

  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  unsigned long tempo_eco = pulseIn(echo, HIGH, 3000);
  double medicao = tempo_eco / 2.0 * 0.0343;

  if (medicao == 0 || medicao > 400) return false;
  else if (medicao <= distancia) return true;
  else return false;

}

void TesteGeral(bool modo) {
  if (modo == true) {
    Serial.println("Modo de teste iniciado");
    while (true) { // Repete infinitamente
      String dados = ""; // Variável para armazenar caracteres iniciada vazia
      String s1 = (String)analogRead(A0);
      String s2 = (String)analogRead(A1);
      String s3 = (String)analogRead(A2);
      String s4 = (String)analogRead(A3);
      String s5 = (String)analogRead(A4);
      dados = "S:" + s1 + " " + s2 + " " + s3 + " " + s4 + " " + s5;
      String us = (String)obstaculo(pin_ultrassonico_trigger, pin_ultrassonico_echo, 10);
      dados = dados + " - US:" + us;
      Serial.println(dados);
    }
  }
}
