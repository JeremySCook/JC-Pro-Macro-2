//Example for JC Pro Macro board
//set up to work in Mac OS
//Includes support for 1306 display
//Reference: https://github.com/NicoHood/HID/blob/master/src/KeyboardLayouts/ImprovedKeylayouts.h
//Reference: https://arduinogetstarted.com/tutorials/arduino-button-long-press-short-press 
//
//To do:
//Figure out what to do with bottom support - remake offset so locks in?
//caps lock code? - does not work properly on Mac it seems

//========================================================

#include <SPI.h>
#include <Wire.h>

// Declare variables etc=========================================

bool SW1 = 1; //encoder button
bool SW2 = 1; //lower-left keyswitch
bool SW3 = 1;
bool SW4 = 1; //lower-right keyswitch
bool SW5 = 1;
bool SW6 = 1; //upper-right keyswitch
bool SW7 = 1; //JCPM 2 key
bool SW8 = 1; //JCPM 2 key
bool SW9 = 1; //JCPM 2 key
bool SW10 = 1; //JCPM 2 mode switch

bool underLight = 0;

bool increment = 0;
bool decrement = 0;
long oldPosition;
long newPosition;
int inputMode = 0;
int LEDLight = 1;
int LEDCircle[6] = {3, 4, 5, 6, 7, 8};
int counter = 0;
bool nascar = 0;
long newNascarTurnTime = 0;
long oldNascarTurnTime = 0;
long newBeatTime = 0;
long oldBeatTime = 0;
bool beatOn = 0;

int fanSpeed = 0;
bool fanPulse = 0;
long newPulseTime = 0;
long oldPulseTime = 0;
int fanRPM = 0;
char toneNote;

int modeArray[] = {0, 1, 3, 5}; //adjust this array to modify sequence of modes - as written, change to {0, 1, 2, 3, 4, 5} to access all modes
int inputModeIndex = 0;
int modeArrayLength = (sizeof(modeArray) / sizeof(modeArray[0]));

// Encoder setup =============================================

#include <Encoder.h>
#include <HID-Project.h>
Encoder myEnc(0,1); //if rotation is backwards, swap 0 and 1

// Screen setup =============================================

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// NeoPixel setup =============================================

// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        5 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 15 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels

//============================================================

void setup() {
  //Serial.begin(9600);
  pinMode(4, INPUT_PULLUP); //SW1 pushbutton (encoder button)
  pinMode(15, INPUT_PULLUP); //SW2 pushbutton
  pinMode(A0, INPUT_PULLUP); //SW3 pushbutton
  pinMode(A1, INPUT_PULLUP); //SW4 pushbutton
  pinMode(A2, INPUT_PULLUP); //SW5 pushbutton
  pinMode(A3, INPUT_PULLUP); //SW6 pushbutton
//===============new pins for JCPM

  pinMode(14, INPUT_PULLUP); //SW7 pushbutton
  pinMode(16, INPUT_PULLUP); //SW8 pushbutton
  pinMode(10, INPUT_PULLUP); //SW9 pushbutton
  pinMode(9, INPUT_PULLUP); //SW10 pushbutton - acts as mode switch

//================end new pins
  

  randomSeed(analogRead(A9));
     
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    //Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.setRotation(2); //sets rotation 1 through 4 (2 = 180º rotation vs 4)
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  
Mouse.begin();
Keyboard.begin();
//BootKeyboard.begin(); - BootKeyboard use appears to give problems w/ Macintosh


//NeoPixel setup=========================================

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.clear();


  for(int i=0; i<NUMPIXELS; i++){
    pixels.setPixelColor(i, pixels.Color(10, 0, 0));
  }
  pixels.show(); // Show results
}


