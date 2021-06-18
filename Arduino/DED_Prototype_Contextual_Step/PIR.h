void passedBy() {
  PIRDetected = true;
  Serial.println("PIR");
//  sendDataToOocsi();
}

void setupPir(){
  pinMode(PIRPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(PIRPin), passedBy, RISING);
  
  // Calibrate PIR
  delay(2000);
 
}
