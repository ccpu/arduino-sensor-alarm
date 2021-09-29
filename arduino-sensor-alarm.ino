#include <neotimer.h>

Neotimer timer;

int RELAY_PIN = 13;
int SENSOR_1 = 7; // vibration sensor
bool SENSOR_ACTIVE = false;
int ALARM_COUNT = 0;
bool ALARMING_ACTIVE = false;

void setup()
{
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(SENSOR_1, INPUT);
  Serial.begin(9600);
  timer = Neotimer(1000);
  Serial.println("Ready");
}
void loop()
{
  long measurement = vibration();
  delay(50);
  if (measurement > 50)
  {
    SENSOR_ACTIVE = true;
    if (ALARM_COUNT == 0)
    {
      timer.start();
    }
    ALARM_COUNT = 10;
  }

  if (SENSOR_ACTIVE == true)
  {
    if (ALARM_COUNT != 0)
    {
      if (timer.done())
      {

        if (ALARMING_ACTIVE)
        {
          ALARMING_ACTIVE = false;
          digitalWrite(RELAY_PIN, LOW);
        }
        else
        {
          ALARMING_ACTIVE = true;
          digitalWrite(RELAY_PIN, HIGH);
        }

        ALARM_COUNT = ALARM_COUNT - 1;
        Serial.println(ALARM_COUNT);
        timer.start();
      }
    }
    else
    {
      SENSOR_ACTIVE = false;
      ALARMING_ACTIVE = false;
      digitalWrite(RELAY_PIN, LOW);
    }
  }
}

long vibration()
{
  long measurement = pulseIn(SENSOR_1, HIGH); //wait for the pin to get HIGH and returns measurement
  return measurement;
}
