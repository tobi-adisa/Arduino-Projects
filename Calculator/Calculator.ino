const int RED_PIN = 13;
const int GREEN_PIN = 12;
const int BLUE_PIN = 11;
const int button1Pin = 2;
const int button2Pin = 3;
const int ledPinY = 7;
const int ledPinR = 6;
const int buzzerPin = 9;
int Number1 = 0;
int Number2 = 0;
int Result;
int t = 200;
int part = 0;
int const noteH = 440;
int const noteL = 262;
int const noteDur1 = 150;
int const noteDur2 = 400;
unsigned long previousMillis = 0;
const long interval = 1000;
void setup() {
  Serial.begin(9600);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(ledPinY, OUTPUT);
  pinMode(ledPinR, OUTPUT);
  pinMode(buzzerPin,OUTPUT);
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
}

void printN(){
  Serial.print("part ");
  Serial.println(part);
  Serial.print("Number1 ");
  Serial.println(Number1);
  Serial.print("Number2 ");
  Serial.println(Number2);
  Serial.print("Result ");
  Serial.println(Result);
  Serial.println("-------");
}

void RGBoff(){
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW); 
}

void loop() {
  int i, button1State, button2State;
  unsigned long currentMillis = millis();
  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);

  if (part == 0){
    digitalWrite(ledPinY, HIGH);
    digitalWrite(ledPinR, LOW);
    if (button1State == LOW){
      Number1 = Number1 + 1;
      delay(t);
      
    }
  }

  if (part == 1){
    digitalWrite(ledPinY, LOW);
    digitalWrite(ledPinR, HIGH);
    if (button1State == LOW){
      Number2 = Number2 + 1;
      delay(t);
    }
  }

  if (part == 2){
    digitalWrite(ledPinY, HIGH);
    digitalWrite(ledPinR, HIGH);
    Result = Number1 + Number2;
    for(i = 0; i < Result; i++){
      if (i < 11){
        digitalWrite(RED_PIN, LOW);
        digitalWrite(GREEN_PIN, LOW);
        digitalWrite(BLUE_PIN, HIGH);
        tone(buzzerPin,noteH,noteDur1);
        delay(300);
        RGBoff();
      }

      if (i > 10 and i < 21){
        digitalWrite(RED_PIN, LOW);
        digitalWrite(GREEN_PIN, HIGH);
        digitalWrite(BLUE_PIN, LOW);
        tone(buzzerPin,noteH,noteDur1);
        delay(300);
        RGBoff();
      }
      if (i > 20 and i <31){
        digitalWrite(RED_PIN, HIGH);
        digitalWrite(GREEN_PIN, LOW);
        digitalWrite(BLUE_PIN, LOW);
        tone(buzzerPin,noteH,noteDur1);
        delay(300);
        RGBoff();
      }
      if (Result > 30){
        tone (buzzerPin,noteL,noteDur2);
        i = Result = 1;
      }
    }
    part = 0;
    Number1 = 0;
    Number2 = 0;
    Result = 0;
  }

  if (button2State == LOW){
    part = part + 1;
    delay(t);
  }
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    printN();

  }
}


