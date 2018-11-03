#define LIGHT_PIN 3
#define LIGHT_VCC 5
#define MOTION_PIN 7
#define MOTION_VCC 8
#define LED 9

#define analogPIN 1

#include <avr/sleep.h>
#include <avr/interrupt.h>

volatile int sleepStatus = 0;             // Переменная для хранения статуса (спим, проснулись)

void wakeUp()        // Прерывание сработает после пробуждения
{
  sleep_disable();     // Выключаем спящий режим
  //detachInterrupt(1);
}

void setup()
{
  pinMode(MOTION_VCC, OUTPUT);
  pinMode(LIGHT_VCC, OUTPUT);
  pinMode(MOTION_PIN, INPUT);
  pinMode(LIGHT_PIN, INPUT);
  pinMode(LED, OUTPUT);
  set_sleep_mode(SLEEP_MODE_PWR_SAVE);   // Устанавливаем режим сна
  /*for(int i = 0; i<5; i++) {
    digitalWrite(LED, HIGH);
    delay(1500);
    digitalWrite(LED, LOW);
    delay(700);
  }
  digitalWrite(LED, HIGH);*/
  digitalWrite(LIGHT_VCC, HIGH);
  digitalWrite(LIGHT_PIN, LOW);
  attachInterrupt(1, wakeUp, RISING);
  Serial.begin(9600);

  
}

void sleep()         // Функция ввода ардуины в спящий режим
{
  Serial.println("sleepEnter");
  delay(100);
  //set_sleep_mode(SLEEP_MODE_PWR_SAVE);   // Устанавливаем режим сна
  //digitalWrite(MOTION_VCC, LOW);
  //digitalWrite(LED, LOW);             // Выключаем светодиодов
  //attachInterrupt(1,wakeUp, HIGH);     // Используем прерывание для выполнения функции wakeUp при появлении HIGH уровня
  //delay(100);
  sleep_enable();                        // Включаем sleep-бит в регистре mcucr. Теперь возможен сон
  sleepStatus = 1;                       // В переменную заносим статус сна
  sleep_mode();                          // Здесь устройство перейдет в режим сна
  Serial.println("kaka");
  delay(100);
  shining();
  //sleep_disable();
  //detachInterrupt(1);
}

void shining()
{
              // В переменную заносим статус бодрствования
  Serial.println("shinning");
  delay(1000);
  /*digitalWrite(LED, HIGH);
  delay(10000);
  digitalWrite(LED, LOW);*/
}

void loop()
{
  Serial.println(analogRead(analogPIN)*0.0049);
  Serial.println(sleepStatus);
  if (sleepStatus)
  {
    Serial.println("sleepStatus");
    sleepStatus = 0; 
    delay(1000);
  } else 
  {
    Serial.println("lol");
    sleep();     // Вызов функции sleep() для засыпания
  }
  Serial.println("loop");
  delay(10000);
  //digitalWrite(MOTION_VCC, HIGH);
  /*digitalWrite(LED, HIGH);
  delay(5000);
  digitalWrite(LED, LOW);*/
  //delay(2000);
  /*while(true)
  {
    if(MOTION_PIN == HIGH)
    {
      shining();
    } else
    break;
  }*/
  //digitalWrite(MOTION_VCC, LOW);
  sleep();     // Вызов функции sleep() для засыпания
}
