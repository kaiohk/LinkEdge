// Desenvolvido por:
// - KAIO HIROKI KINOSHITA - RM569127
// - LEONARDO DANIEL DOS SANTOS - RM571092
// - MATHEUS DIONISIO CINTRA - RM569844

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

#define TRIG_PIN 12
#define ECHO_PIN 13

DHT dht(11, DHT22);
Adafruit_MPU6050 mpu;
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int ledA[3] = {2, 3, 4};
const int ledB[3] = {5, 6, 7};
const int ledC[3] = {8, 9, 10};

int estadoA = 0, estadoB = 0, estadoC = 0;

void setup() {
  dht.begin();
  mpu.begin();
  lcd.init(); lcd.backlight();
  for(int i = 2; i <= 10; i++) pinMode(i, OUTPUT);
  lcd.print("LinkEdge Active");
  delay(1500); lcd.clear();
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  avaliarNoA();
  avaliarNoB();
  avaliarNoC();

  aplicarCor(ledA, estadoA);
  aplicarCor(ledB, estadoB);
  aplicarCor(ledC, estadoC);
  exibirStatus();

  delay(3500);
}

void avaliarNoA() {
  float temp = dht.readTemperature();
  float umid = dht.readHumidity();

  if (isnan(temp) || isnan(umid)) {
    estadoA = 0;
    return;
  }
  if (temp >= 40.0 || temp <= -20.0 || umid <= 20.0 || umid >= 80.0) {
    estadoA = 2;
  }
  else if (temp >= 35.0 || temp <= -10.0 || umid <= 40.0 || umid >= 65.0) {
    estadoA = 1;
  }
  else {
    estadoA = 0;
  }
}

void avaliarNoB() {
  digitalWrite(12, LOW);
  delayMicroseconds(2);
  digitalWrite(12, HIGH);
  delayMicroseconds(10);
  digitalWrite(12, LOW);

  long duracao = pulseIn(13, HIGH);

  int distancia = duracao / 58;

    if (distancia <= 20) {
      estadoB = 2;
    }
    else if (distancia <= 50) {
      estadoB = 1;
    }
    else if (distancia < 150) {
      estadoB = 0;
    }
    else if (distancia < 300) {
      estadoB = 1;
    }
    else {
      estadoB = 2;
  }
}

void avaliarNoC() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  float totalAcc = sqrt(pow(a.acceleration.x,2) + pow(a.acceleration.y,2) + pow(a.acceleration.z,2)) / 9.81;

  if (totalAcc >= 2.5) estadoC = 2;
  else if (totalAcc >= 1.5) estadoC = 1;
  else estadoC = 0;
}

void aplicarCor(const int pino[], int estado) {
  digitalWrite(pino[0], (estado == 1 || estado == 2) ? HIGH : LOW);
  digitalWrite(pino[1], (estado == 0 || estado == 1) ? HIGH : LOW);
  digitalWrite(pino[2], LOW);
}

void exibirStatus() {
  lcd.setCursor(0, 0); lcd.print("A:"); lcd.print(estadoA == 2 ? "ATEN" : (estadoA == 1 ? "ALER" : "NORM  "));
  lcd.setCursor(8, 0); lcd.print("B:"); lcd.print(estadoB == 2 ? "ATEN" : (estadoB == 1 ? "ALER" : "NORM  "));
  lcd.setCursor(0, 1); lcd.print("C:"); lcd.print(estadoC == 2 ? "ATEN" : (estadoC == 1 ? "ALER" : "NORM  "));
}
