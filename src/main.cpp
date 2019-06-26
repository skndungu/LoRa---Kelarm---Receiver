#include <Arduino.h>

#include <SPI.h>
#include <LoRa.h>

int led = 6;
int received_value = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  while (!Serial)
    ;
  Serial.println("LoRa Receiver");

  if (!LoRa.begin(433E6))
  {
    Serial.println("Starting LoRa failed!");
    while (1)
      ;
  }
}

void loop()
{
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize)
  {
    // received a packet
    Serial.print("Received packet '");

    // read packet
    while (LoRa.available())
    {
      received_value = LoRa.read();
      Serial.print((char)received_value);
      //      Serial.print((char)LoRa.read());
      (received_value == '5') ? blink() : digitalWrite(led, LOW);
    }

    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }
}

void blink()
{
  digitalWrite(led, HIGH);
  delay(50);
  digitalWrite(led, LOW);
  delay(50);
}
