//This task reads the voltage from a TMP36 temperature sensor connected to analog pin A2
//Converts the voltage from a TMP36 temperature sensor connected to analog pin A2
//Prints the temperature to the serial monitor

//TMP36 sensor is connected to analog pin A2
int tmp36 = A2;

void setup() {
  Serial.begin(9600);      //Start serial communication at 9600 baud
  while(!Serial);          //Wait until the Serial Monitor is opened

  analogReadResolution(12);
//Set ADC resolution to 12 bits
//readings will be from 0 to 4095 instead of 0 to 1023
}

void loop() {
//Read the raw ADC value from the TMP36 sensor on pin A2
  uint16_t rawADC = analogRead(tmp36);

  //Convert ADC reading to voltage
  //Board uses 3.3volts reference, 12-bit ADC -> max value = 4095
  float voltage = 3.3*rawADC/4095.0;
  //Convert voltage to temperature for TMP36:
  //0.5V at 0 degree celsius and 10mV (0.01 V) per degree celsius
  float temperature = (voltage-0.5)*100;

  //Print result to Serial Monitor
  Serial.print("Room Temperature = ");
  Serial.println(temperature);              // show numeric value
  Serial.println(" degree Celsius. ");      //show units

  delay(1000);                              //Wait 1 second before taking the next reading

}
