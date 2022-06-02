
#include <Wire.h>
#include <SparkFun_Qwiic_OpenLog_Arduino_Library.h>
#include <SparkFun_LPS25HB_Arduino_Library.h>
#include <Servo.h>

//this sets up the sensor board, datalog and the servo
LPS25HB sensorBoard;
OpenLog dataLog;
Servo myservo;

//these are my data types i have my "end position" and "start position" as intergers and setting up my servo to pin 9 as a const
int spos = 0;
int epos = 90;
const byte pressue = 1000;
const byte SERVO_PIN = 9;

//this is setting up the serial monitor. starting the datalog, sensorboard.
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

//these are the if statments, it makes sure the sensorboard is connected and it grabs the status of it
void loop()
{

  if (sensorBoard.isConnected() == true)
  {
    if (sensorBoard.getStatus() == 0x00)
    {
      sensorBoard.begin();
    }
    //this prints to my serial monitor the hpa and the temp
    Serial.print("Pressure (hPa): ");
    Serial.print(sensorBoard.getPressure_hPa());
    Serial.print(", Temperature (degC): ");
    Serial.println(sensorBoard.getTemperature_degC());

    //this gets the all of the data onto the sync file
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

  //if statment to get my shute to open
  //if (getPressure_hPa < 1031) 
  //{deployShute ();
  }
 // else { 
   // SERVO_PIN.write(ShuteClose);
 // }
 {
    myservo.write(epos);
  }
}
