const int sensorPin = A0; 
int reading;
float volts;
float millivolts;
float degreesC;    // temp in deg C for serial monitor
float degreesF;

const int led1 = 2;  // blue LED
const int led2 = 3;  // green LED
const int led3 = 5;  // red LED

const int thresh1 = 22;
const int thresh2 = 24;
const int thresh3 = 27;

const float aref_voltage = 1.07;

const int buttonPin = A2;
int buttonState = 0;
int lastButtonState = HIGH;  // using pullup, so starts high
bool systemOn = false;       // thermometer system on/off

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  pinMode(buttonPin, INPUT_PULLUP);
  analogReference(INTERNAL);  
  Serial.begin(9600);
}

void loop() {
  buttonState = digitalRead(buttonPin);

  // if button pressed, toggle system on/off
  if (buttonState == LOW && lastButtonState == HIGH) {
    systemOn = !systemOn;
    delay(200);  
  }
  lastButtonState = buttonState;

  if (systemOn) {
    reading = analogRead(sensorPin);
    volts = reading * aref_voltage / 1023.0;
    millivolts = volts * 1000;
    degreesC = (millivolts - 500) / 10;
    degreesF = (degreesC * 9 / 5) + 32;

    // decide which LED to light up based on temp
    if (degreesC >= thresh3) {
      digitalWrite(led3, HIGH);
      digitalWrite(led2, LOW);
      digitalWrite(led1, LOW);
    }
    else if (degreesC >= thresh2) {
      digitalWrite(led3, LOW);
      digitalWrite(led2, HIGH);
      digitalWrite(led1, LOW);
    }
    else if (degreesC >= thresh1) {
      digitalWrite(led3, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led1, HIGH);
    }
    else {
      digitalWrite(led3, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led1, LOW);
    }

    // print temp info to Serial Monitor
    Serial.print("ADC reading: ");
    Serial.print(reading);
    Serial.print(" , Volts: ");
    Serial.print(volts);
    Serial.print(" | mV: ");
    Serial.print(millivolts);
    Serial.print(" , °C: ");
    Serial.print(degreesC);
    Serial.print(" , °F: ");
    Serial.println(degreesF);
  }
  else {
    // turn off all LEDs if system off
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  }

  delay(500);  // pause before next loop
}


