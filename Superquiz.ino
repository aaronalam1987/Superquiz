#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd (0x27, 20, 4); //Define 20x4 LCD
LiquidCrystal_I2C lcd2 (0x26, 16, 2); //Define 16x2 LCD

int buttonPressed = 0; //int for which button is pressed.
int welcome = 0; //Set welcome to 0 to display welcome message.
int questionNum = 0; //Define question number.
int totalQuestions = 10; //Set question amount.
int score = 0; //Keep score.
int answer = 0;

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
void doEnd(){
 lcd.setCursor(0,0);
    lcd.print("Game over");
      lcd.setCursor(0,1);
        lcd.print("Your score is:");
          lcd.setCursor(0,2);
            lcd.print(score);
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

const char * const welcomeMess[9] PROGMEM = { "Welcome to", "Superquiz", "press any button", "to continue.", "Ready", "to", "play", "?", 1 };
const char * const gameEnd[3] PROGMEM = { "Game Over", "Your score is:", 1 };
const char * const Q1[9] PROGMEM = { "How many", "seasons of", "Friends", "where there?", "1", "4", "6", "10", 4 };
const char * const Q2[9] PROGMEM = { "Who pees on", "Monica after", "she is stung", "by a jelly fish?", "Chandler", "Rachel", "Joey", "Pheobe", 3 };
const char * const Q3[9] PROGMEM = { "Ross says whos", "name at the altar", "in london?", "", "Rachel", "Pheobe", "Monica", "Emily", 1 };
const char * const Q4[9] PROGMEM = { "How many sisters", "does joey have?", "", "", "5", "7", "2", "0", 2 };
const char * const Q5[9] PROGMEM = { "What is the name of", "Joeys character in", "the commercial for", "opening milk carton", "Mike", "Tommy", "Kevin", "Drake", 3 };
const char * const Q6[9] PROGMEM = { "What instrument did", "Ross intend to play", "at Monica and", "Chandlers Wedding?", "Bagpipe", "Drums", "Guitar", "Sax", 1 };
const char * const Q7[9] PROGMEM = { "What is Chandlers", "middle name?", "", "", "Nora", "Muriel", "Charles", "Francis", 2 };
const char * const Q8[9] PROGMEM = { "Who was", "Monicas first kiss?", "", "", "Chandler", "Pete", "Ross", "Richard", 3 };
const char * const Q9[9] PROGMEM = { "Chick Jr and Duck Jr", "get stuck in what?", "", "", "Toilet", "Foosball", "Bin", "Fridge", 2 }; 
const char * const Q10[9] PROGMEM = { "Who", "famously said", "PIVOT?", "", "Rachel", "Joey", "Monica", "Ross", 4 };

void doButtons(){
  if(buttonPressed > 0 & welcome==0){ //If any button pressed.
      welcome=1; //Set welcome to 1 to show we have passed this stage.
      questionNum++; //Set first question
      lcd.clear(); //Clear lcd one.
      lcd2.clear(); //Clear lcd two.
      buttonPressed=0; //Reset button press.
      delay(1000); //Delay for one second.
  }
 else{
  if(buttonPressed > 0){ //As we reset button to 0, make sure it is more than 0.
        if(buttonPressed==answer){ 
            doAnswer(1); //Call answerCorrect function.  
        }
        else{
           doAnswer(0);        
        }
  }
 }
  
}

void loop() {
  if(welcome==0){ //Display welcome message.
    doDisplay(welcomeMess[0], welcomeMess[1], welcomeMess[2], welcomeMess[3], welcomeMess[4], welcomeMess[5], welcomeMess[6], welcomeMess[7]);
    doButtons();
  }
  else{
    if(questionNum > totalQuestions){ //Check which question is active and display it.
      doEnd();
    }
    if(questionNum==1){ //Check which question is active and display it.
      doDisplay(Q1[0], Q1[1], Q1[2], Q1[3], Q1[4], Q1[5], Q1[6], Q1[7]);
      answer = Q1[8];
      doButtons();
    }
    if(questionNum==2){
      doDisplay(Q2[0], Q2[1], Q2[2], Q2[3], Q2[4], Q2[5], Q2[6], Q2[7]);
      answer = Q2[8];
      doButtons();
    }
    if(questionNum==3){
      doDisplay(Q3[0], Q3[1], Q3[2], Q3[3], Q3[4], Q3[5], Q3[6], Q3[7]);
      answer = Q3[8];
      doButtons();
    }
    if(questionNum==4){
      doDisplay(Q4[0], Q4[1], Q4[2], Q4[3], Q4[4], Q4[5], Q4[6], Q4[7]);
      answer = Q4[8];
      doButtons();
    }
    if(questionNum==5){
      doDisplay(Q5[0], Q5[1], Q5[2], Q5[3], Q5[4], Q5[5], Q5[6], Q5[7]);
      answer = Q5[8];
      doButtons();
    }
    if(questionNum==6){
      doDisplay(Q6[0], Q6[1], Q6[2], Q6[3], Q6[4], Q6[5], Q6[6], Q6[7]);
      answer = Q6[8];
      doButtons();
    }
    if(questionNum==7){
      doDisplay(Q7[0], Q7[1], Q7[2], Q7[3], Q7[4], Q7[5], Q7[6], Q7[7]);
      answer = Q7[8];
      doButtons();
    }
    if(questionNum==8){
      doDisplay(Q8[0], Q8[1], Q8[2], Q8[3], Q8[4], Q8[5], Q8[6], Q8[7]);
      answer = Q8[8];
      doButtons();
    }
    if(questionNum==9){
      doDisplay(Q9[0], Q9[1], Q9[2], Q9[3], Q9[4], Q9[5], Q9[6], Q9[7]);
      answer = Q9[8];
      doButtons();
    }
    if(questionNum==10){
      doDisplay(Q10[0], Q10[1], Q10[2], Q10[3], Q10[4], Q10[5], Q10[6], Q10[7]);
      answer = Q10[8];
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
