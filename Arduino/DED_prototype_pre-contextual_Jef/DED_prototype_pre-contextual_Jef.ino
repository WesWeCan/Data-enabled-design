/*********************************************************************
   Example of the ESP connecting to WiFi and accessing items in an
   Entity dataset on the Data Foundry.
   This works only with an existing account, project and dataset on
   the Data Foundry (https://data.id.tue.nl)
 *********************************************************************/

#include "DFDataset.h" // https://github.com/iddi/oocsi-esp -> examples -> DataFoundry
#include "time.h"

// SSID of your Wifi network, the library currently does not support WPA2 Enterprise networks
const char *ssid = "SSID";
//const char* ssid = "@Home Network";
// Password of your Wifi network.
const char *password = "PASSSWORD";
// put the adress of Data Foundry here
const char *datafoundry = "data.id.tue.nl";

// create connection to dataset with server address, dataset id, and the access token
DFDataset iot(datafoundry, 9999, "TOKEN");

//Pins & associated values (use pin addresses as written on ESP!)
int pot1 = 32; //Pin for the potentiometer 1 to connect to
int pot2 = 33; //Pin for the potentiometer 2 to connect to
int btn1 = 34; //Pin for button 1 to connect to
int btn2 = 35; //Pin for button 2 to connect to
int pir = 25;
int pirVal;
int prevPirVal;
int prevPot1Val = 0;
int pot1Val = 0;
int prevPot2Val = 0;
int pot2Val = 0;
//float potValTemp;
int prevbtn1Val;
int btn1Val;
int prevbtn2Val;
int btn2Val;
String timestamp;

const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 3600;

void setup()
{
  Serial.begin(115200);

  // establish Wifi connection
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi..");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print('.');
  }

  Serial.println("Connected to the WiFi network");

  // you can also already set the device and activity here,
  // if they don't change throughout the program execution
  iot.device("2_btns_2_pots");
  iot.activity("measuring");

  //get accurate time
  //  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  //  printLocalTime();

  //Initiate pins
  pinMode(pot1, INPUT);
  pinMode(pot2, INPUT);
  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
  pinMode(pir, INPUT);

  // ESP doesn't like interrupts...
  //  attachInterrupt(digitalPinToInterrupt(btn1), button_one, CHANGE);
  //  attachInterrupt(digitalPinToInterrupt(btn2), button_two, CHANGE);

  prevPot1Val = analogRead(pot1) / 400;
  prevPot2Val = analogRead(pot2) / 400;
  prevbtn1Val = digitalRead(btn1);
  prevbtn2Val = digitalRead(btn2);
  prevPirVal = digitalRead(pir);
  //  Serial.print("Starting values - ");
  //  printVal(prevPotVal, prevbtn1Val, prevbtn2Val);
}

void loop()
{
  interrupt_pot();
  interrupt_button();
  interrupt_pir();
}

void interrupt_pir()
{
  pirVal = digitalRead(pir);
  if (pirVal != prevPirVal)
  {
    Serial.print("PIR: ");
    Serial.println(pirVal);
    prevPirVal = pirVal;

    //Send data to Data Foundry
    iot.addInt("PIR", pirVal);
    iot.logItem();
    //    delay(50);
  }
}

void interrupt_pot()
{
  pot1Val = analogRead(pot1);
  pot2Val = analogRead(pot2);

  if (abs(pot1Val - prevPot1Val) > 100)
  {
    Serial.println(pot1Val);
    prevPot1Val = pot1Val;

    //Send data to Data Foundry
    iot.addInt("potentiometer_1", pot1Val);
    iot.logItem();
    //    delay(50);
  }

  if (abs(pot2Val - prevPot2Val) > 100)
  {
    Serial.println(pot2Val);
    prevPot2Val = pot2Val;

    //Send data to Data Foundry
    iot.addInt("potentiometer_2", pot2Val);
    iot.logItem();
    //    delay(50);
  }
}

void interrupt_button()
{
  btn1Val = digitalRead(btn1);
  btn2Val = digitalRead(btn2);

  if (btn1Val != prevbtn1Val || btn2Val != prevbtn2Val)
  {
    static unsigned long last_interrupt_time = 0;
    unsigned long interrupt_time = millis();
    // If interrupts come faster than 200ms, assume it's a bounce and ignore
    if (interrupt_time - last_interrupt_time > 100)
    {
      if (btn1Val != prevbtn1Val)
      {
        Serial.print("Button one state: ");
        Serial.println(btn1Val);

        //Send data to Data Foundry
        iot.addInt("button_1", btn1Val);
        iot.logItem();

        prevbtn1Val = btn1Val;
      }
      if (btn2Val != prevbtn2Val)
      {
        Serial.print("Button two state: ");
        Serial.println(btn2Val);

        //Send data to Data Foundry
        iot.addInt("button_2", btn2Val);
        iot.logItem();

        prevbtn2Val = btn2Val;
      }
    }
    last_interrupt_time = interrupt_time;
  }
}

//void printLocalTime()
//{
//  struct tm timeinfo;
//  if (!getLocalTime(&timeinfo)) {
//    Serial.println("Failed to obtain time");
//    return;
//  }
//  char timeString[50];
//  strftime(timeString, sizeof(timeString), "%A, %B %d %Y %H:%M:%S", &timeinfo);
//  //  Serial.println(timeString);
//  //  timestamp = "";
//  //  timestamp = String(timestamp + timeString);
//  Serial.println(timeString);
//}
