#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#include <TimeLib.h>
#include <WidgetRTC.h>
BlynkTimer timer;
WidgetRTC rtc;

char auth[] = "KndqlGwGYVh7aZOcEEjqy-IfZjv4kP2R";
char ssid[] = "abcd";
char pass[] = "123456789";

char domain[] = "prakitblog.com";

bool alarmSet_on = false; // Status apakah alarm telah diset
int alarmHour_on;
int alarmMinute_on;

bool alarmSet_off = false; // Status apakah alarm telah diset
int alarmHour_off;
int alarmMinute_off;



void setup() 
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass, domain, 8181);
  setSyncInterval(10 * 60); 
  timer.setInterval(10000L, clockDisplay);
}

void loop()
{
  Blynk.run(); 
  timer.run();
  clockDisplay();
}

void clockDisplay()
{
  String currentTime = String(hour()) + ":" + minute() + ":" + second();
  String currentDate = String(day()) + " " + month() + " " + year();
  Serial.print("Current time: ");
  Serial.print(currentTime);
  Serial.print(" ");
  Serial.print(currentDate);
  Serial.println();

  if (alarmSet_on && (hour() == alarmHour_on && minute() == alarmMinute_on)) {
    Serial.println("masuk on");
    delay(1000); // Buzzer berbunyi selama 1 detik
    //digitalWrite(buzzerPin, LOW); // Mematikan buzzer
    alarmSet_on = false; // Reset status alarm agar hanya berbunyi sekali
  }

  if (alarmSet_off && (hour() == alarmHour_off  && minute() == alarmMinute_off )) {
    Serial.println("masuk off");
    delay(1000); // Buzzer berbunyi selama 1 detik
    //digitalWrite(buzzerPin, LOW); // Mematikan buzzer
    alarmSet_off  = false; // Reset status alarm agar hanya berbunyi sekali
  }

}

BLYNK_CONNECTED() 
{
  rtc.begin();
}

BLYNK_WRITE(V0) {
  TimeInputParam t(param);

  // Process start time

  if (t.hasStartTime())
  {
    Serial.println(String("Start: ") +
                   t.getStartHour() + ":" +
                   t.getStartMinute() + ":" +
                   t.getStartSecond());
  }
  else if (t.isStartSunrise())
  {
    Serial.println("Start at sunrise");
  }
  else if (t.isStartSunset())
  {
    Serial.println("Start at sunset");
  }
  else
  {
    // Do nothing
  }

  // Process stop time

  if (t.hasStopTime())
  {
    Serial.println(String("Stop: ") +
                   t.getStopHour() + ":" +
                   t.getStopMinute() + ":" +
                   t.getStopSecond());
  }
  else if (t.isStopSunrise())
  {
    Serial.println("Stop at sunrise");
  }
  else if (t.isStopSunset())
  {
    Serial.println("Stop at sunset");
  }
  else
  {
    // Do nothing: no stop time was set
  }

  // Process timezone
  // Timezone is already added to start/stop time

  Serial.println(String("Time zone: ") + t.getTZ());

  // Get timezone offset (in seconds)
  Serial.println(String("Time zone offset: ") + t.getTZ_Offset());

  // Process weekdays (1. Mon, 2. Tue, 3. Wed, ...)

  for (int i = 1; i <= 7; i++) {
    if (t.isWeekdaySelected(i)) {
      Serial.println(String("Day ") + i + " is selected");
    }
  }

    alarmHour_on = t.getStartHour();
    alarmMinute_on = t.getStartMinute();
    alarmSet_on = true; // Menandakan alarm telah diset
    Serial.println(String("Alarm set for: ") + alarmHour_on + ":" + alarmMinute_on);

    alarmHour_off = t.getStopHour();
    alarmMinute_off = t.getStopMinute();
    alarmSet_off = true; // Menandakan alarm telah diset
    Serial.println(String("Alarm set for: ") + alarmHour_off + ":" + alarmMinute_off);
 

  Serial.println();
}
