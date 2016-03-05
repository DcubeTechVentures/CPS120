// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// CPS120
// This code is designed to work with the CPS120_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Barometer?sku=CPS120_I2CS#tabs-0-product_tabset-2

import com.pi4j.io.i2c.I2CBus;
import com.pi4j.io.i2c.I2CDevice;
import com.pi4j.io.i2c.I2CFactory;
import java.io.IOException;

public class CPS120
{
	public static void main(String args[]) throws Exception
	{
		// Create I2CBus
		I2CBus bus = I2CFactory.getInstance(I2CBus.BUS_1);
		// Get I2C device, CPS120 I2C address is 0x28(40)
		I2CDevice device = bus.getDevice(0x28);
		
		// Send start command
		device.write(0x28, (byte)0x80);
		Thread.sleep(800);
		
		// Read 2 bytes of data, msb first
		byte[] data = new byte[2];
		device.read(data, 0, 2);
		
		// Convert data to kPa
		double pressure = (((data[0] & 0x3F) * 256 + data[1]) * (90 / 16384.00)) + 30;
		
		// Output data to screen
		System.out.printf("Pressure is : %.2f kPa %n",pressure);
	}
}
