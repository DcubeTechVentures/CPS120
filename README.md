[![CPS120](CPS120_I2CS.png)](https://www.controleverything.com/content/Barometer?sku=CPS120_I2CS)
# CPS120
CPS120 Digital Barometer Altimeter  

The CPS120 is a absolute pressure sensor which provide a compensated digital pressure value.

This Device is available from ControlEverything.com [SKU: CPS120_I2CS]

https://www.controleverything.com/content/Barometer?sku=CPS120_I2CS

This Sample code can be used with Raspberry pi.

##Java 
Download and install pi4j library on Raspberry pi. Steps to install pi4j are provided at:

http://pi4j.com/install.html

Download (or git pull) the code in pi.

Compile the java program.
```cpp
$> pi4j CPS120.java
```

Run the java program as.
```cpp
$> pi4j CPS120
```

##Python 
Download and install smbus library on Raspberry pi. Steps to install smbus are provided at:

https://pypi.python.org/pypi/smbus-cffi/0.5.1

Download (or git pull) the code in pi. Run the program

```cpp
$> python CPS120.py
```
The code output is digital pressure in kPa.
