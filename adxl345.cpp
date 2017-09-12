#include "Arduino.h"

#include "adxl345_const.h"
#include "adxl345.h"
#include <Wire.h>

void adxl345::close(void)
{
  Wire.end();
}

void adxl345::init(void)
{
  Wire.begin();       // can't change transfer rate dynamatically, must change wire.h

  setPowerControl(0x00);     //standby mode
  setDataFormatControl(0x0B);//Full resolution, +/-16g, 4mg/LSB.
  setDataRate(ADXL345_400HZ);
  setPowerControl(0x08);     //measurement mode
}

void adxl345::setPowerControl(byte settings)
{
  oneByteWrite(ADXL345_POWER_CTL_REG, settings);
}

void adxl345::setDataFormatControl(byte settings)
{
  oneByteWrite(ADXL345_DATA_FORMAT_REG, settings);
}

void adxl345::setDataRate(byte rate)
{
  //Get the current register contents, so we don't clobber the power bit.
  byte registerContents = oneByteRead(ADXL345_BW_RATE_REG);

  registerContents &= 0x10;
  registerContents |= rate;

  oneByteWrite(ADXL345_BW_RATE_REG, registerContents);
}

void adxl345::getOutput(int* readings)
{
    byte buffer[6];
    
    multiByteRead(ADXL345_DATAX0_REG, buffer, 6);
    
    readings[0] = (int)buffer[1] << 8 | (int)buffer[0];
    readings[1] = (int)buffer[3] << 8 | (int)buffer[2];
    readings[2] = (int)buffer[5] << 8 | (int)buffer[4];
}

void adxl345::oneByteWrite(byte address, byte data)
{
    Wire.beginTransmission(I2C_Address);
    Wire.write(address); 
    Wire.write(data);
    Wire.endTransmission();
}

int adxl345::oneByteRead(byte address)
{
    Wire.beginTransmission(I2C_Address);
    Wire.write(address);
    Wire.endTransmission();
    
    Wire.requestFrom(I2C_Address,1);
    
    if(Wire.available()<=1){
        return Wire.read();
    }
}

void adxl345::multiByteRead(byte startAddress, byte* buffer, int size) 
{
    Wire.beginTransmission(I2C_Address);
    Wire.write(startAddress);
    Wire.endTransmission();
    
    Wire.requestFrom(I2C_Address,size);
    int remaining = size;
    byte* next = buffer;
    while (Wire.available() && remaining--)
    {
      *next++ = Wire.read();
    }
} 

