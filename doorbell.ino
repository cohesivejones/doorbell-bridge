#include <WiFi.h>
#include <HTTPClient.h>
#include "config.h"

void connectToWifi()
{
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

void GPIO_wake_up()
{
  esp_sleep_wakeup_cause_t wakeup_reason = esp_sleep_get_wakeup_cause();
  if (wakeup_reason != ESP_SLEEP_WAKEUP_EXT0)
  {
    return;
  }
  Serial.println("Doorbell ON");
  delay(4000);
}

void setup()
{
  Serial.begin(9600);
  while (!Serial)
    ;

  GPIO_wake_up();
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_4, HIGH);
  Serial.println("Going to sleep...");
  esp_deep_sleep_start();
}

void loop()
{
}