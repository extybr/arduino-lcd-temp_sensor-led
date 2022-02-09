#include <stdint.h>
#include "SparkFunBME280.h"
#include "Wire.h"
#include "SPI.h"
#include <LiquidCrystal_I2C.h>
int ledPin1 = 9;
int ledPin2 = 10;
int ledPin3 = 11;
BME280 mySensor;
LiquidCrystal_I2C lcd(0x27,16,2); 

void setup()
{
  lcd.init();
  lcd.backlight(); 
  mySensor.settings.commInterface = I2C_MODE;
  mySensor.settings.I2CAddress = 0x76; 
  mySensor.settings.runMode = 3; 
  mySensor.settings.tStandby = 5;
  mySensor.settings.filter = 0;
  mySensor.settings.tempOverSample = 1;
  mySensor.settings.pressOverSample = 1;
  mySensor.settings.humidOverSample = 1;
  mySensor.begin();
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
}

void loop()
{

  lcd.setCursor(0,0);
  lcd.print("H=");
  lcd.print((uint8_t)mySensor.readFloatHumidity());
  lcd.print("% ");
  lcd.print(mySensor.readFloatPressure());
  lcd.setCursor(14,0);
  lcd.print("Pa");  
  lcd.setCursor(0,1);
  lcd.print("T=");
  lcd.print(mySensor.readTempC());
  lcd.print(" P="); 
  int mmH=mySensor.readFloatPressure()/133;
  lcd.print(mmH);
  lcd.print("mmH");
  lcd.setCursor(14,1);
  if (mySensor.readTempC()>24 and mySensor.readTempC()<=26) digitalWrite(ledPin1, HIGH); // если значение 24<t<=26 включаем светодиод на 9 пине
  else digitalWrite(ledPin1, LOW); // если значение >=24 - выключаем светодиод на 9 пине
  if (mySensor.readTempC()>26 and mySensor.readTempC()<=28) digitalWrite(ledPin2, HIGH); // если значение 26<t<=28 включаем светодиод на 10 пине
  else digitalWrite(ledPin2, LOW); // если значение >=26 - выключаем светодиод на 10 пине
  if (mySensor.readTempC()>28 and mySensor.readTempC()<=30) digitalWrite(ledPin3, HIGH); // если значение 28<t<=30 включаем светодиод на 11 пине
  else digitalWrite(ledPin3, LOW); // если значение >=28 - выключаем светодиод на 11 пине
  delay(1000);

}