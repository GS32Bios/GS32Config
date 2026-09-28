#include <Arduino.h>
#include <GS32Config.h>

GS32Config config;

char ssid[32];
int channel = 1;
bool dhcpEnabled = true;
int8_t retryCount = 3;
uint8_t authMode = 0;

void setup() {
  Serial.begin(115200);

  // Открыть пространство имён в NVS.
  if (!config.begin("mydevice_cfg")) {
    Serial.println("Не удалось открыть NVS");
    return;
  }

  // Зарегистрировать настройки и их значения по умолчанию.
  config.addText("ssid", ssid, sizeof(ssid), "MyHomeWiFi");
  config.addInt("channel", &channel, 1);
  config.addBool("dhcp", &dhcpEnabled, true);
  config.addInt8("retries", &retryCount, 3);
  config.addUInt8("auth", &authMode, 0);

  // Загрузить сохранённые настройки.
  config.load();

  Serial.printf("SSID: %s\n", ssid);
  Serial.printf("Channel: %d\n", channel);
}

void loop() {
}