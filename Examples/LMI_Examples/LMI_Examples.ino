#include <LMI.h>

void setup()
{
    if(!Serial) { // if user did not begin Serial then we will
        Serial.begin(19200);
        while(!Serial); // wait for Serial to be ready
    }
  
}

void loop()
{
  LMI sensor;
  sensor.begin(0x5f);
  Serial.print("FW Number : ");
  Serial.println(sensor.GetFWVersion());
  Serial.print("Part Number : ");
  Serial.println(sensor.GetPartNumber());
  Serial.print("Lot Number :");
  Serial.println(sensor.GetLotNumber());
  Serial.print("Scale Factor : " );
  Serial.println(sensor.GetScaleFactor());
  Serial.print("Output Type : ");
  Serial.println(sensor.GetOutputType());
  Serial.print("Pressure Range : ");
  Serial.println(sensor.GetPressureRange());
  while(1){   
      Serial.println(sensor.GetPressure());
      delay(1500);
  }
}
            




