#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd (0x27, 20, 4); //Define 20x4 LCD
LiquidCrystal_I2C lcd2 (0x26, 16, 2); //Define 16x2 LCD

int buttonPressed = 0; //int for which button is pressed.
int welcome = 0; //Set welcome to 0 to display welcome message.
int questionNum = 0; //Define question number.
int totalQuestions = 10; //Set question amount.
int score = 0; //Keep score.
int answer = 0;
int buzzer = 7; //Buzzer pin.

void setup() {
//Define buzzer.
  pinMode(buzzer, OUTPUT);
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
void doDisplay(String mainLCD, String A1, String A2, String A3, String A4){
//Split question string between total lines and print on appropriate line.
  int stringStart = 0;
  int stringEnd = 20;
  int lcdLine = 0;

  for(lcdLine; lcdLine <= 3; lcdLine++){
    String displayString = mainLCD.substring(stringStart, stringEnd);//Create substring from main string within 20 chars.
          lcd.setCursor(0,lcdLine); //Set lcd line to required line.
          lcd.print(displayString); //Print 20 char substring.
              stringStart = stringEnd; //New substring start position is string end.
              stringEnd = stringEnd+20; //Add 20 to stringEnd to start the next 20 chars.
                
  }
  //Set answer screen.
  lcd2.setCursor(0, 0);
  lcd2.print(A1);
    lcd2.setCursor(7, 0);
    lcd2.print(A2);
      lcd2.setCursor(0, 1);
      lcd2.print(A3);
          lcd2.setCursor(7, 1);
          lcd2.print(A4);
            
}

//Sound function.
void playSound(int doSound){
  switch (doSound){
    //Current answer sound.
    case 0:
    tone(buzzer,1000);    
    delay(200);
    tone(buzzer,500);    
    delay(200);
    tone(buzzer,1000);    
    delay(200);
    noTone(buzzer); 
    break;
    
    //Wrong answer sound.
    case 1:
    tone(buzzer,200);    
    delay(200);
    noTone(buzzer); 
    tone(buzzer,100);    
    delay(200);
    noTone(buzzer); 
    break;

    //Intro / gameover sound.
    case 2:
    tone(buzzer,1000);    
    delay(500);
    noTone(buzzer); 
    tone(buzzer,800);    
    delay(200);
    noTone(buzzer); 
    tone(buzzer,1000);    
    delay(200);
    noTone(buzzer);
    tone(buzzer,900);    
    delay(200);
    tone(buzzer,800);    
    delay(200);
    noTone(buzzer);
    break;
  }
}

//Function to run on end of game.
void doEnd(){
  lcd.setCursor(0,0);
  lcd.print("Game over");
    lcd.setCursor(0,1);
    lcd.print("Your score is:");
      lcd.setCursor(0,2);
      lcd.print(score);
        lcd.setCursor(0,3);
        lcd.print("Press any button.");
}


//Function for if answer is correct.
void doAnswer(int a){
      lcd.clear(); //Clear lcd one
      lcd2.clear(); //Clear lcd two
      lcd.setCursor(0,0);
        if(a==1){
          lcd.print("Correct answer!"); 
          score++; 
          playSound(0);
        }
          else{
            lcd.print("Wrong answer!"); 
            playSound(1);
            }
              lcd2.print("Next question"); //Print on lcd two
              lcd2.setCursor(0,1); //Set second row on lcd two.
              lcd2.print("Coming up"); //Print on lcd two.
              buttonPressed=0; //Reset stored button press value.
              delay(3000); //Delay 3 seconds so use can read screen.
              lcd.clear(); //Clear lcd one.
              lcd2.clear(); //Clear lcd two.
              questionNum++; //Move to next question.
}

const char * const welcomeMess[6] PROGMEM = { "Welcome to Superquiz! Press any button to continue.", "Ready", "to", "play", "?", 1 };
const char * const gameEnd[3] PROGMEM = { "Game Over", "Your score is:", 1 };
const char * const Q1[6] PROGMEM = { "How many seasons of Friends where there?", "1", "4", "6", "10", 4 };
const char * const Q2[6] PROGMEM = { "Who pees on Monica after she is stung by a jelly fish?", "Chandler", "Rachel", "Joey", "Pheobe", 3 };
const char * const Q3[6] PROGMEM = { "Ross says whos name at the altar in london?", "Rachel", "Pheobe", "Monica", "Emily", 1 };
const char * const Q4[6] PROGMEM = { "How many sisters does joey have?", "5", "7", "2", "0", 2 };
const char * const Q5[6] PROGMEM = { "What is the name of Joeys character in the commercial for opening milk carton", "Mike", "Tommy", "Kevin", "Drake", 3 };
const char * const Q6[6] PROGMEM = { "What instrument did Ross intend to play at Monica and Chandlers Wedding?", "Bagpipe", "Drums", "Guitar", "Sax", 1 };
const char * const Q7[6] PROGMEM = { "What is Chandlers middle name?", "Nora", "Muriel", "Charles", "Francis", 2 };
const char * const Q8[6] PROGMEM = { "Who was Monicas first kiss?", "Chandler", "Pete", "Ross", "Richard", 3 };
const char * const Q9[6] PROGMEM = { "Chick Jr and Duck Jr get stuck in what?", "Toilet", "Foosball", "Bin", "Fridge", 2 }; 
const char * const Q10[6] PROGMEM = { "Who famously said PIVOT?", "Rachel", "Joey", "Monica", "Ross", 4 };

void doButtons(){
  if(buttonPressed > 0 & welcome==0){ //If any button pressed.
  playSound(2);
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
  if(questionNum > totalQuestions){ //Check which question is active and display it.
      doEnd();
  }
  else{
    switch (questionNum){
      case 0:
          doDisplay(welcomeMess[0], welcomeMess[1], welcomeMess[2], welcomeMess[3], welcomeMess[4]);
          answer = welcomeMess[5];
          break;
    case 1:
          doDisplay(Q1[0], Q1[1], Q1[2], Q1[3], Q1[4]);
          answer = Q1[5];
          break;
    case 2:
          doDisplay(Q2[0], Q2[1], Q2[2], Q2[3], Q2[4]);
          answer = Q2[5];
          break;
    case 3:
          doDisplay(Q3[0], Q3[1], Q3[2], Q3[3], Q3[4]);
          answer = Q3[5];
          break;      
    case 4:
          doDisplay(Q4[0], Q4[1], Q4[2], Q4[3], Q4[4]);
          answer = Q4[5];
          break;      
    case 5:
          doDisplay(Q5[0], Q5[1], Q5[2], Q5[3], Q5[4]);
          answer = Q5[5];
          break;      
    case 6:
          doDisplay(Q6[0], Q6[1], Q6[2], Q6[3], Q6[4]);
          answer = Q6[5];
          break;      
    case 7:
          doDisplay(Q7[0], Q7[1], Q7[2], Q7[3], Q7[4]);
          answer = Q7[5];
          break;      
    case 8:
          doDisplay(Q8[0], Q8[1], Q8[2], Q8[3], Q8[4]);
          answer = Q8[5];
          break;      
    case 9:
          doDisplay(Q9[0], Q9[1], Q9[2], Q9[3], Q9[4]);
          answer = Q9[5];
          break;      
    case 10:
          doDisplay(Q10[0], Q10[1], Q10[2], Q10[3], Q10[4]);
          answer = Q10[5];
          break;           
          
    
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
doButtons();
    //Call doButton function which checks button press compared to answer.
     

}
