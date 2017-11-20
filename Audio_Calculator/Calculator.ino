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
int t = 200; //delay time in millisdeconds
int part = 0;
int const noteH = 440; //this is the frequency of the high note (counting)
int const noteL = 262; //this is the frequency of the low note (error)  
int const noteDur1 = 150; //this is the duration of the counting note (NoteH)
int const noteDur2 = 400; //this is the duration of the error note (NoteL)
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

void printN(){ //this function prints out the values of the Numbers at each part of the calculation
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

void RGBoff(){//this function turns off all of the lights in the RGB Led after the function is complete
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW); 
}

void loop() {
  int i, button1State, button2State;
  unsigned long currentMillis = millis();//this reads how long the code has been running for in milliseconds
  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);

  if (Result > 30){//this is a test to see if the result is less than 30, if it is higher than 30 an error note is played and the loop is exited
  tone (buzzerPin,noteL,noteDur2);
  i = Result = 1;
 }
  if (part == 0){ //this is where the first number is inputted
    digitalWrite(ledPinY, HIGH);//yellow light is turned on to signify part 1
    digitalWrite(ledPinR, LOW);
    if (button1State == LOW){ //each time the button is pressed, the first number increases by one
      Number1 = Number1 + 1;
      delay(t);
      
    }
  }

  if (part == 1){ //this is where the second number is inputted
    digitalWrite(ledPinY, LOW);
    digitalWrite(ledPinR, HIGH);//Red light is turned on to signify part 2
    if (button1State == LOW){ //each time the button is pressed, the second number increases by one
      Number2 = Number2 + 1;
      delay(t);
    }
  }

  if (part == 2){
    digitalWrite(ledPinY, HIGH);
    digitalWrite(ledPinR, HIGH);//Both lights are turned on to signify part 3
    Result = Number1 + Number2;//the result is then counted
    for(i = 0; i < Result; i++){//the result is then played through the buzzer in intervals of 300ms
      if (i < 11){//for numbers less than 11, a blue light is shown 
        digitalWrite(RED_PIN, LOW);
        digitalWrite(GREEN_PIN, LOW);
        digitalWrite(BLUE_PIN, HIGH);
        tone(buzzerPin,noteH,noteDur1);
        delay(300);
        RGBoff();
      }

      if (i > 10 and i < 21){//for numbers between 11 and 20, a green light is shown
        digitalWrite(RED_PIN, LOW);
        digitalWrite(GREEN_PIN, HIGH);
        digitalWrite(BLUE_PIN, LOW);
        tone(buzzerPin,noteH,noteDur1);
        delay(300);
        RGBoff();
      }
      if (i > 20 and i <31){//for numbers between 21 and 30, a red light is shown
        digitalWrite(RED_PIN, HIGH);
        digitalWrite(GREEN_PIN, LOW);
        digitalWrite(BLUE_PIN, LOW);
        tone(buzzerPin,noteH,noteDur1);
        delay(300);
        RGBoff();
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


