/*

  Data-enabled Desing
  Prototype for Data Foundry testing

*/

/* LIBS */
#include "OOCSI.h" // https://github.com/iddi/oocsi-esp
#include "DFDataset.h" // https://github.com/iddi/oocsi-esp -> examples -> DataFoundry
#include "secrets.h"


#include "_variables.h"

#include "oocsi_.h"
#include "mood.h"

#include "PIR.h"
#include "Rotary.h"






void setup() {
    Serial.begin(115200);

  // output OOCSI activity on the built-in LED
  pinMode(LED, OUTPUT);

  // establish Wifi connection
  oocsi.connect(OOCSIName, hostserver, ssid, password);

  // you can also already set the device and activity here,
  // if they don't change throughout the program execution
  iot.device("ESP_DED");
  iot.activity("idle");

  pinMode(PIRPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(PIRPin), passedBy, RISING);

  pinMode(PIRPin, INPUT);
  pinMode(smallRotA, INPUT_PULLUP);
  pinMode(smallRotB, INPUT_PULLUP);
  pinMode(smallRotBtn, INPUT_PULLUP);

  pinMode(bigRotA, INPUT_PULLUP);
  pinMode(bigRotB, INPUT_PULLUP);
  pinMode(bigRotBtn, INPUT_PULLUP);

  pinMode(mood_btn_1, INPUT_PULLUP);
  pinMode(mood_btn_2, INPUT_PULLUP);
  pinMode(mood_btn_3, INPUT_PULLUP);
  pinMode(mood_btn_4, INPUT_PULLUP);


  // Calibrate PIR
  delay(2000);

  attachInterrupt(digitalPinToInterrupt(PIRPin), passedBy, RISING);

  attachInterrupt(digitalPinToInterrupt(smallRotA), updateSmallRotaryEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(smallRotBtn), smallRotButtonPressed, RISING);

  attachInterrupt(digitalPinToInterrupt(bigRotA), updateBigRotaryEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(bigRotBtn), bigRotButtonPressed, RISING);

  attachInterrupt(digitalPinToInterrupt(mood_btn_1), mood_1, RISING);
  attachInterrupt(digitalPinToInterrupt(mood_btn_2), mood_2, RISING);
  attachInterrupt(digitalPinToInterrupt(mood_btn_3), mood_3, RISING);
  attachInterrupt(digitalPinToInterrupt(mood_btn_4), mood_4, RISING);

  analogReadResolution(10); // 10 = 0-1024
}



void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    yellowValue = map(analogRead(yellow_slider), 0, 1024, 100, 0);
    blackValue = map(analogRead(black_slider), 0, 1024, 100, 0);

    sendDataToOocsi();
  }


  if (sendDataOut) {
    sendDataToOocsi();
    sendDataOut = false;
  }

}






// Blocks the program to connect to WiFI
void connectToWiFi() {
  WiFi.begin(ssid, password);
  //  Serial.println("Connecting to WiFi..");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    //    Serial.print('.');
  }

  digitalWrite(LED, HIGH);

  //  Serial.println("Connected to the WiFi network");
}
