#pragma once

class adxl345
{
  public:
  void init(void);
  void setPowerControl(byte settings);
  void setDataFormatControl(byte settings);
  void setDataRate(byte rate);
  void getOutput(int* readings);
  void close(void);

  private:
  void oneByteWrite(byte address, byte data);
  int oneByteRead(byte address);
  void multiByteRead(byte startAddress, byte* buffer, int size);
} ;

