/*
 * ESP32 + SIM800L MQTT Data Logger
 * Sends Temperature (DS18B20) and TDS data via GSM using MQTT
 * 
 * Author: Yodha Ardiansyah
 * Website: https://arunovasi.my.id
 */

#define TINY_GSM_MODEM_SIM800

#include <TinyGsmClient.h>
#include <PubSubClient.h>
#include <SoftwareSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// --- GSM Module Configuration ---
SoftwareSerial SerialAT(34, 32); // RX, TX for SIM800L communication
#define SerialMon Serial

// --- GPRS/APN Configuration ---
const char apn[] = "your_apn";  // Replace with your APN
const char user[] = "";         // APN username (if required)
const char pass[] = "";         // APN password (if required)

// --- MQTT Configuration ---
const char* mqttServer = "your_mqtt_broker";  // Replace with your MQTT broker
const int mqttPort = 1883;
const char* mqttUser = "your_mqtt_user";      // Replace with your MQTT username
const char* mqttPassword = "your_mqtt_pass";  // Replace with your MQTT password
const char* topicTemperature = "home/temperature"; 
const char* topicTDS = "home/tds";

// --- Initialize GSM & MQTT Client ---
TinyGsm modem(SerialAT);
TinyGsmClient gsmClient(modem);
PubSubClient mqttClient(gsmClient);

// --- Sensor Configuration ---
#define DS18B20_PIN 15  // DS18B20 Data Pin
#define TDS_PIN 35      // TDS Sensor Analog Input

OneWire oneWire(DS18B20_PIN);
DallasTemperature sensors(&oneWire);

float tdsValue = 0;
float voltage = 0;
float tdsFactor = 0.5;  // Adjust based on sensor calibration

void setup() {
    // --- Initialize Serial Monitor ---
    SerialMon.begin(115200);
    delay(10);

    // --- Initialize GSM Module ---
    SerialMon.println("Initializing GSM...");
    SerialAT.begin(9600);
    delay(3000);

    // Restart modem and connect to GPRS
    modem.restart();
    SerialMon.println("Connecting to GPRS...");
    if (!modem.gprsConnect(apn, user, pass)) {
        SerialMon.println("Failed to connect to GPRS");
        while (true);
    }
    SerialMon.println("GPRS connected!");

    // --- Setup MQTT Client ---
    mqttClient.setServer(mqttServer, mqttPort);

    // --- Initialize DS18B20 Sensor ---
    sensors.begin();
}

void reconnect() {
    // Attempt to reconnect until successful
    while (!mqttClient.connected()) {
        SerialMon.println("Connecting to MQTT...");
        if (mqttClient.connect("SIM800LClient", mqttUser, mqttPassword)) {
            SerialMon.println("Connected to MQTT!");
        } else {
            SerialMon.print("MQTT connection failed, state: ");
            SerialMon.println(mqttClient.state());
            delay(5000);
        }
    }
}

void loop() {
    // Reconnect to MQTT broker if disconnected
    if (!mqttClient.connected()) {
        reconnect();
    }
    mqttClient.loop();

    // --- Read Temperature from DS18B20 ---
    sensors.requestTemperatures();
    float temperature = sensors.getTempCByIndex(0);
    if (temperature != -127.00) {
        SerialMon.print("Temperature: ");
        SerialMon.print(temperature);
        SerialMon.println(" °C");

        String temperatureStr = String(temperature);
        mqttClient.publish(topicTemperature, temperatureStr.c_str());
    } else {
        SerialMon.println("Error: DS18B20 Sensor not detected!");
    }

    // --- Read TDS Sensor Data ---
    int analogValue = analogRead(TDS_PIN);
    voltage = analogValue * (3.3 / 4095.0);  // ESP32 ADC (0-3.3V)
    tdsValue = voltage * tdsFactor * 1000;   // Convert voltage to TDS (ppm)

    SerialMon.print("TDS Value: ");
    SerialMon.print(tdsValue);
    SerialMon.println(" ppm");

    String tdsValueStr = String(tdsValue);
    mqttClient.publish(topicTDS, tdsValueStr.c_str());

    delay(2000);
}
