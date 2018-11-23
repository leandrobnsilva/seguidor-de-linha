// Configurações de linha
int preto = 300;

// Configurações de velocidade
int velocidade_reta = 150;
int velocidade_curva1 = 170;
int velocidade_curva2 = 190;

// Configurações obstáculo
int distancia_obstaculo = 7;

// Pinos
int pin_motor_a_e = 2; // Ponte H - En 1
int pin_motor_a_0 = 4; // Ponte H - In 1
int pin_motor_a_1 = 5; // Ponte H - In 2
int pin_motor_b_e = 3; // Ponte H - En 2
int pin_motor_b_0 = 6; // Ponte H - In 3
int pin_motor_b_1 = 7; // Ponte H - In 4

int pin_ultrassonico_echo = 22;
int pin_ultrassonico_trigger = 23;

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
    delay(700);

    // Segue reto
    MotorA(velocidade_curva1, 1);
    MotorB(velocidade_curva1, -1);
    delay(1000);

    // Vira esquerda
    MotorA(velocidade_curva1, -1);
    MotorB(velocidade_curva1, 1);
    delay(700);

    // Segue reto
    MotorA(velocidade_curva1, 1);
    MotorB(velocidade_curva1, -1);
    delay(2000);

    // Vira esquerda
    MotorA(velocidade_curva1, -1);
    MotorB(velocidade_curva1, 1);
    delay(700);

    // Anda reto até encontrar a linha
    while (!sensor(A2)) { // enquanto for branco
      MotorA(velocidade_curva1, 1);
      MotorB(velocidade_curva1, 1);
    }

    // Anda reto
    MotorA(velocidade_curva1, 1);
    MotorB(velocidade_curva1, 1);
    delay(400);

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
  digitalWrite(trigger, 0);
  delayMicroseconds(2);

  digitalWrite(trigger, 1);
  delayMicroseconds(10);
  digitalWrite(trigger, 0);

  unsigned long tempo_eco = pulseIn(echo, HIGH);
  double medicao = tempo_eco / 2.0 * 0.0343;

  if (medicao <= 0 || medicao > 400) return false;
  else if (medicao <= distancia) return true;
  else return false;
}
