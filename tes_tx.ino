#include <DHT.h>
#include <DHT_U.h>

#include <SPI.h>

#include <nRF24L01.h>

#include <RF24.h>
#include <RF24_config.h>

#include <dht.h>


const uint64_t pipeOut = 0xE8E8F0F0E1LL; 
#define DHTPIN A0 
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);
#define BUZZER 3
RF24 radio(9, 10); //  CN and CSN  pins of nrf
struct MyData {
  byte h;
  byte t;
};
MyData data;
void setup()
{
  Serial.begin(9600); 
  dht.begin();
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(pipeOut);
  pinMode(BUZZER,OUTPUT);
}
void loop()
{
  data.h = dht.readHumidity();
  data.t = dht.readTemperature();
  if (isnan(data.h) || isnan(data.t)){
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  {
  Serial.print("Humidity: ");
  Serial.print(data.h);
  Serial.print("Temperature: ");
  Serial.print(data.t);
  radio.write(&data, sizeof(MyData));
}
}