void loop() {

  SW1 = digitalRead(4);
  SW2 = digitalRead(15);
  SW3 = digitalRead(A0);
  SW4 = digitalRead(A1);
  SW5 = digitalRead(A2);
  SW6 = digitalRead(A3);
  SW7 = digitalRead(14);
  SW8 = digitalRead(16);
  SW9 = digitalRead(10);
  SW10 = digitalRead(9);
  
  newPosition = myEnc.read();
  
  if (newPosition > (oldPosition + 2)) { 
    increment = 1;
    delay(5);
    oldPosition = myEnc.read();
  }
  if (newPosition < (oldPosition - 2)) {
    decrement = 1;
    delay(5);
    oldPosition = myEnc.read();
  }

//=========change mode=================

   if (SW10 == 0){ 
      if (inputModeIndex < modeArrayLength){
        inputModeIndex++;
        inputMode = modeArray[inputModeIndex];
      }
      if (inputModeIndex == modeArrayLength){
        inputModeIndex = 0;
        inputMode = modeArray[inputModeIndex];
      }
      SW10 = 1;
      delay(250);
    }

//================================

//screen(); //need to change to only call within functions

//======select input mode:=======

if (inputMode == 0) volume();
if (inputMode == 1) jiggler();
if (inputMode == 2) slitherIO();
if (inputMode == 3) FCPX();
if (inputMode == 4) fan();
if (inputMode == 5) music();

//Serial.println(inputMode);

}

void volume(){

  if (increment == 1) {
        Consumer.write(MEDIA_VOLUME_UP);
        if (LEDLight == 5) LEDLight = 0;
        else if (LEDLight < 5) LEDLight += 1;
        topPixelsClear();
        pixels.setPixelColor(LEDCircle[LEDLight], pixels.Color(10, 0, 0));
        pixels.show(); // Show results
        increment = 0;
        decrement = 0;
        //delay(10);
      }
      
  if (decrement == 1) {
        Consumer.write(MEDIA_VOLUME_DOWN);
        if (LEDLight == 0) LEDLight = 5;
        else if (LEDLight > 0) LEDLight -= 1;
        topPixelsClear();
        pixels.setPixelColor(LEDCircle[LEDLight], pixels.Color(10, 0, 0));
        pixels.show(); // Show results
        increment = 0;
        decrement = 0;
        //delay(10);
      }
  if (SW6 == 0){ //tab to next browser tab Firefox or Chrome
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_TAB);          
        Keyboard.releaseAll();
        delay(50);
      }
  if (SW5 == 0){ //tab to previous browser tab Firefox or Chrome
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_TAB);
        Keyboard.releaseAll();
        delay(50);
      }
  if (SW3 == 0) {
        Consumer.write(MEDIA_PLAY_PAUSE); 
        delay(100);
      }
  if (SW4 == 0) {
        Consumer.write(MEDIA_NEXT);
        delay(50);
      }
  if (SW2 == 0) {
        Consumer.write(MEDIA_PREVIOUS);
        delay(50);
      }
  if ((SW7 == 0) && (underLight == 0)) {        
    underLight = 1;
    pixels.setPixelColor(9, pixels.Color(150, 0, 0));
    pixels.setPixelColor(10, pixels.Color(150, 0, 0));
    pixels.setPixelColor(11, pixels.Color(150, 0, 0));
    pixels.setPixelColor(12, pixels.Color(150, 0, 0));
    pixels.show(); // Show results
    delay(100);
  }
  else if ((SW7 == 0) && (underLight == 1)) {        
    underLight = 0;
    pixels.setPixelColor(9, pixels.Color(0, 0, 0));
    pixels.setPixelColor(10, pixels.Color(0, 0, 0));
    pixels.setPixelColor(11, pixels.Color(0, 0, 0));
    pixels.setPixelColor(12, pixels.Color(0, 0, 0));
    pixels.show(); // Show results
    delay(100);
  }  
  if ((SW8 == 0)||(SW9 == 0)){
    fan();
  }

      
screenVolume();
}

