#define LIGHT_PIN 3
#define LIGHT_VCC 5
#define MOTION_PIN 2
#define MOTION_VCC 8
#define LED 9

#include <avr/sleep.h>
#include <avr/interrupt.h>

volatile bool night = false;             // Переменная для хранения времени суток (0-день, 1-ночь)
volatile bool motion = false;            // 1 - есть движение

void wakeUpMotion()        // Прерывание сработает после пробуждения
{
  sleep_disable();     // Выключаем спящий режим
  motion = 1;
}

void wakeUp()        // Прерывание сработает после пробуждения
{
  sleep_disable();     // Выключаем спящий режим
}

void setup()
{
  pinMode(MOTION_VCC, OUTPUT);
  pinMode(LIGHT_VCC, OUTPUT);
  pinMode(MOTION_PIN, INPUT);
  pinMode(LIGHT_PIN, INPUT);
  pinMode(LED, OUTPUT);
  set_sleep_mode(SLEEP_MODE_PWR_SAVE);   // Устанавливаем режим сна
  for(int i = 0; i<5; i++) {
    digitalWrite(LED, HIGH);
    delay(1200);
    digitalWrite(LED, LOW);
    delay(600);
  }
  digitalWrite(LIGHT_VCC, HIGH);
  digitalWrite(LIGHT_PIN, LOW);
  Serial.begin(9600);

  
}

void sleep()         // Функция ввода ардуины в спящий режим
{
  Serial.println("sleepEnter");
  delay(100);  
  attachInterrupt(1, wakeUp, CHANGE);
  attachInterrupt(0, wakeUpMotion, CHANGE);      // Используем прерывание для выполнения функции wakeUp при появлении HIGH уровня
  sleep_enable();                        // Включаем sleep-бит в регистре mcucr. Теперь возможен сон
  sleep_mode();                          // Здесь устройство перейдет в режим сна

  detachInterrupt(0);
  detachInterrupt(1);
  
  if(digitalRead(LIGHT_PIN) == HIGH) 
  {
    Serial.println("NIGHT");
    night = true;
    digitalWrite(MOTION_VCC, HIGH);
  } else {
    Serial.println("DAY");
    night = false;
    sleep();
  }
}

void shining()
{
  digitalWrite(LED, HIGH);
  delay(10000);
  digitalWrite(LED, LOW);
}

void loop()
{
  if(night) 
  {
    if(motion)
    {
      Serial.println("shining");
      delay(10000);
      motion = false;
      digitalWrite(MOTION_VCC, LOW);
    } else {
    
    }
  } else {
    Serial.println("Sleeeeping, DAY");
    sleep();
  }
  sleep();     // Вызов функции sleep() для засыпания
}
