// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// CPS120
// This code is designed to work with the CPS120_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Barometer?sku=CPS120_I2CS#tabs-0-product_tabset-2

#include<Wire.h>

// CPS120 I2C address is 0x28(40)
#define Addr 0x28

void setup() 
{
    // Initialise I2C communication
    Wire.begin();
    // Initialise Serial Communication, set baud rate = 9600
    Serial.begin(9600);
}

void loop()
{
    unsigned int data[4];
    // Request 4 byte of data
    Wire.requestFrom(Addr, 4);

    // Read 4 bytes of data
    // pressure msb, pressure lsb, temp msb, temp lsb
    if(Wire.available() == 4)
    {
      data[0] = Wire.read();
      data[1] = Wire.read();
      data[2] = Wire.read();
      data[3] = Wire.read(); 
      delay(100);
    
      // Convert the data to 14 bits
      float pressure = ((((data[0] & 0x3F) * 265 + data[1]) / 16384.0 ) * 90.0 ) + 30.0 ;
      float temperature = ((((data[2] * 256) + (data[3] & 0xFC)) / 4.0 ) * (165.0 / 16384.0)) - 40.0;
       
      // Output data to serial monitor
      Serial.print("Pressure is :   ");
      Serial.print(pressure);
      Serial.println(" kPa");
      Serial.print("Temperature is :  ");
      Serial.print(temperature);
      Serial.println(" C");
      delay(500); 
    }  
}
