#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd (0x27, 20, 4); //Define 20x4 LCD
LiquidCrystal_I2C lcd2 (0x26, 16, 2); //Define 16x2 LCD

int buttonPressed = 0; //int for which button is pressed.
int welcome = 0; //Set welcome to 0 to display welcome message.
int questionNum = 0; //Define question number.
int maxQuestion = 10;
int score = 0; //Keep score.

void setup() {
//Define button pins.
  pinMode(8, INPUT_PULLUP);
    pinMode(9, INPUT_PULLUP);
      pinMode(10, INPUT_PULLUP);
        pinMode(11, INPUT_PULLUP);

//Start serial
  Serial.begin(9600);

//Initalise both lcd screens.
    lcd.init();
      lcd.backlight();
        lcd2.init();
          lcd2.backlight();

}

//Function for displaying on lcds.
void doDisplay(String L1, String L2, String L3, String L4, String L5, String L6, String L7, String L8){
  lcd.setCursor(0,0);
    lcd.print(L1);
      lcd.setCursor(0,1);
        lcd.print(L2);
          lcd.setCursor(0,2);
            lcd.print(L3);
              lcd.setCursor(0,3);
                lcd.print(L4);
  lcd2.setCursor(0, 0);
    lcd2.print(L5);
      lcd2.setCursor(7, 0);
        lcd2.print(L6);
          lcd2.setCursor(0, 1);
            lcd2.print(L7);
              lcd2.setCursor(7, 1);
                lcd2.print(L8);
            
}

//Function for if answer is correct.
void doAnswer(int a){
      lcd.clear(); //Clear lcd one
        lcd2.clear(); //Clear lcd two
        lcd.setCursor(0,0);
        if(a==1){lcd.print("Correct answer!"); score++;}
            else{lcd.print("Wrong answer!");}
              lcd2.print("Next question"); //Print on lcd two
                lcd2.setCursor(0,1); //Set second row on lcd two.
                  lcd2.print("Coming up"); //Print on lcd two.
                      buttonPressed=0; //Reset stored button press value.
                        delay(3000); //Delay 3 seconds so use can read screen.
                          lcd.clear(); //Clear lcd one.
                            lcd2.clear(); //Clear lcd two.
                            questionNum++; //Move to next question.
}

//Similar to answerCorrect function but with different prints and without incrementing score.


//Question struct.
struct Question {
String line1; 
String line2;
String line3;
String line4;
String line5;
String line6;
String line7;
String line8;
int ANS; 
};

//Define question and answers, LCD one (line 1,2,3,4) LCD2 (line 1 (button 1), line 1.7 (button 2), line 2 (button 3), line 2.7 (button 4)) button tied to answer.
Question welcomeMess = {"Welcome to", "Superquiz", "Press any button", "to continue", "Ready", "to", "play", "?", 1}; 
Question Q1 = {"How many", "seasons of", "Friends", "were there?", "1", "4", "6", "9", 4};
Question Q2 = {"Who pees on", "monica", "after she is", "stung by a jelly fish?", "Chandler", "Rachel", "Joey", "Pheobe", 3};
Question Q3 = {"Ross says whos", "name at the altar", "in london?", "", "Rachel", "Pheobe", "Monica", "Emily", 1};



void doButtons(){
switch (questionNum){
  case 0:
  if(buttonPressed > 0){
      welcome=1; //Set welcome to 1 to show we have passed this stage.
      questionNum++; //Set first question
         lcd.clear(); //Clear lcd one.
          lcd2.clear(); //Clear lcd two.
            buttonPressed=0; //Reset button press.
              delay(1000); //Delay for one second.
    }
  case 1: 
  if(buttonPressed > 0){ //As we reset button to 0, make sure it is more than 0.
        if(buttonPressed==Q1.ANS){ 
            doAnswer(1); //Call answerCorrect function.  
        }
        else{
           doAnswer(0);        
        }
  }
  case 2:
  if(buttonPressed > 0){
        if(buttonPressed==Q2.ANS){
            doAnswer(1);       
        }
        else{
           doAnswer(0);
        }
  }
  case 3:
  if(buttonPressed > 0){
        if(buttonPressed==Q3.ANS){
            doAnswer(1); 
        }
        else{
           doAnswer(0);
        }
  }
}


}

void loop() {
  if(welcome==0){ //Display welcome message.
    doDisplay(welcomeMess.line1, welcomeMess.line2, welcomeMess.line3, welcomeMess.line4, welcomeMess.line5, welcomeMess.line6, welcomeMess.line7, welcomeMess.line8);
    doButtons();
  }
  else{
    if(questionNum==1){ //Check which question is active and display it.
      doDisplay(Q1.line1, Q1.line2, Q1.line3, Q1.line4, Q1.line5, Q1.line6, Q1.line7, Q1.line8);
      doButtons();
    }
    if(questionNum==2){
      doDisplay(Q2.line1, Q2.line2, Q2.line3, Q2.line4, Q2.line5, Q2.line6, Q2.line7, Q2.line8);
      doButtons();
    }
    if(questionNum==3){
      doDisplay(Q3.line1, Q3.line2, Q3.line3, Q3.line4, Q3.line5, Q3.line6, Q3.line7, Q3.line8);
      doButtons();
    }
  }

    //Read button inputs.
    int b1 = digitalRead(8); 
    int b2 = digitalRead(9);
    int b3 = digitalRead(10);
    int b4 = digitalRead(11);

    //Assign button inputs to an number, 1-4
    if(b1==0){buttonPressed=1;} 
      if(b2==0){buttonPressed=2;}
        if(b3==0){buttonPressed=3;}
          if(b4==0){buttonPressed=4;}

    //Call doButton function which checks button press compared to answer.
     

}
