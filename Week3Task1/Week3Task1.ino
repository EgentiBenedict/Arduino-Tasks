//This task is a program from your MKR Wifi1010 that waits for a character from the 
// computer monitor, check if the character is a letter(A-Z or a-z), if it's a letter,
//it turns ON LED, if it's anything else, it turns off the LED .

int myLed = 6;      //LED is connected in Pin6 on MKR1010
int input = 0;      //Variable to store character

void setup() {  
    pinMode(myLed,OUTPUT);      //Configure pin 6 as an LED so we candrive the LED
    Serial.begin(115200);       //Start the serial connection at 115200 baud
    while(!Serial);             //Wait her until the USB serial port is ready
    Serial.println("Serial is ready!");
}  

void loop() {  
  //Check if at least one byte has arrived from the computer
    if(Serial.available() > 0){  
        input = Serial.read();    //Read a single character from the serial buffer

        //Test if the character is a letter(lowercase a-z or uppercase A-Z)
        if(input >= 'a' && input <= 'z' || input >= 'A' && input <= 'Z')
        { 
            Serial.println("Letter Pressed ");   //Report that a letter was received
            digitalWrite(myLed,HIGH);            // Turn the LED on
        } else
        {  
            //Any other character(digits, punctuation, etc)
            Serial.println("Number Pressed ");
            digitalWrite(myLed,LOW);              //Turn the LED off
        }  
        Serial.flush();        //Wait until all outgoing serial data has been sent
    }  
    delay(5);                  //delay a bit to avoid hammering the serial port
} 