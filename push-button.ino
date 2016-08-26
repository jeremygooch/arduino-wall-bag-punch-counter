#include <SoftwareSerial.h>  //for software serial communication

#define txPin 1  //change to your serial port on Arduino board
#define rxPin 0  //not used but is required

SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);
int buttonPressCount;

const int  buttonPin = 2;    //the pin that the pushbutton is attached to

int buttonPushCounter = 0;   //counter for the number of button presses
int buttonState = 0;         //current state of the button
int lastButtonState = 0;     //previous state of the button

void setup()  {
  pinMode(buttonPin, INPUT);  //initialize the button pin as a input
  Serial.begin(9600);  //initialize serial communication

  pinMode(txPin, OUTPUT);
  //the following resets the board, changes the brightness to 100%, and sets the board to '0000':
  mySerial.begin(9600);
  mySerial.print(0x7A); //special character
  mySerial.print(0x00); //set brightness to full
  mySerial.print(0x76); //reset board
  mySerial.print(0); //send '0' character
  mySerial.print(0); //send '0' character
  mySerial.print(0); //send '0' character
  mySerial.print(0); //send '0' character
}

void loop() {

  buttonState = digitalRead(buttonPin);  //read the pushbutton input pin

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button
      // went from off to on:
      buttonPushCounter++;

      Serial.print("number of button pushes:  ");
      Serial.println(buttonPushCounter, DEC);
      updateDisplay(buttonPushCounter);  //function to update the display 'requires button press count'
    }

  }

  lastButtonState = buttonState;  // save the current state as the last state, for next time through the loop
}

void updateDisplay(int buttonPushCounter) {
  String intString = String(buttonPushCounter);  //changes integer to a string
  char displayChars[4];  //create array to hold the four numbers
  int stringLength = intString.length();  //get length of the string
  //the following will determine if the button press count variable has 1, 2, 3, or 4 numbers in it
  //and will fill the empty spaces with '0'. so if the button press count variable is '29' it will end up being '0029':
  if (stringLength == 4) {
    displayChars[0] = intString.charAt(0);
    displayChars[1] = intString.charAt(1);
    displayChars[2] = intString.charAt(2);
    displayChars[3] = intString.charAt(3);
  } else if (stringLength == 3) {
    displayChars[0] = 0;
    displayChars[1] = intString.charAt(0);
    displayChars[2] = intString.charAt(1);
    displayChars[3] = intString.charAt(2);
  } else if (stringLength == 2) {
    displayChars[0] = 0;
    displayChars[1] = 0;
    displayChars[2] = intString.charAt(0);
    displayChars[3] = intString.charAt(1);
  } else if (stringLength == 1) {
    displayChars[0] = 0;
    displayChars[1] = 0;
    displayChars[2] = 0;
    displayChars[3] = intString.charAt(0);
  }

  Serial.println(displayChars[3]);

  // Reset each digit on the board
  mySerial.print(0x76);
  mySerial.print(0x76);
  mySerial.print(0x76);
  mySerial.print(0x76);

  // Print the digits to the screen
  mySerial.print(displayChars[3]);
  mySerial.print(displayChars[0]);
  mySerial.print(displayChars[1]);
  mySerial.print(displayChars[2]);
  // mySerial.print(0);
  // mySerial.print(1);
  // mySerial.print(2);
  // mySerial.print(3);

  delay(50); //this will make it so you don't get double counts. you could also use this to avoid someone pressing the button repeatedly 'for fun!'
}


