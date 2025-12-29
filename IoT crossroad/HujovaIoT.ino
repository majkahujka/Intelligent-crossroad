#define BLYNK_TEMPLATE_ID "TMPL4mtUHjySF"
#define BLYNK_TEMPLATE_NAME "LED ESP32 1"
#define BLYNK_FIRMWARE_VERSION "0.1.0"

#define BLYNK_PRINT Serial
#define APP_DEBUG

#include <WiFi.h>
#include "BlynkEdgent.h"
#include <time.h>

// ====== Piny ======
#define OUT_D2_PIN   13      // výstup podľa tvojho riadenia
#define OUT_D4_PIN   4      // svetlo < 50% => ON
#define ADC_PIN      34     // ADC

// ====== Virtual piny ======
#define VPIN_V0   V0   // automatika
#define VPIN_V1   V1   // manual (noc/den)
#define VPIN_V2   V2   // sync času
#define VPIN_V3   V3   // svetlo %
#define VPIN_V4   V4   // čas text

BlynkTimer timer;

// stavy z appky
int v0_state = 0;
int v1_state = 0;
int lightPct = 0;

// ---- NTP sync (len keď dáš V2=1) ----
void syncTimeNow()
{
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("[TIME] WiFi nie je pripojene");
    return;
  }

  // Bratislava CET/CEST
  setenv("TZ", "CET-1CEST,M3.5.0/2,M10.5.0/3", 1);    //verejne znamy prikaz 
  tzset();

  configTime(0, 0, "pool.ntp.org", "time.google.com", "time.nist.gov");
  Serial.println("[TIME] NTP init");
}

// ---- tvoje riadenie + D4 podľa svetla ----
void riadenie()
{
  // D4: podľa svetla
  if (lightPct < 50) digitalWrite(OUT_D4_PIN, HIGH);
  else              digitalWrite(OUT_D4_PIN, LOW);

  // D2: tvoja logika
  if (v0_state == 1)
  {
    struct tm t;
    if (getLocalTime(&t, 50))
    {
      if (t.tm_hour >= 20 || t.tm_hour < 6)
        digitalWrite(OUT_D2_PIN, HIGH);
      else
        digitalWrite(OUT_D2_PIN, LOW);
    }
    // ak čas nie je dostupný, nemením D2
  }
  else
  {
    if (v1_state == 1) digitalWrite(OUT_D2_PIN, HIGH);
    else               digitalWrite(OUT_D2_PIN, LOW);
  }
}

// ---- ADC -> V3 ----
void sendLightToV3()
{
  int raw = analogRead(ADC_PIN);      // 0..4095
  lightPct = (raw * 100) / 4095;      // 0..100
  Blynk.virtualWrite(VPIN_V3, lightPct);
}

// ---- čas -> V4 ----
void sendTimeToV4()
{
  struct tm t;
  if (!getLocalTime(&t, 50)) {
    Blynk.virtualWrite(VPIN_V4, "NO TIME");
    return;
  }

  char buf[32];
  strftime(buf, sizeof(buf), "%d.%m.%Y %H:%M:%S", &t);
  Blynk.virtualWrite(VPIN_V4, buf);
}

// ---- vypis stavu (ak chceš každú sekundu) ----
void printStatus()
{
  struct tm t;
  bool ok = getLocalTime(&t, 10);

  Serial.print("[STAV] V0=");
  Serial.print(v0_state);
  Serial.print(" V1=");
  Serial.print(v1_state);
  Serial.print(" D2=");
  Serial.print(digitalRead(OUT_D2_PIN));
  Serial.print(" D4=");
  Serial.print(digitalRead(OUT_D4_PIN));
  Serial.print(" LIGHT%=");
  Serial.print(lightPct);
  Serial.print(" TIME=");
  if (ok) {
    Serial.print(t.tm_hour); Serial.print(":");
    Serial.print(t.tm_min);  Serial.print(":");
    Serial.print(t.tm_sec);
  } else {
    Serial.print("NO_TIME");
  }
  Serial.println();
}

// ====== Blynk inputy ======
BLYNK_WRITE(VPIN_V0) { v0_state = param.asInt(); }
BLYNK_WRITE(VPIN_V1) { v1_state = param.asInt(); }

BLYNK_WRITE(VPIN_V2)
{
  if (param.asInt() == 1) syncTimeNow();
}

BLYNK_CONNECTED()
{
  Serial.println("[BLYNK] Connected");
  Blynk.syncVirtual(VPIN_V0, VPIN_V1);
  //syncTimeNow(); // zisti čas hneď na začiatku
}

void setup()
{
  Serial.begin(115200);
  delay(100);

  pinMode(OUT_D2_PIN, OUTPUT);
  pinMode(OUT_D4_PIN, OUTPUT);
  digitalWrite(OUT_D2_PIN, LOW);
  digitalWrite(OUT_D4_PIN, LOW);

  analogReadResolution(12);
  analogSetPinAttenuation(ADC_PIN, ADC_11db);

  BlynkEdgent.begin();

  // 1x za sekundu urob všetko potrebné
  timer.setInterval(1000L, []() {
    sendLightToV3();
    sendTimeToV4();
    riadenie();
    printStatus();   // ak nechceš výpis, túto riadku vymaž
  });
}

void loop()
{
  BlynkEdgent.run();
  timer.run();
}
