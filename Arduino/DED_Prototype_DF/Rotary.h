void updateSmallRotaryEncoder() {

  smallRotACurrent = digitalRead(smallRotA);

  if ((smallRotALast == LOW) && (smallRotACurrent == HIGH)) {
    if (digitalRead(smallRotB)) {
      //      Serial.println("Left");
      smallValue--;
    }
    else {
      //      Serial.println("Right");
      smallValue++;
    }
  }

  smallRotALast = smallRotACurrent;

  sendDataOut = true;
}

void smallRotButtonPressed() {
  smallRotPressed = true;

  sendDataOut = true;
}


void updateBigRotaryEncoder() {

  bigRotACurrent = digitalRead(bigRotA);

  if ((bigRotALast == LOW) && (bigRotACurrent == HIGH)) {
    if (digitalRead(bigRotB)) {
      bigValue--;
      //      Serial.println("B Left");
    }
    else {
      bigValue++;
      //      Serial.println("B Right");
    }
  }

  bigRotALast = bigRotACurrent;

  sendDataOut = true;
}

void bigRotButtonPressed() {
  bigRotPressed = true;

  sendDataOut = true;
}
