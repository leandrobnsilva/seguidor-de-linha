void Setup() {
  
}

bool sensor(int pin) {
  if(analogRead(pin) > preto) {
    return 1;
  }
  return 0;
}

void MotorA(int velocidade, int sentido) {
  analogWrite(pin_motor_b_e, velocidade);
  if(sentido == 1) {
    digitalWrite(pin_motor_b_0, 1);
    digitalWrite(pin_motor_b_1, 0);
  } else if(sentido == -1) {
    digitalWrite(pin_motor_b_0, 0);
    digitalWrite(pin_motor_b_1, 1);
  } else {
    digitalWrite(pin_motor_b_0, 0);
    digitalWrite(pin_motor_b_1, 0);
  }
}
void MotorB(int velocidade, int sentido) {
  analogWrite(pin_motor_a_e, velocidade);
  if(sentido == 1) {
    digitalWrite(pin_motor_a_0, 0);
    digitalWrite(pin_motor_a_1, 1);
  } else if(sentido == -1) {
    digitalWrite(pin_motor_a_0, 1);
    digitalWrite(pin_motor_a_1, 0);
  } else {
    digitalWrite(pin_motor_a_0, 0);
    digitalWrite(pin_motor_a_1, 0);
  }
}
