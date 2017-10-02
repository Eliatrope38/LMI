# LMI Libraries
Arduino Librairie for use LMI Pressure Sensor from First Sensor
[LMI Datasheet](https://www.first-sensor.com/en/products/pressure-sensors/pressure-sensors-and-transmitters/amplified-pressure-sensors/lmi/index.html)

#Libraries Description

* Initialisation with Address
```
void begin(int Address);

```
* Get Pressure Value in Pascal
```
float GetPressure();
```
* Get Pressure Value in count
```
int16_t GetPressureCount(); // Pressure in count
```
* Get Hardware information like Firware Number, Part Number etc...
```
String GetFWVersion();
String GetPartNumber();
String GetLotNumber();
unsigned int GetScaleFactor(); // factor used to go to Pa Value
int GetPressureRange();
char GetOutputType();
```
