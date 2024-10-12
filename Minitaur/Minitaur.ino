// Pines para el receptor y el controlador de motores
const int servoPin1 = 3; // Canal 1 del receptor
const int servoPin2 = 9; // Canal 2 del receptor

// Pines del controlador de motores L9110S
const int motor1In1 = 6; // Entrada 1 del Motor 1
const int motor1In2 = 5; // Entrada 2 del Motor 1
const int motor2In1 = 11; // Entrada 1 del Motor 2
const int motor2In2 = 10; // Entrada 2 del Motor 2

// Variables para almacenar los valores de los canales
int channel1Value = 0; // Vertical (avanzar/reversa)
int channel2Value = 0; // Horizontal (giro)

void setup() {
  // Inicializar los pines del controlador de motores
  pinMode(motor1In1, OUTPUT);
  pinMode(motor1In2, OUTPUT);
  pinMode(motor2In1, OUTPUT);
  pinMode(motor2In2, OUTPUT);

  // Configuración del receptor
  pinMode(servoPin1, INPUT);
  pinMode(servoPin2, INPUT);

  // Configuración del puerto serial para depuración
  Serial.begin(9600);
}

void loop() {
  // Leer los valores de los canales del receptor
  channel1Value = pulseIn(servoPin1, HIGH); // Lectura del canal 1 en microsegundos
  channel2Value = pulseIn(servoPin2, HIGH); // Lectura del canal 2 en microsegundos

  // Mapea los valores del canal (suponiendo que el rango es 1000-2000 us)
  int forwardSpeed = map(channel1Value, 950, 2050, -250, 250); // Movimiento adelante/reversa
  int turnSpeed = map(channel2Value, 950, 2050, -250, 250); // Giro

  // Controlar el Motor 1 y Motor 2
  int motor1Speed = forwardSpeed + turnSpeed; // Combinación para dirección y velocidad
  int motor2Speed = forwardSpeed - turnSpeed; // Combinación para dirección y velocidad

  // Ajustar los valores de los motores
  if (motor1Speed > 0) {
    analogWrite(motor1In1, motor1Speed);
    digitalWrite(motor1In2, LOW);
  } else {
    analogWrite(motor1In2, -motor1Speed);
    digitalWrite(motor1In1, LOW);
  }

  if (motor2Speed > 0) {
    analogWrite(motor2In1, motor2Speed);
    digitalWrite(motor2In2, LOW);
  } else {
    analogWrite(motor2In2, -motor2Speed);
    digitalWrite(motor2In1, LOW);
  }

  // Depuración en el puerto serial
  Serial.print("Channel 1 (Vertical): ");
  Serial.print(channel1Value);
  Serial.print(" Channel 2 (Horizontal): ");
  Serial.println(channel2Value);

  // Pequeña pausa
  delay(20);
}
