// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// CPS120
// This code is designed to work with the CPS120_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Barometer?sku=CPS120_I2CS#tabs-0-product_tabset-2

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

void main()
{
	// Create I2C bus
	int file;
	char *bus = "/dev/i2c-1";
	if((file = open(bus, O_RDWR)) < 0) 
	{
		printf("Failed to open the bus. \n");
		exit(1);
	}
	// Get I2C device, CPS120 I2C address is 0x28(40)
	ioctl(file, I2C_SLAVE, 0x28);

	// Send start command(0x80)
	char config[2] = {0};
	config[0] = 0x28;
	config[1] = 0x80;
	write(file, config, 2);
	sleep(1);

	// Read 2 bytes of data, msb first
	char reg = {0x00};
	write(file, reg, 1);
	char data[2] = {0};
	if(read(file, data, 2) != 2)
	{
		printf("Erorr : Input/output Erorr \n");
	}
	else
	{
		// Convert data to kPa
		double pressure = (((data[0] & 0x3F) * 256 + data[1]) * (90 / 16384.00)) + 30;

		// Output data to screen
		printf("Pressure is : %.2f kPa \n", pressure);
	}
}
