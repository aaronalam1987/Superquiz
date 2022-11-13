#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd (0x27, 20, 4); //Define 20x4 LCD
LiquidCrystal_I2C lcd2 (0x26, 16, 2); //Define 16x2 LCD

int buttonPressed = 0; //int for which button is pressed.
int welcome = 0; //Set welcome to 0 to display welcome message.
int questionNum = 0; //Define question number.
int totalQuestions = 12; //Set question amount plus 2 for game messages.
int score = 0; //Keep score.
int buzzer = 7; //Buzzer pin.
int answer = 0;
bool doQuestion = false;

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

//Question structure - Question, answer one, answer two, answer three, answer four, correct answer button.
const char * const Question[12][6]= {
{"Welcome to Superquiz! Press any button to continue.", "Ready", "to", "play", "?", "1" },
{ "Game Over", "Your score is:", "1" },
{ "How many seasons of Friends were there?", "1", "4", "6", "10", "4" },
{ "Who pees on Monica after she is stung by a jelly fish?", "Chandler", "Rachel", "Joey", "Pheobe", "3" },
{ "Ross says whos name at the altar in london?", "Rachel", "Pheobe", "Monica", "Emily", "1" },
{ "How many sisters does joey have?", "5", "7", "2", "0", "2" },
{ "What is the name of Joeys character in the commercial for opening milk carton", "Mike", "Tommy", "Kevin", "Drake", "3" },
{ "What instrument did Ross intend to play at Monica and Chandlers Wedding?", "Bagpipe", "Drums", "Guitar", "Sax", "1" },
{ "What is Chandlers middle name?", "Nora", "Muriel", "Charles", "Francis", "2" },
{ "Who was Monicas first kiss?", "Chandler", "Pete", "Ross", "Richard", "3" },
{ "Chick Jr and Duck Jr get stuck in what?", "Toilet", "Foosball", "Bin", "Fridge", "2" },
{ "Who famously said PIVOT?", "Rachel", "Joey", "Monica", "Ross", "4" }
};

//Function for displaying on lcds.
void doDisplay(int Q){
  String mainLCD = Question[Q][0];
  String A1 = Question[Q][1];
  String A2 = Question[Q][2]; 
  String A3 = Question[Q][3];
  String A4 = Question[Q][4];
//Split question string between total lines and print on appropriate line.
  int stringStart = 0;
  int stringEnd = 20;
  

  for(int lcdLine = 0; lcdLine <= 3; lcdLine++){
    String displayString = mainLCD.substring(stringStart, stringEnd);//Create substring from main string within 20 chars.
          lcd.setCursor(0,lcdLine); //Set lcd line to required line.
          lcd.print(displayString); //Print 20 char substring.
              stringStart = stringEnd; //New substring start position is string end.
              stringEnd = stringEnd+20; //Add 20 to stringEnd to start the next 20 chars.
                
  }
  //Set answer screen.
  lcd2.setCursor(0, 0);
  lcd2.print(A1); //Print answer 1.
    lcd2.setCursor(7, 0);
    lcd2.print(A2); //Print answer 2.
      lcd2.setCursor(0, 1);
      lcd2.print(A3); //Print answer 3.
          lcd2.setCursor(7, 1);
          lcd2.print(A4); //Print answer 4.
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
        lcd.print("Restarting in 5..");
      delay(1000);
        lcd.setCursor(0,3);
        lcd.print("Restarting in 4..");
      delay(1000);
        lcd.setCursor(0,3);
        lcd.print("Restarting in 3..");
      delay(1000);
        lcd.setCursor(0,3);
        lcd.print("Restarting in 2..");
      delay(1000);
        lcd.setCursor(0,3);
        lcd.print("Restarting in 1..");
      delay(1000);
      //Reset game.
      welcome = 0; 
      questionNum = 0;
      buttonPressed = 0;
      score = 0;
        lcd.clear();
          lcd2.clear();
      doDisplay(0);
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

              delay(3000); //Delay 3 seconds so user can read screen.
              lcd.clear(); //Clear lcd one.
              lcd2.clear(); //Clear lcd two.
              questionNum++; //Move to next question.
              doQuestion = true; //Set doQuestion to true to display the next question.
}

void doButtons(){
  if(buttonPressed > 0 && welcome==0){ //If any button pressed.
  playSound(2);
      welcome=1; //Set welcome to 1 to show we have passed this stage.
      doQuestion = true;//Set first question
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
  if(questionNum +2 >= totalQuestions){ //Check if quiz should end, add 2 to question number to allow for game messages.
      doEnd();
  }
  else{
    if(welcome == 0){
         doDisplay(0); //Display first value from question array (Welcome message).
     }
     
    else{
      while(doQuestion){ //While do question is true.
        int showQuestion = questionNum +2; //showQuestion is question + 2 for game messages.
        doDisplay(showQuestion); //Display the question.
            answer = atoi(Question[showQuestion][5]); //Define the answer.
          doQuestion=false; //doQuestion is false because question is displayed.
          
          
    }
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
  doButtons();
   
     

}
