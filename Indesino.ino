#include <U8g2lib.h>
/*#include <RBDDimmer.h>*/
/*
 Indesino project
*/

#define PIN_LED_RED  13
#define PIN_LED_GREEN  12
#define PIN_BUTTON_BLACK  10
#define PIN_BUTTON_BLUE  11

bool pictureInvalid = true;
int delayCounter = 0;
bool timerStatus = false;
int blueButtonCounter = 0;
int blackButtonCounter = 0;
bool blackStatus = false;
bool blueStatus = false;
bool lastBlackStatus = false;
bool lastBlueStatus = false;

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);


// the setup function runs once when you press reset or power the board
void setup() {
     u8g2.begin();
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
   pinMode(PIN_LED_RED, OUTPUT);
   pinMode(PIN_LED_GREEN, OUTPUT);
   pinMode(PIN_BUTTON_BLACK, INPUT);
   pinMode(PIN_BUTTON_BLUE, INPUT);
}

// the loop function runs over and over again forever
void loop() {
  drawDisplay();
  buttonPoll();
  calcLogic();
  
  delayCounter++;
  if (delayCounter >= 100)
  {
    delayCounter = 0;
    timerStatus = !timerStatus;
  }
  delay(10); 
}


void drawDisplay() {
  if (pictureInvalid){

   u8g2.clearBuffer();         // clear the internal memory
   u8g2.setFont(u8g2_font_10x20_t_cyrillic);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
   u8g2.drawUTF8(2,15,"ПОЛОСКАНИЕ");  // write something to the internal memory
  // u8g2.sendBuffer();         // transfer internal memory to the display
   u8g2.drawUTF8(2,35,"59");
 
   u8g2.setFont(u8g2_font_unifont_t_symbols);  // https://github.com/olikraus/u8g2/wiki/fntgrpunifont#font-details
   u8g2.drawUTF8(74,55,"⏰☀☕⏳⏵");  // write something to the internal memory
   u8g2.drawUTF8(54,55,"◒"); 
  //  u8g2.sendBuffer();
  
   u8g2.drawUTF8(18,55,blackStatus?"◎":"○");  
   u8g2.drawUTF8(2,55,blueStatus?"◎":"○");  


   
   u8g2.sendBuffer();         // transfer internal memory to the display
/*for (int i=0; i < 10; i++)
{
    u8g2.drawUTF8(54,35,"◐"); 
    u8g2.sendBuffer();
       delay(200);
    u8g2.drawUTF8(54,35,"◓"); 
    u8g2.sendBuffer();
       delay(200);
    u8g2.drawUTF8(54,35,"◑"); 
    u8g2.sendBuffer();
     delay(200);
    u8g2.drawUTF8(54,35,"◒"); 
    u8g2.sendBuffer();
     delay(200);

} */


    pictureInvalid= false;
}
}
void buttonPoll(){
blackStatus =  digitalRead(PIN_BUTTON_BLACK);
blueStatus =  digitalRead(PIN_BUTTON_BLUE);
if (lastBlackStatus != blackStatus)
{
  lastBlackStatus = blackStatus;
  pictureInvalid = true;
}

if (lastBlueStatus != blueStatus)
{
  lastBlueStatus = blueStatus;
  pictureInvalid = true;
}

}

void pressBlackButton() {

}

void pressBlueButton() {
}

void calcLogic() {
 digitalWrite(PIN_LED_RED, timerStatus? HIGH : LOW);   
}
