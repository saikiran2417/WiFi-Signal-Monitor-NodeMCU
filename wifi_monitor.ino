#include <ESP8266WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const char* ssid = "iPhone";
const char* password = "11223344";

#define LED1 D5
#define LED2 D6
#define LED3 D7
#define BUZZER D0

void setup() {
  Serial.begin(115200);

  Wire.begin(D2, D1);
  lcd.init();
  lcd.backlight();

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  lcd.print("Connecting WiFi");

  WiFi.begin(ssid, password);
  int tries = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    tries++;
    if (tries > 20) {
      lcd.clear();
      lcd.print("WiFi Failed!");
      while(true) { delay(100); }
    }
  }

  lcd.clear();
  lcd.print("Connected");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());
  delay(2000);
  lcd.clear();

  Serial.println("\nScanning...");
  int n = WiFi.scanNetworks();
  int bestRSSI = -1000;
  String bestSSID = "";

  for (int i = 0; i < n; i++) {
    Serial.print(WiFi.SSID(i));
    Serial.print(" | RSSI: ");
    Serial.println(WiFi.RSSI(i));
    if (WiFi.RSSI(i) > bestRSSI) {
      bestRSSI = WiFi.RSSI(i);
      bestSSID = WiFi.SSID(i);
    }
  }

  Serial.println("Best Network:");
  Serial.print(bestSSID);
  Serial.print(" (");
  Serial.print(bestRSSI);
  Serial.println(" dBm)");
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    lcd.setCursor(0, 1);
    lcd.print("WiFi Lost     ");
    digitalWrite(BUZZER, HIGH);
    return;
  }

  int rssi = WiFi.RSSI();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("RSSI:");
  lcd.print(rssi);
  lcd.print(" dBm");

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(BUZZER, LOW);

  lcd.setCursor(0, 1);

  if (rssi > -65) {
    lcd.print("Strong [|||]");
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
  }
  else if (rssi > -75) {
    lcd.print("Medium [|| ]");
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(BUZZER, HIGH);
    delay(200);
    digitalWrite(BUZZER, LOW);
    delay(800);
  }
  else {
    lcd.print("Weak [|  ]");
    delay(1000);
    lcd.setCursor(0, 1);
    lcd.print("Weak Zone   ");
    digitalWrite(LED1, HIGH);
    digitalWrite(BUZZER, HIGH);
  }

  delay(300);
}