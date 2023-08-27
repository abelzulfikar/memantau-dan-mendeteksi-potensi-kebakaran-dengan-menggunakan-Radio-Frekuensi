#include <LiquidCrystal_I2C.h>

#include <nRF24L01.h>

#include <RF24.h>
#include <RF24_config.h>

#include <Wire.h>

#include <SPI.h>
#define BUZZERPIN 3
int pesan [1];
LiquidCrystal_I2C lcd(0x27, 16, 2);
const uint64_t pipeIn = 0xE8E8F0F0E1LL; 
RF24 radio(9, 10);
struct MyData {
  byte h; 
  byte t;
};
MyData data;
void setup()
{
  Serial.begin(9600); 
  radio.begin();
  lcd.begin();
  lcd.home();
  lcd.backlight();
  lcd.clear();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(1, pipeIn);
  radio.startListening();
  //lcd.println("Receiver ");
}
void recvData()
{
  if ( radio.available() ) {
    radio.read(&data, sizeof(MyData));
    }
    

}
void loop()
{
  recvData();
  Serial.print("Humidity: ");
  Serial.print(data.h);
  lcd.setCursor(0,0);
  lcd.print("Humidity:"); 
  lcd.print(data.h);
  lcd.print("%");
  lcd.setCursor(0,1);
  Serial.print("Temperature: ");
  Serial.print(data.t);
  lcd.print("Temperature:");
  lcd.print(data.t);
  lcd.print(" C");  
  //Serial.print("\n");
  {
   if ((data.t > 0) && (data.t <= 32))
    {
    delay(10);
    digitalWrite(BUZZERPIN, LOW);
  }
  else if ((data.t > 34) && (data.t <= 45))
   {
    delay(10);
    digitalWrite(BUZZERPIN, HIGH);
    tone(3, 500, 1000);
    delay(10);
     digitalWrite(BUZZERPIN, LOW);
   }
}
}
