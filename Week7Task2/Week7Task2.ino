//This Arduino program uses SPI communication to read an external Analog-to-Digital-Converter
//The ADC measures an analog voltage(temperature sensor output), sends the digital value back using SPI
//and the Arduino converts that reading into a temperature value

#include <SPI.h>
//Chip Select pin used to communicate with the ADC over SPI
#define CS 5
//SPI clock rate (1.6MHz)
#define ADC_CLK 1600000
//ADC reference voltage in millivolts
#define ADC_VREF 3300

  float temp;
// put your setup code here, to run once:
    void setup() {
      //CS pin must be an output
    pinMode(CS, OUTPUT);
    digitalWrite(CS, HIGH);   //Start disabled
    //SPI settings
    SPISettings settings(ADC_CLK, MSBFIRST, SPI_MODE0);
    //Initialize SPI hardware
    SPI.begin();
    SPI.beginTransaction(settings);

    //Start serial communication
    Serial.begin(115200);
    //Wait for Serial monitor to connect
    while (!Serial);
  }
  void loop() {
    // Channel number to read from ADC
    uint8_t ch = 4;
    //Read ADC value
    uint16_t adc_value = spi_adc(ch);
    //Convert ADC reading to voltage (3.3V)
    float volt = 3.3 * adc_value / 4095.0;
    //Convert voltage to temperature 
    temp = (volt - 0.5) * 100;
    //Print the temperature
    Serial.print("Temperature in the room is ");
    Serial.print(temp, 2);
    Serial.println(" deg. C. ");
    //Update every second
    delay(1000);
  }

  //Reads ADC channel over SPI
  uint16_t spi_adc(uint16_t channel) {
    //Build command bytes sent to the ADC
    uint8_t channelMSB = (channel & 0b00000100) >> 2;
    uint8_t firstByte = (0b00000110) | channelMSB;
    uint8_t secondByte = channel << 6;
    uint8_t firstByteMsk = 0x0F;
    if (channel > 7) {
      //Check if ADC has only 8 channels
      Serial.println("Invalid channel number");
      return 0xFFFF;
    }
    //Begin SPI transfer
    digitalWrite(CS, LOW);
    //Send first command byte
    SPI.transfer(firstByte);
    uint8_t firstResult = SPI.transfer(secondByte);
    uint8_t secondResult = SPI.transfer(0x0);
    End SPI
    digitalWrite(CS, HIGH);
    uint16_t finalResult = (firstResult & firstByteMsk) << 8;
    finalResult = finalResult | secondResult;
    return finalResult;
  }
