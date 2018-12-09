#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

int motion1 = 14;   // Digital pin D5
int motion2 = 12;   // Digital pin D6
int led1 = 13;      // Digital pin D7
int led2 = 15;      // Digital pin D8

int statRoom1;      // Read from motion 1
int statRoom2;      // Read from motion 2
String Status;      // Room Status

// Blynk Application
char auth[] = "xxxxxxxx";
WidgetLCD lcd1(V1);
WidgetLCD lcd2(V2);
BlynkTimer timer;

// Wi-Fi
const char *ssid = "xxxxxxxx";
const char *password = "xxxxxxxx";

void statusRoom(int statRoom, int led, WidgetLCD lcd) {
  if (statRoom == HIGH) {            // Room not empty
    digitalWrite(led, HIGH);
    Status = "Full Room";
  }
  else {                            // Room empty
    digitalWrite(led, LOW);
    Status = "Empty Room";
  }
  Serial.println(Status);
  lcd.clear();
  lcd.print(0, 0, Status);
}

// LCD Widget is blinking
void blinkLcdWidget() {
  statRoom1 = digitalRead(motion1);
  statRoom2 = digitalRead(motion2);

  statusRoom(statRoom1, led1, lcd1);
  statusRoom(statRoom2, led2, lcd2);
}

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, password);

  timer.setInterval(1000L, blinkLcdWidget);       // Detect every 10 second

  pinMode(motion1, INPUT);
  pinMode(motion2, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {
  Blynk.run();
  timer.run();
}
