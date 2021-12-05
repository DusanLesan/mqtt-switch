#include <WiFi.h>
#include <PubSubClient.h>
#include "src/cred.h"

#define PUSH_TIME 400
#define PWR_PIN 12
#define LED_BUILTIN 2

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

void connectToWiFi() {
	Serial.print("Connectig to ");

	WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
	Serial.println(WIFI_SSID);

	while (WiFi.status() != WL_CONNECTED) {
		Serial.print(".");
		delay(500);
	}

	Serial.println("Connected.");
}

void setupMQTT() {
	mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
	mqttClient.setCallback(callback);
	mqttClientConnect();
}

void mqttClientConnect() {
	while (!mqttClient.connected()) {
		Serial.print("Attempting MQTT connection...");
		String clientId = "ESP32Client-";
		clientId += String(random(0xffff), HEX);
		if (mqttClient.connect(clientId.c_str(), MQTT_USER, MQTT_PASSWORD)) {
			Serial.println("connected");
			mqttClient.subscribe(MQTT_SUB_TOPIC);
		} else {
			Serial.print("failed, rc=");
			Serial.print(mqttClient.state());
			Serial.println(" try again in 5 seconds");
			delay(5000);
		}
	}
}

void callback(char* topic, byte *payload, unsigned int length) {
	String message;

	for (int i = 0; i < length; i++) {
		char c = (char)payload[i];
		message += c;
	}
	if (message == MQTT_MESSAGE) {
		Serial.println(message);
		togglePin(PWR_PIN, PUSH_TIME);
	}
	message = "";
	Serial.flush();
}

void togglePin(int pin, int ms) {
	digitalWrite(LED_BUILTIN, HIGH);
	digitalWrite(pin, LOW);
	pinMode(pin, OUTPUT);
	delay(ms);
	pinMode(pin, INPUT);
	digitalWrite(LED_BUILTIN, LOW);
}

void setup() {
	Serial.begin(115200);
	setCpuFrequencyMhz(80);
	pinMode(LED_BUILTIN, OUTPUT);

	connectToWiFi();
	setupMQTT();
}

void loop() {
	if (!mqttClient.connected()) {
		mqttClientConnect();
	}
	mqttClient.loop();
}
