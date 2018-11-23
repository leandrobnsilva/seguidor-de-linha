// Configurações de linha
int preto = 300;

// Configurações de velocidade
int velocidade_reta = 150;
int velocidade_curva1 = 170;
int velocidade_curva2 = 190;

// Pinos
int pin_motor_a_e = 2; // Ponte H - En 1
int pin_motor_a_0 = 4; // Ponte H - In 1
int pin_motor_a_1 = 5; // Ponte H - In 2
int pin_motor_b_e = 3; // Ponte H - En 2
int pin_motor_b_0 = 6; // Ponte H - In 3
int pin_motor_b_1 = 7; // Ponte H - In 4

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
}

bool sensor(int pin) {
  if (analogRead(pin) > preto) {
    return true;
  } else {
    return false;
  }
}

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