void jiggler(){ //works with new code
  
  //Serial.print("commence to jiggling");
      //Consumer.write(MEDIA_VOLUME_UP);
      //Consumer.write(MEDIA_VOLUME_DOWN);
      long randNumber = random(-50, 50);
      long randNumber1 = random(-50, 50);
      long randNumber2 = random(-50, 50);
      Mouse.move(randNumber, randNumber1);
      delay(100);
      int xMap = map(randNumber, -50, 50, 0, 100);
      int yMap = map(randNumber1, -50, 50, 0, 100);
      int zMap = map(randNumber2, -50, 50, 0, 100);
      pixels.setPixelColor(0, pixels.Color(xMap, yMap, zMap));
      pixels.setPixelColor(2, pixels.Color(zMap,xMap,yMap));
      pixels.setPixelColor(1, pixels.Color(yMap, zMap, xMap));
      pixels.setPixelColor(3, pixels.Color(xMap, yMap, zMap));
      pixels.setPixelColor(4, pixels.Color(zMap, xMap, yMap));    
      pixels.setPixelColor(5, pixels.Color(yMap, zMap, xMap));    
      pixels.setPixelColor(6, pixels.Color(xMap, yMap, zMap));    
      pixels.setPixelColor(7, pixels.Color(zMap, xMap, yMap));  
      pixels.setPixelColor(8, pixels.Color(yMap, zMap, xMap));                                  
      pixels.show(); // Show results

screenJiggle(); 
    
}

void slitherIO(){ //works with new code
//movement tracking
int xMovements[] = {-3, -8, -14, -16, -19, -19, -16, -14, -8, -3, 3, 8, 14, 16, 19, 19, 16, 14, 8, 3, -3};
int yMovements[] = {19, 16, 14, 8, 3, -3, -8, -14, -16, -19, -19, -16, -14, -8, -3, 3, 8, 14, 16, 19, 19};
int multiplier = 2; //changes speed of rotation

//homing routine =====================================================  
  if (SW6 == 0){
    Mouse.move(40, 10); //was 60, 0 before
    counter = 0;
    delay(250);
  }

//mouse move routine==================================================

  if (increment == 1) {
    //need a routine to loop back to zero etc to loop around the x/y movements for each increment

      for(int i=0; i< multiplier; i++){
        if (counter == 20) counter = 1;
        else if (counter < 20) ++counter;
        Mouse.move(xMovements[counter], yMovements[counter]);
        
        //Serial.print(counter); Serial.print(" "); Serial.print(xMovements[counter]); Serial.print(" "); Serial.println(yMovements[counter]);
        increment = 0;
        decrement = 0;
      }
  }
  

    if (decrement == 1) { //increment and decrement work fine individually, but don't line up when reversed
      for(int i=0; i< multiplier; i++){     
        if (counter == 0) counter = 19; 
        else if (counter > 0) --counter;       
        Mouse.move(-xMovements[counter+1], -yMovements[counter+1]);

        //Serial.print(counter); Serial.print(" "); Serial.print(-xMovements[counter+1]); Serial.print(" "); Serial.println(-yMovements[counter+1]);
        increment = 0;
        decrement = 0;
      }
  }

//worm speed input==============================

if ((SW2 == 0)||(SW3 == 0)||(SW4 ==0)){
        Keyboard.press(HID_KEYBOARD_SPACEBAR);       
        delay(5);
}

if ((SW2 == 1) && (SW3 == 1) && (SW4 == 1)){
        Keyboard.releaseAll();
        delay(5);
}

//worm auto turn input - NASCAR mode: all left turns

if ((SW5 == 0) && (nascar == 0)){
  nascar = 1;
  delay(20);
}

else if ((SW5 == 0) && (nascar ==1)){
  nascar = 0;
  delay(20);
}

if (nascar == 1){
  newNascarTurnTime = millis();
  if ((newNascarTurnTime - oldNascarTurnTime) > 200){
    decrement = 1;
    oldNascarTurnTime = newNascarTurnTime;
  }
}


screen();
  
}

