
/***************************************************
  This is a library for the First Sensor LMI Pressure sensor
  Designed specifically to work with the LMI
  ---->https://www.first-sensor.com/en/products/pressure-sensors/pressure-sensors-and-transmitters/amplified-pressure-sensors/lmi/index.html
***************************************************/

#ifndef LMI_h
#define LMI_h

#include "Arduino.h"
#include <Wire.h>

#define PRESSURE_REGISTER 0x20
#define SIGNATURE_REGISTER 0x23

class LMI{
  private:
    int address = 0x00; // Set at 0x00 to be sure about init
    String FW_Version;
    String PartNumber;
    String LotNumber;
    String SerialNumber;
    unsigned int PressureRange;
    char OutputType; // U or B
    unsigned int scale_factor; // used to convert read pressure count to Pa Pressure Value
    int OutputCount; // Pressure count from LMI
    String Raw_Data; // Raw Data read from Signature recovery
    void GetSignature(); // Read signature and fill parameters

  public:
    LMI();
    void begin(int Address);
    float GetPressure(); // Pressure in Pascal
    int16_t GetPressureCount(); // Pressure in count
    String GetFWVersion();
    String GetPartNumber();
    String GetLotNumber();
    String GetSerialNumber();
    unsigned int GetScaleFactor(); // factor used to go to Pa Value
    int GetPressureRange();
    char GetOutputType();
};

#endif
