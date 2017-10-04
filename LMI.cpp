
/***************************************************
  This is a library for the First Sensor LMI Pressure sensor
  Designed specifically to work with the LMI
  ---->https://www.first-sensor.com/en/products/pressure-sensors/pressure-sensors-and-transmitters/amplified-pressure-sensors/lmi/index.html
***************************************************/

#include "LMI.h"

LMI::LMI(){
  // Check if Wire already initialized
  if (TWCR == 0)
  {
     Wire.begin();
  }
}

void LMI::begin(int Address){
  address = Address;
  // read electonics information from sensor
  GetSignature();
}

// read electonics information from sensor
void LMI::GetSignature(){
  byte raw_data[54];
  int count = 0;
  if (address == 0x00){
    return;
  }
  Wire.beginTransmission(address);
  Wire.write(SIGNATURE_REGISTER);
  byte error = Wire.endTransmission();

  Wire.beginTransmission(address);
  Wire.requestFrom(address,54,true);
  while(Wire.available()) {
      raw_data[count] = Wire.read();
      Raw_Data += String(raw_data[count++],DEC);
      Raw_Data += ",";
      if (count == 54)
        break;
  }
  Wire.endTransmission();
  count = 0;
  // Parse Raw Data for filling Value
  FW_Version = "";
  FW_Version += String(raw_data[count++],DEC);
  FW_Version += '.';
  FW_Version += String(raw_data[count++],DEC);
  PartNumber = "";
  while (count < 13){
    PartNumber += (char)raw_data[count++];
  }
  LotNumber = "";
  while (count < 20){
    LotNumber += (char)raw_data[count++];
  }
  PressureRange =raw_data[count++] <<8 | raw_data[count++];
  OutputType = (char)raw_data[count++];
  scale_factor = raw_data[count++] <<8 | raw_data[count++];
  SerialNumber = (char)raw_data[count++];
  SerialNumber += (char)raw_data[count++];
  SerialNumber += String(raw_data[count++],DEC);
  SerialNumber += String(raw_data[count++],DEC);
  SerialNumber += String(raw_data[count++],DEC);
  SerialNumber += String(raw_data[count++],DEC);
}

// read pressure count from LMI
int16_t LMI::GetPressureCount(){
  int i = 0;
  if (address == 0x00){
    return;
  }
  Wire.beginTransmission(address);
  Wire.write(PRESSURE_REGISTER);
  byte error = Wire.endTransmission();

  Wire.beginTransmission(address);
  Wire.requestFrom(address,2,true);
  i =  Wire.read();
  return Wire.read() << 8 | i;
}

// get Pressure value in Pascal based on count / scale factor
float LMI::GetPressure(){
  return (float)GetPressureCount() / (float) scale_factor;
}

// return output type U : Unidirectionnal - B : Bidirectionnal
char LMI::GetOutputType(){
  return OutputType;
}

String LMI::GetFWVersion(){
  return FW_Version;
}

String LMI::GetPartNumber(){
  return PartNumber;
}

String LMI::GetLotNumber(){
  return LotNumber;
}

unsigned int LMI::GetScaleFactor(){
  return scale_factor;
}

int LMI::GetPressureRange(){
  return PressureRange;
}

String LMI::GetSerialNumber(){
  return SerialNumber;
}
