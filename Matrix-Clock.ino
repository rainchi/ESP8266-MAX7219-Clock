#include <ESP8266WiFi.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>
#include <time.h>

int pinCS = D6;
int numberOfHorizontalDisplays = 4;
int numberOfVerticalDisplays   = 1;
char time_value[6];
Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

void setup() {
  configTime(8 * 3600, 0, "time.stdtime.gov.tw", "asia.pool.ntp.org");

  matrix.setIntensity(4); // Use a value between 0 and 15 for brightness
  matrix.setRotation(0, 1);    // The first display is position upside down
  matrix.setRotation(1, 1);    // The first display is position upside down
  matrix.setRotation(2, 1);    // The first display is position upside down
  matrix.setRotation(3, 1);    // The first display is position upside down
  matrix.fillScreen(LOW);
  matrix.write();
  WiFi.mode(WIFI_STA);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    WiFi.disconnect();
    WiFi.begin("AndroidAp71d", "Age732104");
    WiFi.setAutoConnect(true);
    WiFi.setAutoReconnect(true);
  }
  while ( WiFi.status() != WL_CONNECTED ) {
    matrix.drawChar(2, 0, 'W', HIGH, LOW, 1); // H
    matrix.drawChar(8, 0, 'I', HIGH, LOW, 1); // HH
    matrix.drawChar(14, 0, '-', HIGH, LOW, 1); // HH:
    matrix.drawChar(20, 0, 'F', HIGH, LOW, 1); // HH:M
    matrix.drawChar(26, 0, 'I', HIGH, LOW, 1); // HH:MM
    matrix.write(); // Send bitmap to display
    delay(250);
    matrix.fillScreen(LOW);
    matrix.write();
    delay(250);
  }
}

void loop() {
  matrix.fillScreen(LOW);
  time_t now = time(nullptr);
  String time = String(ctime(&now));
  time.trim();
  time.substring(11, 16).toCharArray(time_value, 6);
  matrix.drawChar(2, 0, time_value[0], HIGH, LOW, 1); // H
  matrix.drawChar(9, 0, time_value[1], HIGH, LOW, 1); // HH
  matrix.drawChar(14, 0, time_value[2], HIGH, LOW, 1); // HH:
  matrix.drawChar(18, 0, time_value[3], HIGH, LOW, 1); // HH:M
  matrix.drawChar(25, 0, time_value[4], HIGH, LOW, 1); // HH:MM
  matrix.write(); // Send bitmap to display
  delay(100);
}
