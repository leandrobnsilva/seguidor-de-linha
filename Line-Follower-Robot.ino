int pin_motor_a_e = 2;
int pin_motor_a_0 = 4;
int pin_motor_a_1 = 5;

int pin_motor_b_e = 3;
int pin_motor_b_0 = 6;
int pin_motor_b_1 = 7;

int preto = 300; // Quanto menor, mais sensível (valor do preto é uns 470)
int velocidade_reta = 150;
int velocidade_curva1 = 170;
int velocidade_curva2 = 190;

void setup() {
  Serial.begin(9600);
  pinMode(pin_motor_a_e, OUTPUT);
  pinMode(pin_motor_a_0, OUTPUT);
  pinMode(pin_motor_a_1, OUTPUT);
  pinMode(pin_motor_b_e, OUTPUT);
  pinMode(pin_motor_b_0, OUTPUT);
  pinMode(pin_motor_b_1, OUTPUT);
}

void loop() {
  if (sensor(A1)) {
    MotorA(velocidade_curva1, -1);
    MotorB(velocidade_curva1, 1);
  }
  if (sensor(A3)) {
    MotorA(velocidade_curva1, 1);
    MotorB(velocidade_curva1, -1);
  }

  if (sensor(A0)) {
    MotorA(velocidade_curva2, -1);
    MotorB(velocidade_curva2, 1);
  }
  if (sensor(A4)) {
    MotorA(velocidade_curva2, 1);
    MotorB(velocidade_curva2, -1);
  }

  if (!sensor(A0) and !sensor(A1) and !sensor(A3) and !sensor(A4)) {
    MotorA(velocidade_reta, 1);
    MotorB(velocidade_reta, 1);
  }
}
