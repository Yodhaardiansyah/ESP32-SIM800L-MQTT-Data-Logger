Here’s an attractive and well-structured **README.md** for your project:  

---

# **ESP32 + SIM800L MQTT Data Logger**  
📡 **Real-time Temperature & TDS Monitoring via GSM & MQTT**  

![IoT Banner](https://user-images.githubusercontent.com/your-image-url/banner.jpg) *(Replace with your actual image URL)*  

## **🔹 Overview**  
This project utilizes an **ESP32** and **SIM800L GSM module** to collect **temperature** (DS18B20) and **TDS** (Total Dissolved Solids) data, sending it to an **MQTT broker** over a cellular network.  

✅ **Features:**  
- 📶 **GPRS-based communication** (No need for WiFi)  
- 🌡️ **DS18B20 Temperature Sensor** support  
- 💧 **TDS sensor** for water quality monitoring  
- ☁️ **MQTT integration** for real-time data updates  
- 🔧 **Customizable & scalable** for IoT applications  

---

## **🛠️ Hardware Requirements**
| Component | Description |
|-----------|------------|
| ESP32 Dev Board | Microcontroller |
| SIM800L Module | GSM/GPRS Communication |
| DS18B20 Sensor | Temperature Sensor |
| TDS Sensor | Water Quality Measurement |
| Power Supply | 5V 2A for SIM800L stability |

---

## **📜 Circuit Diagram**  
*(Insert a diagram image or link here, e.g., Fritzing design)*  

### **Pin Connections:**  

| Component | ESP32 Pin |
|-----------|----------|
| SIM800L TX | GPIO 32 |
| SIM800L RX | GPIO 34 |
| DS18B20 Data | GPIO 15 |
| TDS Analog | GPIO 35 |
| SIM800L VCC | 5V |
| SIM800L GND | GND |

---

## **📦 Software Requirements**
- **Arduino IDE** (or **PlatformIO**)
- **ESP32 Board Package**
- **Required Libraries:**
  - [`TinyGSM`](https://github.com/vshymanskyy/TinyGSM)
  - [`PubSubClient`](https://github.com/knolleary/pubsubclient)
  - [`OneWire`](https://github.com/PaulStoffregen/OneWire)
  - [`DallasTemperature`](https://github.com/milesburton/Arduino-Temperature-Control-Library)

📌 **Install these libraries in Arduino IDE via Library Manager.**

---

## **🚀 Setup & Usage**
### **1️⃣ Configure the Code**
Before uploading, **replace placeholders** in `setup()` with your credentials:
```cpp
const char apn[] = "your_apn";  // Replace with your APN
const char* mqttServer = "your_mqtt_broker";
const char* mqttUser = "your_mqtt_user";
const char* mqttPassword = "your_mqtt_pass";
```

### **2️⃣ Upload the Code**
- Select **ESP32** as the board in **Arduino IDE**.
- Choose the correct **COM port**.
- Click **Upload**.

### **3️⃣ Monitor Output**
- Open **Serial Monitor** (115200 baud rate) to debug.
- View data on your **MQTT broker**.

---

## **📊 Data Output Example**
🔍 **Serial Monitor Output:**
```
Initializing GSM...
GPRS connected!
Connecting to MQTT...
Connected to MQTT!
Temperature: 27.5 °C
TDS Value: 450.0 ppm
```

📡 **MQTT Broker Data:**
```json
{
  "temperature": 27.5,
  "tds": 450.0
}
```

---

## **🛠️ Troubleshooting**
🔹 **SIM800L Not Connecting?**
- Check **power supply** (5V 2A recommended).  
- Ensure **APN settings** are correct.  

🔹 **No Sensor Data?**
- Verify **wiring connections**.  
- Try a different **GPIO pin**.  

🔹 **MQTT Connection Fails?**
- Ensure **broker credentials** are correct.  
- Check **network signal strength**.  

---

## **📜 License**
This project is open-source under the **MIT License**.  

---

## **👤 Credits**
Developed by **Yodha Ardiansyah**  
🔗 [arunovasi.my.id](https://arunovasi.my.id)  

🚀 **Happy Coding!** 🚀
