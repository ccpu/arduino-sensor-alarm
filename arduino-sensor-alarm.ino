#include <neotimer.h>

Neotimer timer;

int led = 13;
int vs = 7; // vibration sensor
bool active = false;
int period = 1000;

int alarm_count = 0;

void setup()
{
  pinMode(led, OUTPUT);
  pinMode(vs, INPUT);
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
    active = true;
    if (alarm_count == 0)
    {
      timer.start();
    }
    alarm_count = 10;
  }

  if (active == true)
  {
    if (alarm_count != 0)
    {
      if (timer.done())
      {
        alarm_count = alarm_count - 1;
        Serial.println(alarm_count);
        timer.start();
        digitalWrite(led, HIGH);
      }
      else
      {
        digitalWrite(led, LOW);
      }
    }
    else
    {
      active = false;
      digitalWrite(led, LOW);
    }
  }
}

long vibration()
{
  long measurement = pulseIn(vs, HIGH); //wait for the pin to get HIGH and returns measurement
  return measurement;
}