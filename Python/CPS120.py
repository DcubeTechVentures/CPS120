# Distributed with a free-will license.
# Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
# CPS120
# This code is designed to work with the CPS120_I2CS I2C Mini Module available from ControlEverything.com.
# https://www.controleverything.com/content/Barometer?sku=CPS120_I2CS#tabs-0-product_tabset-2

import smbus
import time

# Get I2C bus
bus = smbus.SMBus(1)

# CPS120 address, 0x28(40)
#		0x80(128)	 Select Start mode
bus.write_byte(0x28, 0x80)

time.sleep(0.1)

# CPS120 address, 0x28(40)
# Read data back from 0x00(0), 4 bytes, Pressure MSB first
data = bus.read_i2c_block_data(0x28, 0x00, 2)

# Convert the data to kPa
pressure = (((data[0] & 0x3F) * 256 + data[1]) / 16384.0) * 90 + 30

# Output data to screen
print "Barometric Pressure is : %.2f kPa" %pressure
