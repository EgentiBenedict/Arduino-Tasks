//This program reads  the value of a potentiometer connected to
//analog pin A2, converts it to voltage between 0V and 3.3V and
// then print the raw ADC value and the calculated voltage to the 
//Serial Monitor


//input pin where potentiometer is conected
int potentiometer = A2;

void setup() {
  //Start the serial monitor at 9600 baud
  Serial.begin(9600);
  //Wait for the serial connection to open
  while(!Serial);
}
void loop() {
  
  //Read raw ADC value 
  uint16_t rawADC = analogRead(potentiometer);
  //convert raw reading to voltage
  float voltage = 3.3*rawADC/1023.0;

  //Print raw ADC value
  Serial.print("ADC value = ");
  Serial.println(rawADC);
  Serial.println(".");

  //Print corresponding voltage
  Serial.print("Voltage = ");
  Serial.print(voltage);
  Serial.println("V.");       //show unit

  delay(1000);            //Wait one second before reading again

}
