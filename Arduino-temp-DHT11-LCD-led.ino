#include <Wire.h>      // Библиотека для использования I2C
#include <LiquidCrystal_I2C.h>  // Библиотека для использования ЖК-дисплея с I2C
#include <DHT.h>                    // Библиотека для использования датчика DHT
#define DHTPIN 8 
#define DHTTYPE DHT11
int ledPin1 = 9;
int ledPin2 = 10;
int ledPin3 = 11;
LiquidCrystal_I2C lcd(0x27, 16, 2);  // инициализировать объект lcd для класса LiquidCrystal_I2C с адресом I2C ЖК-дисплея типа 0x27 и 16x2
DHT dht(DHTPIN, DHTTYPE);
byte degree[8] = // кодируем символ градуса
{
B00111,
B00101,
B00111,
B00000,
B00000,
B00000,
B00000,
};

void setup() {
Serial.begin(9600);
lcd.init();
lcd.backlight();
lcd.createChar(1, degree);
dht.begin();
pinMode(ledPin1, OUTPUT);
pinMode(ledPin2, OUTPUT);
pinMode(ledPin3, OUTPUT);
}

void loop()
{
  float h = dht.readHumidity();       // Получаем значение влажности
  float t = dht.readTemperature();    // Получаем значение температуры
  if (t>24 and t<=26) digitalWrite(ledPin1, HIGH); // если значение 24<t<=26 включаем светодиод на 9 пине
  else digitalWrite(ledPin1, LOW); // если значение >=24 - выключаем светодиод на 9 пине
  if (t>26 and t<=28) digitalWrite(ledPin2, HIGH); // если значение 26<t<=28 включаем светодиод на 10 пине
  else digitalWrite(ledPin2, LOW); // если значение >=26 - выключаем светодиод на 10 пине
  if (t>28 and t<=30) digitalWrite(ledPin3, HIGH); // если значение 28<t<=30 включаем светодиод на 11 пине
  else digitalWrite(ledPin3, LOW); // если значение >=28 - выключаем светодиод на 11 пине
  if (isnan(h) || isnan(t)) {
  Serial.println(F("Failed to read from DHT sensor!"));
  return;
  }
  float hic = dht.computeHeatIndex(t);
  Serial.print(F("Влажность: "));
  Serial.print(h);
  Serial.print(F("% Температура: "));
  Serial.print(t);
  Serial.print(F("°C \n"));
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print(" *C");
  lcd.setCursor(0,1);
  lcd.print("Humid: ");
  lcd.print(h);
  lcd.print(" %");
  delay(2000);
}