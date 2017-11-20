
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
const int button1Pin = 6;
const int button2Pin = 7;
int Operand = 0;
int Number1 = 0;
int Number2 = 0;
float Result;
int t = 200; //delay time in millisdeconds
int part = 0;
int j = 0, k = 0, l = 0, m = 0;
unsigned long previousMillis = 0;
const long interval = 1000;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);

}
void printN(){ //this function prints out the values of the Numbers at each part of the calculation
  Serial.print("part ");
  Serial.println(part);
  Serial.print("Number1 ");
  Serial.println(Number1);
  Serial.print("Number2 ");
  Serial.println(Number2);
  Serial.print("operand ");
  Serial.println(Operand);  
  Serial.print("Result ");
  Serial.println(Result);
  Serial.println("-------");
}
void loop() {
  int i, button1State, button2State;
  unsigned long currentMillis = millis();//this reads how long the code has been running for in milliseconds
  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);
   if (button2State == LOW){
    part = part + 1;
    delay(t);
  }
  if (part > 3){
    part = 0;
    Number1 = 0;
    Number2 = 0;
    j = 0;
    k = 0;
    l = 0;
    m = 0;
  }
  if (part == 0){ //this is where the first number is inputted
    lcd.setCursor(0,0);
    if ( j < 1){
      lcd.clear();    
      lcd.print("Input Value 1: ");
      j = 1;
    }
    if (button1State == LOW){ //each time the button is pressed, the first number increases by one
      Number1 = Number1 + 1;
      delay(t); 
    }
    lcd.setCursor(0,1);
    lcd.print(Number1);
  }

  if (part == 1){ //this is where the second number is inputted
    lcd.setCursor(0,0);
    if ( k < 1){
      lcd.clear();
      lcd.print("Input Value 2: ");
      k = 1;
    }
    if (button1State == LOW){ //each time the button is pressed, the second number increases by one
      Number2 = Number2 + 1;
      delay(t);
    }
    lcd.setCursor(0,1);
    lcd.print(Number2);
  }

  if (part == 2){ //this is where the arithmetic operand is decided
    lcd.setCursor(0,0);
    if ( l < 1){
      lcd.clear();
      lcd.print("Operation: ");
      l = 1;
    }
    if (button1State == LOW){
      Operand = Operand + 1;
      delay(t);
    }
    if (Operand == 0){
      lcd.setCursor(0,1);
      lcd.print("+");
    }
    if (Operand == 1){
      lcd.setCursor(0,1);
      lcd.print("-");
    }
    if (Operand == 2){
      lcd.setCursor(0,1);
      lcd.print("*");
    }
    if (Operand == 3){
      lcd.setCursor(0,1);
      lcd.print("/");
    }
    if (Operand > 3){
      Operand = 0;
    }
  }
  if (part == 3){
    lcd.setCursor(0,0);
    if ( m < 1){
      lcd.clear();
      lcd.print("Result: ");
      m = 1;
    }
  
    if (Operand == 0){
      Result = Number1 + Number2;
      lcd.setCursor(0,1);
      lcd.print(Result);
    }
    if (Operand == 1){
      Result = Number1 - Number2;
      lcd.setCursor(0,1);
      lcd.print(Result);
    }
    if (Operand == 2){
      Result = Number1 * Number2;
      lcd.setCursor(0,1);
      lcd.print(Result);
    }
    if (Operand == 3){
      Result = (double) Number1 / Number2;
      lcd.setCursor(0,1);
      lcd.print(Result);
    }
  }


  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    printN();
  }
}

