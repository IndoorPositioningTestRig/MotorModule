#include <SoftwareSerial.h>
#include "main.h"

volatile const int MID = 4;
const char mid = '0' + MID;

SoftwareSerial Rs485Serial(6, 5);

bool isMoving = false;

void Moving();
void Listening();

void setup()
{
  setupMotor();
  setupEncoder();
  setupSwitches();

  Rs485Serial.begin(9600);
  Serial.begin(9600);
}
void loop()
{
  if (isMoving)
  {
    Moving();
  }
  else
  {
    Listening();
  }
}

//state functions:
void Listening()
{
  String Command = "";
  bool isReceiving = false;
  if (Rs485Serial.available())
  {
    char c = (char)Rs485Serial.read();
    if (c == '*')
      isReceiving = true;

    while (isReceiving)
    {
      if (Rs485Serial.available())
      {
        c = (char)Rs485Serial.read();
        if (c == '#')
          isReceiving = false;
        else
          Command += c;
      }
    }
  }
  if (Command != "")
  {
    int ProtocolId = -1, ModuleId = -1;
    ProtocolId = Command.substring(0, 1).toInt();
    ModuleId = Command.substring(2, 3).toInt();

    Serial.print("Received: ");
    Serial.println(Command);
    Serial.print("protocolId: ");
    Serial.println(ProtocolId);
    int currentLength, desiredLength, desiredSpeed, Length, Speed;
    getEncoderData(currentLength, desiredLength, desiredSpeed);
    String lengthInMm = String(currentLength);
    String dummy;
    if (ModuleId == MID || ModuleId == 0)
    {
      switch (ProtocolId)
      {
      case 1: // setting length
        Length = Command.substring(Command.indexOf('|', 2) + 1, Command.lastIndexOf('|')).toInt();
        Speed = Command.substring(Command.lastIndexOf('|') + 1, Command.length()).toInt();
        setEncoderData(Length, Speed);
        break;
      case 2: // start moving
        isMoving = true;
        break;
      case 3:
        Rs485Serial.write('*');
        Rs485Serial.write('3');
        Rs485Serial.write('|');
        Rs485Serial.write(mid);
        Rs485Serial.write('|');
        dummy = String(desiredLength);
        for (int i = 0; i < dummy.length(); i++)
          Rs485Serial.write(dummy.charAt(i));
        Rs485Serial.write('#');
        break;
      case 4: // Send length to application
        Rs485Serial.write('*');
        Rs485Serial.write('4');
        Rs485Serial.write('|');
        Rs485Serial.write(mid);
        Rs485Serial.write('|');
        for (int i = 0; i < lengthInMm.length(); i++)
        {
          Rs485Serial.write(lengthInMm.charAt(i));
        }
        Rs485Serial.write('#');
        break;
      case 5: // Set encoder position
        desiredLength = Command.substring(Command.indexOf('|', 2) + 1, Command.lastIndexOf('#')).toInt();
        setEncoderPos(desiredLength);
        break;
      default:
        Serial.print("Received unknown command");
        break;
      }
    }
    else
    {
      Serial.print("Received Wrong destination");
    }
  }
}

void Moving()
{
  bool retractDirection, done;
  int newSpeed;
  getPwmSpeed(newSpeed);
  calculateMotorSpeed(retractDirection, newSpeed, done);

  //int currentLength, desiredLength;
  //getEncoderData(currentLength, desiredLength);

  setMotor(retractDirection, newSpeed);
  if (done)
    isMoving = false;
}