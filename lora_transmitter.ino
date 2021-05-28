#include <SPI.h>
#include <RH_RF95.h>

#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 7
#define RF95_FREQ 915.0

// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);

#define LED 13

        // Wait Without Delay
            unsigned long ping_previousMillis = 0;
            int long ping_interval = 5000;
              // Adjust ping_interval for more/less transmitter gap time

void setup() 
{
 
  pinMode(LED, OUTPUT);
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);

  Serial.begin(115200);

  delay(100); //Serial.println("LoRa TX Node");

  // manual reset
  digitalWrite(RFM95_RST, LOW);  delay(10);
  digitalWrite(RFM95_RST, HIGH); delay(10);

  while (!rf95.init()) { Serial.println("LoRa radio init failed"); while (1); }
  //Serial.println("LoRa radio init OK!");

  if (!rf95.setFrequency(RF95_FREQ)) { Serial.println("setFrequency failed"); while (1);}
  //Serial.print("Set Freq to: "); Serial.println(RF95_FREQ);
  
  // you can set transmitter powers from 5 to 23 dBm:
  rf95.setTxPower(23, false);
  
  rf95.setSpreadingFactor(12);
  rf95.setSignalBandwidth(125000);
  rf95.setCodingRate4(8);

  /*
  //Different Combination for distance and speed examples: 
  Example 1: Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on. Default medium range
    rf95.setSignalBandwidth(125000);
    rf95.setCodingRate4(5);
    rf95.setSpreadingFactor(7);
  Example 2: Bw = 500 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on. Fast+short range
    rf95.setSignalBandwidth(500000);
    rf95.setCodingRate4(5);
    rf95.setSpreadingFactor(7);
  Example 3: Bw = 31.25 kHz, Cr = 4/8, Sf = 512chips/symbol, CRC on. Slow+long range
    rf95.setSignalBandwidth(31250);
    rf95.setCodingRate4(8);
    rf95.setSpreadingFactor(9);
  Example 4: Bw = 125 kHz, Cr = 4/8, Sf = 4096chips/symbol, CRC on. Slow+long range
    rf95.setSignalBandwidth(125000);
    rf95.setCodingRate4(8);
    rf95.setSpreadingFactor(12); 
  */

}

int16_t packetnum = 0;  // packet counter, we increment per transmission

void loop()
{
                  unsigned long currentMillis = millis();
                              if (currentMillis - ping_previousMillis >= ping_interval){
                                                                  send_mode(1);
                                                                  ping_previousMillis = millis();
                                                                  packetnum++;
                              }
}


void send_mode(int x){
                            char buffer[80];
                            byte sendLen;
                            memset(buffer, '\0', sizeof(buffer));
  
                          if (x == 1){
                                          sprintf(buffer, "#,1A,Z,%i,#", packetnum);
                                            // Packet sent will be '#,1A,Z,0,#', '#,1A,Z,1,#', '#,1A,Z,2,#' etc, etc.
                                          sendLen = strlen(buffer);
  
                                          Serial.print(" Sending ... "); Serial.print(buffer); 
                                          digitalWrite(LED, HIGH); // Turns on LED
                                            rf95.send(buffer, sendLen);
                                            rf95.waitPacketSent();
                                          digitalWrite(LED, LOW);  // Turns off LED
                                          Serial.println(" - Done");
                                          delay(10);
                          }
}
