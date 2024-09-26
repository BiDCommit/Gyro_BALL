#include <Arduino.h>
#include <BleKeyboard.h>
#include <BleMouse.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
//#include "WiFi.h"

Adafruit_MPU6050 mpu;

//задефайнены светодиоды
#define ledD5 5
#define ledD4 4
#define ledD18 18
#define ledD2 2
#define ledD15 15
#define ledD19 19
int LedArr[]={ledD5,ledD4,ledD18,ledD2,ledD15,ledD19};


void setup(void) {
  Serial.begin(115200);//установка скорости порта
  //установка ble
  bleDevice.setName("GYROBALL"); //вызовите перед любой из функций begin, чтобы изменить имя устройства.
  bleDevice.setManufacturer("Espressif"); //вызовите перед любой из функций begin, чтобы изменить название производителя.
  bleDevice.setDelay(40); //измените задержку между каждым ключевым событием #, если определено(USE_NIMBLE)
  Keyboard.begin();//начинает эмулировать клавиатуру,
  delay(1500);//задержка на три секунды
  //установка светодиодов по оссям(x y z)
 for(int thisPin=0; thisPin<6; thisPin++){
  pinMode(LedArr[thisPin],OUTPUT);
  }
}

void loop() {
  /*Получайте новые события датчика вместе с показаниями */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  for(int PinNow=0; PinNow<6;PinNow++){
    digitalWrite(LedArr[PinNow],LOW);
  }
  //// для оси  X --> (+)
  if (g.gyro.x > 3) {
    digitalWrite(ledD19, HIGH);
    digitalWrite(ledD2, HIGH);
    digitalWrite(ledD15, HIGH);
    Keyboard.write(KEY_UP_ARROW );//Отправляет нажатие клавиши на подключенный компьютер
    delay(200);
  }
  //// Для оси X --> (-)
  if (g.gyro.x < -3) {
    digitalWrite(ledD19, HIGH);
    digitalWrite(ledD5, HIGH);
    digitalWrite(ledD15, HIGH);
    Keyboard.write(KEY_DOWN_ARROW);//Отправляет нажатие клавиши на подключенный компьютер
    delay(200);
  }
  // для оси Y --> (+)
  if (g.gyro.y > 3) {
    digitalWrite(ledD19, HIGH);
    digitalWrite(ledD18, HIGH);
    digitalWrite(ledD15, HIGH);
    Keyboard.write(KEY_RIGHT_ARROW);//Отправляет нажатие клавиши на подключенный компьютер
    delay(200);
  }
  // для оси Y --> (-)
  if (g.gyro.y < -3) {
    digitalWrite(ledD19, HIGH);
    digitalWrite(ledD4, HIGH);
    digitalWrite(ledD15, HIGH);
    Keyboard.write(KEY_LEFT_ARROW);//Отправляет нажатие клавиши на подключенный компьютер
    delay(200);
  }
  // для оси Z --> (+)
  if (g.gyro.z > 3) {
    digitalWrite(ledD2, HIGH);
    digitalWrite(ledD18, HIGH);
    Keyboard.write(KEY_Z);//Отправляет нажатие клавиши на подключенный компьютер
    delay(200);
  }
  // для оси Z --> (-)
  if (g.gyro.z < -3) {
    digitalWrite(ledD5, HIGH);
    digitalWrite(ledD4, HIGH);
    Keyboard.write(KEY_X);//Отправляет нажатие клавиши на подключенный компьютер
    delay(200);
  }
  Keyboard.releaseAll();//Отпускает все нажатые в данный момент клавиши
}