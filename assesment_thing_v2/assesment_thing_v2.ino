
#include <Wire.h>
#include "SparkFun_Qwiic_OpenLog_Arduino_Library.h"
#include <SparkFun_LPS25HB_Arduino_Library.h> // Click here to get the library: http://librarymanager/All#SparkFun_LPS25HB
LPS25HB sensorBoard; // Create an object of the LPS25HB class
OpenLog dataLog;

const byte hPa = 8;

//test
void setup()
{
  Serial.begin(9600);


  Wire.begin();
  dataLog.begin();
  sensorBoard.begin(Wire, LPS25HB_I2C_ADDR_DEF); // Begin with I2C settings of your choice (see Example2_I2C_Configuration)
  dataLog.append("Kade.txt");
  dataLog.println("Pressure, Temp");

}

void loop()
{

  if (sensorBoard.isConnected() == true)
  {
    if (sensorBoard.getStatus() == 0x00)
    {
      sensorBoard.begin();
    } // If it is connected but not responding (for example after a hot-swap) then it may need to be re-initialized
    Serial.print(", Pressure (hPa): ");
    Serial.print(sensorBoard.getPressure_hPa()); // Get the pressure reading in hPa as determined by dividing the number of ADC counts by 4096 (according to the datasheet)
    Serial.print(", Temperature (degC): ");
    Serial.println(sensorBoard.getTemperature_degC()); // Get the temperature in degrees C by dividing the ADC count by 480
    dataLog.print(", Pressure (hPa): ");
    dataLog.print(sensorBoard.getPressure_hPa()); // Get the pressure reading in hPa as determined by dividing the number of ADC counts by 4096 (according to the datasheet)
    dataLog.print(", Temperature (degC): ");
    dataLog.println(sensorBoard.getTemperature_degC()); // Get the temperature in degrees C by dividing the ADC count by 480
    dataLog.syncFile();

  }
  else
  {
    Serial.println("Disconnected");
    sensorBoard.begin();
  }
  delay(100);
}
