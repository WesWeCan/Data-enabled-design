

void sendDataToOocsi() {

Serial.print(currentMood);
Serial.println("send");
  
  // create a new message
  oocsi.newMessage("2021_DED_MOOD_11_B");

  // add data (primitive data types int, float, long, string)
  // the labels such as "count" or "timestamp" are completely free to choose

  oocsi.addInt("lastMood", currentMood);
  oocsi.addInt("smallRotary", smallValue);
  oocsi.addInt("bigRotary", bigValue);
  oocsi.addInt("yellowSlider", yellowValue);
  oocsi.addInt("blackSlider", blackValue);
  oocsi.addBool("smallRotP", smallRotPressed);
  oocsi.addBool("bigRotP", bigRotPressed);
  oocsi.addBool("PIRDetected", PIRDetected);
  oocsi.addLong("programTime", (long) millis());

  // this command will send the message; don't forget to call this after creating a message
  oocsi.sendMessage();

  // prints out the raw message (how it is sent to the OOCSI server)
  // oocsi.printSendMessage();

  // needs to be checked in order for OOCSI to process incoming data.
  oocsi.check();

  bigRotPressed = false;
  smallRotPressed = false;
  PIRDetected = false;

}
