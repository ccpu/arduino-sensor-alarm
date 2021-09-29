#include <neotimer.h>

Neotimer timer;

int RELAY_PIN = 12;
int SENSOR_1 = 7; // vibration sensor
bool SENSOR_ACTIVE = false;
int ALARM_COUNT = 0;
int MAX_ALARM = 10;
bool RELAY_ON = false;
bool ALARM_ACTIVATION_PIN = 2;

void setup()
{
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(SENSOR_1, INPUT);
  Serial.begin(9600);
  timer = Neotimer(1000);
  Serial.println("Ready");
  delay(100);
  digitalWrite(RELAY_PIN, HIGH);
}
void loop()
{

  // if (digitalRead(ALARM_ACTIVATION_PIN) == LOW)
  // {
  //   return;
  // }

  long measurement = vibration();
  delay(50);
  if (measurement > 50)
  {
    SENSOR_ACTIVE = true;
    if (ALARM_COUNT == 0)
    {
      alarmOn();
      timer.start();
    }
    ALARM_COUNT = (MAX_ALARM * 2) - 1;
  }

  if (SENSOR_ACTIVE == true)
  {
    if (ALARM_COUNT != 0)
    {
      if (timer.done())
      {

        if (RELAY_ON)
        {
          alarmOff();
        }
        else
        {
          alarmOn();
        }

        ALARM_COUNT = ALARM_COUNT - 1;
        Serial.println(ALARM_COUNT);
        timer.start();
      }
    }
    else
    {
      if (timer.done())
      {
        SENSOR_ACTIVE = false;
        alarmOff();
      }
    }
  }
}

void alarmOn()
{
  RELAY_ON = true;
  digitalWrite(RELAY_PIN, LOW);
}

void alarmOff()
{
  RELAY_ON = false;
  digitalWrite(RELAY_PIN, HIGH);
}

long vibration()
{
  long measurement = pulseIn(SENSOR_1, HIGH); //wait for the pin to get HIGH and returns measurement
  return measurement;
}
