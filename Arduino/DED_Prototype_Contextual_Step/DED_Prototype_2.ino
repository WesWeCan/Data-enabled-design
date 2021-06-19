/*

  Data-enabled Desing
  Prototype for Data Foundry deployment 1 - Contextual Step

  Data Foundry (https://data.id.tue.nl)

*/

/* LIBS */

//#include "DFDataset.h" // https://github.com/iddi/oocsi-esp -> examples -> DataFoundry
#include "secrets.h"

#include <WiFi.h>      // https://github.com/iddi/oocsi-esp -> examples -> extras
#include <WiFiMulti.h> // https://github.com/iddi/oocsi-esp -> examples -> extras

int LED = 5;
int yellow_slider = 33;
int black_slider = 34;

int yellowValue = -1;
int blackValue = -1;

int diff = 0;
int diff2 = 0;
int pBlackValue = blackValue;
int pYellowValue = yellowValue;

unsigned long previousMillis = 0;
const long interval = ((1000 * 60) * 15);

bool sendDataOut = false;

int isTesting = false;

int PIRPin = 35;
bool PIRDetected = false;

#include "_oocsi.h" // https://github.com/iddi/oocsi-esp
#include "PIR.h"

WiFiMulti wifiMulti;

void setup()
{
  Serial.begin(115200);
  delay(10);

  wifiMulti.addAP(ssid, password);
  wifiMulti.addAP("Dickie’s Home", "bc706706");

  // output OOCSI activity on the built-in LED
  pinMode(5, OUTPUT);
  oocsi.setActivityLEDPin(5);

  if (wifiMulti.run() == WL_CONNECTED)
  {
    // establish Wifi connection
    oocsi.connect(OOCSIName, hostserver, ssid, password);
  }

  setupPir();

  analogReadResolution(10); // 10 = 0-1024
}

void loop()
{
  yellowValue = analogRead(yellow_slider);
  blackValue = analogRead(black_slider);

  diff = blackValue - pBlackValue;
  if (abs(diff) >= 3)
  {
    sendDataToOocsi();
  }

  diff2 = yellowValue - pYellowValue;
  if (abs(diff2) >= 3)
  {
    sendDataToOocsi();
  }

  pBlackValue = blackValue;
  pYellowValue = yellowValue;

  delay(500);
}