void FCPX(){
  
  if (increment == 1) {
        //Keyboard.press(KEY_K);
        //Keyboard.releaseAll();       
        Keyboard.press(HID_KEYBOARD_RIGHTARROW);
        Keyboard.releaseAll();
        if (LEDLight == 5) LEDLight = 0;
        else if (LEDLight < 5) LEDLight += 1;
        topPixelsClear();
        pixels.setPixelColor(LEDCircle[LEDLight], pixels.Color(0, 10, 0));
        pixels.show(); // Show results
        increment = 0;
        decrement = 0;
        //delay(50);
      }
      
  else if (decrement == 1) {
        //Keyboard.press(KEY_K);
        //Keyboard.releaseAll();  
        Keyboard.press(HID_KEYBOARD_LEFTARROW);
        Keyboard.releaseAll();
        if (LEDLight == 0) LEDLight = 5;
        else if (LEDLight > 0) LEDLight -= 1;
        topPixelsClear();
        pixels.setPixelColor(LEDCircle[LEDLight], pixels.Color(0, 10, 0));
        pixels.show(); // Show results
        increment = 0;
        decrement = 0;
        //delay(50);
      }
  else if (SW7 == 0){ //Zoom in
        Keyboard.press(KEY_LEFT_WINDOWS);
        Keyboard.press(HID_KEYBOARD_EQUALS_AND_PLUS);    
        Keyboard.releaseAll();
        delay(50);
      }
  else if (SW8 == 0){ //Zoom out
        Keyboard.press(KEY_LEFT_WINDOWS);
        Keyboard.press(HID_KEYBOARD_MINUS_AND_UNDERSCORE);    
        Keyboard.releaseAll();
        delay(50);
      }
  else if (SW4 == 0) { //fwd
        Keyboard.press(KEY_L);
        Keyboard.releaseAll();
        delay(50);
      }
  else if (SW3 == 0) { //stop
        Keyboard.press(KEY_K);
        Keyboard.releaseAll();
        delay(50);
      }
  else if (SW2 == 0) { //BACK
        Keyboard.press(KEY_J);
        Keyboard.releaseAll();
        delay(50);
      }
  else if (SW1 == 0) { //break all win + shift + b
        Keyboard.press(KEY_LEFT_WINDOWS);        
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(KEY_B);        
        Keyboard.releaseAll();
        delay(50);
      }
    else if (SW6 == 0) { //break current track win + b
        Keyboard.press(KEY_LEFT_WINDOWS);        
        Keyboard.press(KEY_B);        
        Keyboard.releaseAll();
        delay(50);
      }
    else if (SW5 == 0) { //undo
        Keyboard.press(KEY_LEFT_WINDOWS);        
        Keyboard.press(KEY_Z);        
        Keyboard.releaseAll();
        delay(50);
      }
    else if (SW9 == 0) { //backspace (delete)  
        Keyboard.press(KEY_BACKSPACE);        
        Keyboard.releaseAll();
        delay(50);
      }
        
screenFCPX();
}

void fan(){
  if (SW8 == 0){
    if (fanSpeed < 5){
    ++fanSpeed;
    }
    delay(20);
  }
  if (SW9 == 0){
    if (fanSpeed > 0){
    --fanSpeed;
    }
    delay(20);
  }
int fanSpeedScaled = map(fanSpeed, 0, 5, 0, 255);
analogWrite(6, fanSpeedScaled);
//Serial.print(fanSpeed); Serial.print(" "); Serial.println(fanSpeedScaled);

if(fanPulse == 0){
  newPulseTime = millis();
  fanRPM = (newPulseTime - oldPulseTime);
  oldPulseTime = newPulseTime;
}

//screenFan();

}

void music(){

//attach small buzzer to pin 6 on aux jack
//

pinMode(7, OUTPUT);
digitalWrite(7, LOW);

  if (SW2 == 0){
    tone(6, 220, 100); //A3 
    toneNote = 'A';
  }
  else if (SW3 == 0){
    tone(6, 247, 100); //B3
    toneNote = 'B';
  }
  else if (SW4 == 0){
    tone(6, 262, 100); //C4
    toneNote = 'C';
  }  
  else if (SW9 == 0){
    tone(6, 294, 100); //D4
    toneNote = 'D';
  }
  else if (SW5 == 0){
    tone(6, 330, 100); //E4
    toneNote = 'E';
  }
  else if (SW8 == 0){
    tone(6, 349, 100); //F4
    toneNote = 'F';
  }
  else if (SW6 == 0){
    tone(6, 392, 100); //G4
    toneNote = 'G';
  }
  else if (SW7 == 0){
    tone(6, 440, 100); //A4
    toneNote = 'A';
  }
  else {
    toneNote = ' ';
  }
  
  if ((SW1 == 0) && (beatOn == 0)) {
    beatOn = 1;
    delay(100);
  }
  else if ((SW1 == 0) && (beatOn == 1)){
    beatOn = 0;
    delay(100);
  }
  
  if (beatOn == 1) {
  newBeatTime = millis();
  if ((newBeatTime - oldBeatTime) > 500){
  digitalWrite(7, HIGH);
  delay(35);
  digitalWrite(7, LOW);
    oldBeatTime = newBeatTime;
  }
  }

  if (decrement == 1){
  digitalWrite(7, HIGH);
  delay(35);
  digitalWrite(7, LOW);
  increment = 0;
  decrement = 0;
  }

  if (decrement == 1){
  digitalWrite(7, HIGH);
  delay(35);
  digitalWrite(7, LOW);
  increment = 0;
  decrement = 0;
  }

  if (increment == 1){
  digitalWrite(7, HIGH);
  delay(35);
  digitalWrite(7, LOW);
  increment = 0;
  decrement = 0;
  }
 
screenNote();
}

