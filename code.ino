/* Interfacing MCP9800 I2C Temperature Sensor to Arduino Uno
 *  
 *  Hardware Components:
 *  Arduino Uno
 *  MCP9800 Temp Sensor
 *  
 *  Hardware Connection:
 *  SCL of MCP9800 is connected A5 of Arduino Uno
 *  SDA of MCP9800 is connected A4 of Arduino Uno
 *  A0,A1,A2 of MCP9800 are connected to ground.
 *  
 *  Author : Sahana B G
 *  Date :07 May 2021
 */

// Header file
#include<Wire.h>

// Device address when A0,A1,A2 are grounded
const int DEVICE_ADDRESS = 0x48;

// Address of Ambient temperature register (TA)
const int AMBIENT_TEMP_REG_ADDRESS = 0x00;

// Address of Configuration register (CONFIG)
const int  CONFIG_REG_ADDRESS =0x01;

// Value of Configuration register for 12bit resolution
const int CONFIG_REG_VALUE =0x20; 

void setup()
{
  // Baud rate
  Serial.begin(9600);

  // This creates a Wire object
  Wire.begin();
  
}

void loop()
{
  //Send a request to begin communication with the device at the specified DEVICE_ADDRESS
  Wire.beginTransmission(DEVICE_ADDRESS);

  // sends instruction byte
  Wire.write(CONFIG_REG_ADDRESS );

  // Sends MCP9800 value byte
  Wire.write(CONFIG_REG_VALUE);

  // This ends transmission of data from the Arduino to the Temperature sensor
  Wire.endTransmission();

  //Send a request to begin communication with the device at the specified DEVICE_ADDRESS
  Wire.beginTransmission(DEVICE_ADDRESS);

  //
  Wire.write(AMBIENT_TEMP_REG_ADDRESS);

  // This ends transmission of data from the Arduino to the Temperature sensor
  Wire.endTransmission();

  Wire.requestFrom(DEVICE_ADDRESS,2);
  while(Wire.available() == 0);
  uint8_t msb = Wire.read();
  uint8_t lsb = Wire.read();
  Wire.endTransmission();

  int temp = (msb << 4) + (lsb >> 4);
  Serial.print(" Temperature Value:");
  Serial.println(temp);
  
}
