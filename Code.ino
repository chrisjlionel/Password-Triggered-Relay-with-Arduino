// This project is coded by J Lionel Christian Jeyaraj (M.tech in Advanced manufacturing)
// Browse his featured works @ https://www.instructables.com/member/chrisjlionel/instructables/
// Email chrisjlionel@live.com
// mobile +91-8807971412

#include <Password.h> //http://playground.arduino.cc/uploads/Code/Password.zip 
#include <Keypad.h> //http://www.arduino.cc/playground/uploads/Code/Keypad.zip  
#include <Adafruit_SSD1306.h>

#define OLED_RESET 3
Adafruit_SSD1306 display(OLED_RESET);

Password password = Password( "LOCK1992" ); //password to unlock, can be changed.

const byte ROWS = 4; // Four rows
const byte COLS = 4; // columns
// Define the Keymap
char keys[ROWS][COLS] = {            //
{'1','2','3','L'},                   //
{'4','5','6','O'},                   // Keymap can be changed.
{'7','8','9','C'},                   //
{'E','0','R','K'}                    //
};
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[4]={5,6,7,8};
byte colPins[4]={9,10,11,12};


// Create the Keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //initialize with the I2C addr 0x3C (128x64)
  display.clearDisplay();
  Serial.write(254);
  Serial.write(0x01);
  delay(200); 
  pinMode(4, OUTPUT);  //Relay pin
  digitalWrite(4, HIGH);
  keypad.addEventListener(keypadEvent); //add an event listener for this keypad
 
  }

void loop(){
    keypad.getKey();
    }
  //take care of some special events
  void keypadEvent(KeypadEvent eKey){
  switch (keypad.getState()){
  case PRESSED:
  
  Serial.print("Enter:");  
  Serial.println(eKey);    
  display.clearDisplay();   
  display.setCursor(0,1);    //OLED Display
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print("PASSWORD:");
  display.print(eKey);
  display.setCursor(0,25);  //OLED Display
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.print("CHRISJLIONEL @ GITHUB");
  display.display();
  delay(10);
  display.clearDisplay();

  

 
  Serial.write(254);
  
  switch (eKey){
    case 'E': checkPassword(); delay(1); break;  // 'E' Enter key can be changed.
    
    case 'R': password.reset(); delay(1); break; // 'R' Reset key can be changed.
     
    default: password.append(eKey); delay(1);
}
}
}
void checkPassword(){
  
if (password.evaluate()){  //if password is right, it will turn on the relay
    
    Serial.println("Accepted");
    Serial.write(254);delay(10);
    digitalWrite(4, LOW);//turn on the relay in my case, some relay will switch with "HIGH", check before u upload
    display.clearDisplay();
    display.setCursor(0,1);  //OLED Display
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.print("Accepted");
    display.setCursor(0,25);  //OLED Display
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.print("CHRISJLIONEL @ GITHUB");
    display.display();
    delay(10);
    display.clearDisplay();
     
    
}
else{
    Serial.println("Denied"); //if passwords wrong keeps the relay in off position 
    Serial.write(254);delay(10);
    digitalWrite(4, HIGH);
    display.clearDisplay();
    display.setCursor(0,1);  //OLED Display
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.print("Denied!");
    display.setCursor(0,25);  //OLED Display
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.print("CHRISJLIONEL @ GITHUB");
    display.display();
    delay(10);
    display.clearDisplay();
    
      
}
}