//======================.96" oled screen=======================

void screenVolume(){
  display.setTextSize(1); 
  display.clearDisplay();
  display.invertDisplay(0);
  display.setCursor(0,0);
  //display.println("");  
  display.println("ENCOD|     |TAB+ |LIT");
  display.println("");
  display.println("VOL- |VOL+ |TAB- |FN+");
  display.println("");
  display.println("BACK |STOP |FORW |FN-");
  display.println("");  
  //display.print(increment);
  //display.print(decrement);
  //display.print(" ");
  display.print(newPosition);
  display.print(" ");
  display.print(LEDLight);
  display.print(" ");
  display.print(SW1);
  display.print(SW2);
  display.print(SW3);
  display.print(SW4);
  display.print(SW5);
  display.print(SW6);
  display.print(SW7);
  display.print(SW8);
  display.print(SW9);
  display.print(SW10);
  display.display();
  //Serial.println(SW1);
  //delay(10);
}

void screen(){
  display.clearDisplay();
  display.invertDisplay(0);
  display.setCursor(0,10);
  display.print(increment);
  display.print(decrement);
  display.print(" ");
  display.print(newPosition);
  display.println(LEDLight);
  display.print(" ");
  display.print(SW1);
  display.print(SW2);
  display.print(SW3);
  display.print(SW4);
  display.print(SW5);
  display.print(SW6);
  //display.print(inputMode);
  display.display();
  //Serial.println(SW1);
  //delay(10);
}

void screenFan(){
  display.clearDisplay();
  display.invertDisplay(0);
  display.setCursor(0,10);
  display.print("Fan ");
  display.print(fanSpeed);
  display.print(" ");
  display.println(fanPulse);
  display.print("T ");
  display.print(fanRPM);
  display.print(" ");
  display.print(inputMode);
  display.display();
  //Serial.println(SW1);
  //delay(10);
}

void screenJiggle(){
  display.setTextSize(3); 
  display.clearDisplay();
  display.invertDisplay(0);
  display.setCursor(0,10);
  display.println("Rando");
  display.print("Mouse!");
  display.display();
}

void screenNote(){ //now used for notes
  display.setTextSize(3); 
  display.clearDisplay();
  display.invertDisplay(0);
  display.setCursor(0,10);
  display.print("TONE ");
  display.println(toneNote);
  display.print(SW1);
  display.print(SW2);
  display.print(SW3);
  display.print(SW4);
  display.print(SW5);
  display.print(SW6);
  display.print(inputMode); 
  display.display();
  //Serial.println(SW1);
  //delay(10);
}

void screenFCPX(){
  display.setTextSize(1); 
  display.clearDisplay();
  display.invertDisplay(0);
  display.setCursor(0,0);
  //display.println("");  
  display.println("FCPX |BRKA |BRK  |ZO+");
  display.println("");
  display.println("FRM- |FRM+ |UNDO |ZO-");
  display.println("");
  display.println("BACK |STOP |FORW |DEL");
  display.println("");  
  //display.println("FCPX");
  //display.print("Sh0rcut");
  display.display();
}

//====================pixel helpers===============

void topPixelsClear(){
    for(int i=0; i<9; i++){
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
  pixels.show(); // Show results
}
