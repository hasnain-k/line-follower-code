// Define analog input
#define ANALOG_IN_PIN A1
 #define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

// Floats for ADC voltage & Input voltage
float adc_voltage = 0.0;
float in_voltage = 0.0;
 
// Floats for resistor values in divider (in ohms)
float R1 = 30000.0;
float R2 = 7500.0; 
 
// Float for Reference Voltage
float ref_voltage = 5.0;
 
// Integer for ADC value
int adc_value = 0;

#include <SPI.h>
#include <SD.h>
File myFile;

#define smid A3
#define sleft A0
#define sright A2

#define aspeed 11
#define bspeed 10

#define m1 2
#define m2 3
#define m3 4 
#define m4 5
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// declare an SSD1306 display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


void setup() {
  // Setup Serial Monitor
  Serial.begin(9600);
  Serial.println("DC Voltage Test");
  if (!oled.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  oled.clearDisplay();
 

  
// Open serial communications and wait for port to open:
Serial.begin(9600);
while (!Serial) {
; // wait for serial port to connect. Needed for native USB port only
}
Serial.print("Initializing SD card...");
if (!SD.begin(10)) {
Serial.println("initialization failed!");
while (1);
}
Serial.println("initialization done.");
// open the file. note that only one file can be open at a time,
// so you have to close this one before opening another.

// if the file opened okay, write to it:



  
Serial.begin(9600);
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }

  delay(2000);         // wait for initializing
  oled.clearDisplay(); // clear display

  oled.setTextSize(3);          // text size
  oled.setTextColor(WHITE);     // text color
  oled.setCursor(0, 10);        // position to display
  //oled.println("ugf"); // text to display
  oled.display();               // show on OLED
  
  Serial.begin(9600);

  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);

  pinMode(smid, INPUT);
  pinMode(sleft, INPUT);
  pinMode(sright, INPUT);
analogWrite(aspeed, 70);
analogWrite(bspeed, 70);

}

void loop() {

  if( (digitalRead(sleft)==0) && (digitalRead(smid)==1) && (digitalRead(sright)==0) ){fwd();}

 if( (digitalRead(sleft)==1) && (digitalRead(smid)==1) && (digitalRead(sright)==0) ){shleft();}

  if( (digitalRead(sleft)==0) && (digitalRead(smid)==1) && (digitalRead(sright)==1) ){shright();}
  
  if( (digitalRead(sleft)==0) && (digitalRead(smid)==0) && (digitalRead(sright)==0) ){Stop();}

 // else {Stop();}
  
  // Read the Analog Input
  adc_value = analogRead(ANALOG_IN_PIN);
 
  // Determine voltage at ADC input
  adc_voltage  = (adc_value * ref_voltage) / 1024.0;
 
  // Calculate voltage at divider input
  in_voltage = adc_voltage / (R2 / (R1 + R2)) ;
 
  // Print results to Serial Monitor to 2 decimal places
  Serial.print("Input Voltage = ");
  Serial.println(in_voltage, 2);
 
  oled.setCursor(20, 10); //oled display
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.println("Battery Voltage");
 
 
  oled.setCursor(25, 30); //oled display
  oled.setTextSize(2);
  oled.setTextColor(WHITE);
  oled.print(in_voltage, 2);
  oled.println(" V");
  oled.display();
  delay(500);
  oled.clearDisplay();
 

  
}

//////////////////////////////////////////////////////
//_____________________________________________________________


void shleft(){
  
  
     Serial.println("sharp left");
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, HIGH);
    oled.setCursor(0, 10);
     oled.println("turning left");
     oled.display(); 
     oled.clearDisplay();
     myFile = SD.open("testpj.txt", FILE_WRITE);
     if (myFile) {
Serial.print("Writing to testpj.txt...");
myFile.println("moving left");
myFile.println("testing 1, 2, 3.");
for (int i = 0; i < 20; i++) {
myFile.println(i);
}
// close the file:
myFile.close();
Serial.println("done.");
} else {
// if the file didn't open, print an error:
Serial.println("error opening testpj.txt");
}
} 


void shright(){
  
  
     Serial.println("sharp right");
    digitalWrite(m1, LOW);
    digitalWrite(m2, HIGH);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
    oled.setCursor(0, 10);
    oled.println("turning right");
    oled.display(); 
     oled.clearDisplay();
     myFile = SD.open("testpj.txt", FILE_WRITE);
     if (myFile) {
Serial.print("Writing to testpj.txt...");
myFile.println("moving right");
myFile.println("testing 1, 2, 3.");
for (int i = 0; i < 20; i++) {
myFile.println(i);
}
// close the file:
myFile.close();
Serial.println("done.");
} else {
// if the file didn't open, print an error:
Serial.println("error opening testpj.txt");
}
}


void fwd(){
  
  
     Serial.println("activated fwd");
    digitalWrite(m1, LOW);
    digitalWrite(m2, HIGH);
    digitalWrite(m3, LOW);
    digitalWrite(m4, HIGH);
    oled.setCursor(0, 10);
    oled.println("moving forward");
    oled.display();   
     oled.clearDisplay();
     myFile = SD.open("testpj.txt", FILE_WRITE);
     if (myFile) {
Serial.print("Writing to testpj.txt...");
myFile.println("moving forward");
myFile.println("testing 1, 2, 3.");
for (int i = 0; i < 20; i++) {
myFile.println(i);
}
// close the file:
myFile.close();
Serial.println("done.");
} else {
// if the file didn't open, print an error:
Serial.println("error opening testpj.txt");
}
    
}

void Stop(){
     Serial.println("STOPING");
          Serial.println("activated REV");
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
    delay(150);      
    

    
   
}
