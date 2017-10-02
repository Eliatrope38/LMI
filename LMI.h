#ifndef LMI_h
#define LMI_h

#include "Arduino.h"
#include <Wire.h>

class LMI{
  private:
    int address = 0x00;
    String FW_Version; // char[0] -> major version number, char[2] -> minor version number , char[1] always a '.'
    String PartNumber;
    String LotNumber;
    int PressureRange;
    char OutputType; // U or B
    unsigned int scale_factor;
    int OutputCount;
    void GetSignature();
    String Raw_Data;

  public:
    LMI();
    void begin(int Address);
    float GetPressure();
    int16_t GetPressureCount();
    String GetFWVersion();
    String GetPartNumber();
    String GetLotNumber();
    unsigned int GetScaleFactor();
    int GetPressureRange();
    char GetOutputType();

};

#endif
