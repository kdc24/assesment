
#include <Wire.h>
#include <SparkFun_Qwiic_OpenLog_Arduino_Library.h>
#include <SparkFun_LPS25HB_Arduino_Library.h>
#include <Servo.h>

//----------------------------
//
//----------------------------
LPS25HB sensorBoard;
OpenLog dataLog;
Servo myservo;

//----------------------------
//
//----------------------------
int spos = 0;
int epos = 90;
const byte SERVO_PIN = 9;

//----------------------------
//
//----------------------------
void setup()
{
  Serial.begin(9600);

  myservo.attach(SERVO_PIN);
  Wire.begin();
  dataLog.begin();
  sensorBoard.begin(Wire, LPS25HB_I2C_ADDR_DEF);
  dataLog.append("Kade.txt");
  dataLog.println("Pressure, Temp");
  myservo.write(spos);
}

//----------------------------
//
//----------------------------
void loop()
{

  if (sensorBoard.isConnected() == true)
  {
    if (sensorBoard.getStatus() == 0x00)
    {
      sensorBoard.begin();
    }
    //----------------------------
    //
    //----------------------------
    Serial.print("Pressure (hPa): ");
    Serial.print(sensorBoard.getPressure_hPa());
    Serial.print(", Temperature (degC): ");
    Serial.println(sensorBoard.getTemperature_degC());

    //----------------------------
    //
    //----------------------------
    dataLog.print(sensorBoard.getPressure_hPa());
    dataLog.print(",");
    dataLog.println(sensorBoard.getTemperature_degC());
    dataLog.syncFile();

  }
  else
  {
    Serial.println("Disconnected");
    sensorBoard.begin();
  }
  delay(100);

  //----------------------------
  //
  //----------------------------
  //   if () // when should i deploy the chute? // millis()
  {
    myservo.write(epos);
  }
}
