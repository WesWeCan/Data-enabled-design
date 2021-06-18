#include "OOCSI.h"
OOCSI oocsi = OOCSI();

//// put the adress of Data Foundry here
//const char* datafoundry = "data.id.tue.nl";
//
//// create connection to dataset with server address, dataset id, and the access token
//DFDataset iot(datafoundry, DATASETID, DATASETTOKEN);


void sendDataToOocsi() {

  oocsi.newMessage("2021_DED_MOOD_11_PROT_2");
  oocsi.addString("device_id", "da3769abf25ac46df");
  oocsi.addString("activity", "ACTIVITY");
  oocsi.addInt("PIR", PIRDetected);
  oocsi.addInt("black", blackValue);
  oocsi.addInt("yellow", yellowValue);
  oocsi.addInt("isTesting", isTesting);
  oocsi.sendMessage();

  PIRDetected = false;

  Serial.println("oocsi");

}
