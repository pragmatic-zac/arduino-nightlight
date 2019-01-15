/*

Inspired by SparkFun Inventor’s Kit, Circuit 1D-RGB Nightlight, starter code written by Sparkfun.

Turns an RGB LED on or off based on the light level read by a photoresistor.
Change colors by turning the potentiometer.

Modifications are my own - I wanted to expirement with a blinking LED and also a pulsing LED.

 */

int photoresistor = A0;          //variable for storing the photoresistor value
int potentiometer = A1;          //variable for storing the photoresistor value
int threshold = 700;            //if the photoresistor reading is lower than this value the light wil turn on

//LEDs are connected to these pins
int RedPin = 9;
int GreenPin = 10;
int BluePin = 11;

void setup() {
  Serial.begin(9600);           //start a serial connection with the computer

  //set the LED pins to output
  pinMode(RedPin,OUTPUT);
  pinMode(GreenPin,OUTPUT);
  pinMode(BluePin,OUTPUT);
}

void loop() {
  
  photoresistor = analogRead(A0);         //read the value of the photoresistor
  potentiometer = analogRead(A1);         // read the value of the potentiometer

  Serial.print("Photoresistor value:");
  Serial.print(photoresistor);          //print the photoresistor value to the serial monitor
  Serial.print("  Potentiometer value:");
  Serial.println(potentiometer);          //print the photoresistor value to the serial monitor

  // zj - trying a sine wave to pulse LED, establishing these variables here (notice that they are inside the loop)
  // for reference - https://www.sparkfun.com/tutorials/329 

  float in, out;

  //
  
  if(photoresistor < threshold){          //if it's dark (the photoresistor value is below the threshold) turn the LED on
    //These nested if staments check for a variety of ranges and 
    //call different functions based on the current potentiometer value.
    //Those functions are found at the bottom of the sketch. 
    if(potentiometer > 0 && potentiometer <= 150)
      red();
      delay(50); // zj - just toying with this to flash the LED from green to red (Merry Christmas)
      green();
    if(potentiometer > 150 && potentiometer <= 300)
      orange();
    if(potentiometer > 300 && potentiometer <= 450)
      yellow(); 
    if(potentiometer > 450 && potentiometer <= 600)
      green();
    if(potentiometer > 600 && potentiometer <= 750)
      cyan();
    if(potentiometer > 750 && potentiometer <= 900)
      blue(); 
    if(potentiometer > 900)
    
     // zj - modified this to pulse the magenta LED via sin wave
          for (in = 0; in < 6.283; in = in + 0.001)
            {
              out = sin(in) * 127.5 + 127.5; // LED can only take values from 0 to 255, hence the math here. it will always return value between 0 and 255
              magenta(out); // passing "out" as an argument to magenta function
              delay(0.01); // this can be taken out - just adds a nice way to vary the pulse speed
            }

  } 
  else {                                //if it isn't dark turn the LED off
    
    turnOff();                            //call the turn off function
    
  }  
  
  delay(100);                             //short delay so that the printout (to serial port) is easier to read
}

void red (){
    
    //set the LED pins to values that make red    
    analogWrite(RedPin, 100);
    analogWrite(GreenPin, 0);
    analogWrite(BluePin, 0);
}
void orange (){
    
    //set the LED pins to values that make orange
    analogWrite(RedPin, 100);
    analogWrite(GreenPin, 50);
    analogWrite(BluePin, 0);
}
void yellow (){
    
    //set the LED pins to values that make yellow
    analogWrite(RedPin, 100);
    analogWrite(GreenPin, 100);
    analogWrite(BluePin, 0);
}
void green (){
    
    //set the LED pins to values that make green    
    analogWrite(RedPin, 0);
    analogWrite(GreenPin, 100);
    analogWrite(BluePin, 0);
}
void cyan (){
    
    //set the LED pins to values that make cyan    
    analogWrite(RedPin, 0);
    analogWrite(GreenPin, 100);
    analogWrite(BluePin, 100);
}
void blue (){
    
    //set the LED pins to values that make blue
    analogWrite(RedPin, 0);
    analogWrite(GreenPin, 0);
    analogWrite(BluePin, 100);
}
void magenta (int out){ // in order to pass thru argument, explicitly type "int"
    
    // set the LED pins to values that make magenta   

    // zj - using "out" here to set values of the LED's; red/blue change at the same rate
    
    analogWrite(RedPin, out);
    analogWrite(GreenPin, 0);
    analogWrite(BluePin, out);

}
void turnOff (){
  
    //set all three LED pins to 0 or OFF
    analogWrite(RedPin, 0);
    analogWrite(GreenPin, 0);
    analogWrite(BluePin, 0);
}