#include "LMI.h"

LMI::LMI(){

  if (TWCR == 0) // do this check so that Wire only gets initialized once
  {
     Wire.begin();
  }

}

void LMI::begin(int Address){
  address = Address;
  GetSignature();
}

void LMI::GetSignature(){
  char raw_data[54];
  int count = 0;
  if (address == 0x00){
    return;
  }
  Wire.beginTransmission(address);
  Wire.write(0x23);
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
    PartNumber += String(raw_data[count++]);
  }
  LotNumber = "";
  while (count < 20){
    LotNumber += String(raw_data[count++]);
  }
  PressureRange =raw_data[count++] <<8 | raw_data[count++];
  OutputType = raw_data[count++];
  scale_factor = raw_data[count++] <<8 | raw_data[count++];
}

int16_t LMI::GetPressureCount(){
  int i = 0;
  if (address == 0x00){
    return;
  }
  Wire.beginTransmission(address);
  Wire.write(0x20);
  byte error = Wire.endTransmission();

  Wire.beginTransmission(address);
  Wire.requestFrom(address,2,true);
  i =  Wire.read();
  return Wire.read() << 8 | i;
}

float LMI::GetPressure(){
  return (float)GetPressureCount() / (float) scale_factor;
}

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
