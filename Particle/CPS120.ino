// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// CPS120
// This code is designed to work with the CPS120_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Barometer?sku=CPS120_I2CS#tabs-0-product_tabset-2

#include <application.h>
#include <spark_wiring_i2c.h>

// CPS120 I2C address is 0x28(40)
#define Addr 0x28

double temperature = 0.0, pressure = 0.0;
void setup() 
{
    // Set variable
    Particle.variable("i2cdevice", "CPS120");
    Particle.variable("pressure", pressure);
    Particle.variable("temperature", temperature);
  
    // Initialise I2C communication as MASTER
    Wire.begin();
    // Initialise serial communication, set baud rate = 9600
    Serial.begin(9600);
}

void loop()
{
    unsigned int data[4];
    
    // Start I2C Transmission
    Wire.beginTransmission(Addr);
    delay(10);
    // Stop I2C Transmission
    Wire.endTransmission();
    
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
    }
    
    // Convert the values
    pressure = ((((data[0] & 0x3F) * 265 + data[1]) / 16384.0 ) * 90.0 ) + 30.0 ;
    cTemp = ((((data[2] * 256) + (data[3] & 0xFC)) / 4.0 ) * (165.0 / 16384.0)) - 40.0;
    fTemp = cTemp * 1.8 + 32;
      
    // Output data to dashboard
    Particle.publish("Pressure is :   ", String(pressure));
    delay(1000);
    Particle.publish("Temperature in Celsius : ", String(cTemp));
    delay(1000);
    Particle.publish("Temperature in Fahrenheit : ", String(fTemp));
    delay(1000); 
}
