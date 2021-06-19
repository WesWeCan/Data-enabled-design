// Script to test all the logic. Pre-contextual step.

int pin = 35;

int smallValue = 0;
int smallRotA = 19;
int smallRotB = 23;
int smallRotBtn = 21;

int smallRotACurrent = LOW;
int smallRotALast = smallRotACurrent;

int bigValue = 0;
int bigRotA = 12;
int bigRotB = 14;
int bigRotBtn = 22;

int bigRotACurrent = LOW;
int bigRotALast = bigRotACurrent;

int mood_btn_1 = 2;
int mood_btn_2 = 4;
int mood_btn_3 = 16;
int mood_btn_4 = 17;

int yellow_slider = 33;
int black_slider = 34;

unsigned long previousMillis = 0;
const long interval = 1000;

void setup()
{
  // put your setup code here, to run once:

  Serial.begin(115200);

  pinMode(pin, INPUT);
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

  // Calibrate
  delay(2000);

  attachInterrupt(digitalPinToInterrupt(pin), passedBy, RISING);

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

void loop()
{

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval)
  {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    Serial.println(map(analogRead(yellow_slider), 0, 1024, 100, 0));
  }
}

void passedBy()
{
  Serial.println("PIR Activated");
}

void updateSmallRotaryEncoder()
{

  smallRotACurrent = digitalRead(smallRotA);

  if ((smallRotALast == LOW) && (smallRotACurrent == HIGH))
  {
    if (digitalRead(smallRotB))
    {
      //      Serial.println("Left");
      smallValue--;
    }
    else
    {
      //      Serial.println("Right");
      smallValue++;
    }
  }

  smallRotALast = smallRotACurrent;
}

void smallRotButtonPressed()
{
  Serial.println("Small Rot Pressed");
  delay(500);
}

void updateBigRotaryEncoder()
{

  bigRotACurrent = digitalRead(bigRotA);

  if ((bigRotALast == LOW) && (bigRotACurrent == HIGH))
  {
    if (digitalRead(bigRotB))
    {
      bigValue--;
      //      Serial.println("B Left");
    }
    else
    {
      bigValue++;
      //      Serial.println("B Right");
    }
  }

  bigRotALast = bigRotACurrent;
}

void bigRotButtonPressed()
{
  Serial.println("Big Rot Pressed");
  delay(500);
}

void mood_1()
{
  Serial.println("mood_1");
}

void mood_2()
{
  Serial.println("mood_2");
}

void mood_3()
{
  Serial.println("mood_3");
}

void mood_4()
{
  Serial.println("mood_4");
}
