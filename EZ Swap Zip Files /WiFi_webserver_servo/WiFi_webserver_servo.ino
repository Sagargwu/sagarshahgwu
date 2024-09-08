#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <ESP32Servo.h>

const char* ssid = "moto";
const char* password = "snorlax24";

AsyncWebServer server(80);

Servo servo1;  // Servo motor for Slot 1 (D12)
Servo servo2;  // Servo motor for Slot 2 (D13)

const int currentSensorPin1 = 26;  // Current Sensor 1 connected to D26
const int currentSensorPin2 = 32;  // Current Sensor 2 connected to D32
const int voltageSensorPin = 33;   // Voltage Sensor connected to D33

// Variables to store sensor readings
int sensor1_current = 0;
int sensor2_current = 0;
int voltage = 0;

// Function prototypes
void handleServoControl(AsyncWebServerRequest *request);
void fetchSensorData(AsyncWebServerRequest *request);

void setup() {
  Serial.begin(115200);

  // Initialize SPIFFS
  if (!SPIFFS.begin()) {
    Serial.println("Failed to mount SPIFFS");
    return;
  }

  // Initialize servos
  servo1.attach(12); // D12
  servo2.attach(13); // D13

  pinMode(currentSensorPin1, INPUT);
  pinMode(currentSensorPin2, INPUT);
  pinMode(voltageSensorPin, INPUT);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Route for serving the index.html file (Home Page)
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/html/index.html", "text/html");
  });

  // Route for serving the swap.html file (Swap Page)
  server.on("/swap", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/html/swap.html", "text/html");
  });

  // Route for serving the about.html file (About Page)
  server.on("/about", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/html/about.html", "text/html");
  });

  // Route for serving the contact.html file (Contact Page)
  server.on("/contact", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/html/contact.html", "text/html");
  });

  // Route for serving the monitor.html file (Monitor Page)
  server.on("/monitor", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/html/monitor.html", "text/html");
  });

  // Route for serving the login.html file (Login Page)
  server.on("/login", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/html/login.html", "text/html");
  });

  // Route for serving the logout.html file (Logout Page)
  server.on("/logout", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/html/logout.html", "text/html");
  });

  // Serve CSS files
  server.on("/css/style.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/css/style.css", "text/css");
  });

  // Serve images
  server.on("/images/logo.png", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/images/logo.png", "image/png");
  });

  server.on("/images/battery_slot1.png", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/images/battery_slot1.png", "image/png");
  });

  server.on("/images/battery_slot2.png", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/images/battery_slot2.png", "image/png");
  });

  server.on("/images/homeswap1.png", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/images/homeswap1.png", "image/png");
  });

  server.on("/images/homerange2.png", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/images/homerange2.png", "image/png");
  });

  server.on("/images/hometime3.png", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/images/hometime3.png", "image/png");
  });

  server.on("/images/homemonitor4.png", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/images/homemonitor4.png", "image/png");
  });

  // Route for handling servo control requests
  server.on("/servo", HTTP_GET, handleServoControl);

  // Route to provide sensor data in JSON format
  server.on("/sensordata", HTTP_GET, fetchSensorData);

  // Start server
  server.begin();
}

void loop() {
  // Simulate sensor readings (replace with actual sensor readings)
  sensor1_current = random(4, 6);
  sensor2_current = random(4, 6);
  voltage = random(10, 12);

  // Add any other code that needs to run continuously

  delay(5000); // Update sensor readings every 5 seconds (adjust as needed)
}

// Function to handle servo control based on request parameters
void handleServoControl(AsyncWebServerRequest *request) {
  if (request->hasParam("slot") && request->hasParam("action")) {
    int slot = request->getParam("slot")->value().toInt();
    int action = request->getParam("action")->value().toInt();

    if (slot == 1) {
      if (action == 1) { // Unlock Slot 1
        servo1.write(0); // Set servo position for unlock
        request->send(200, "text/plain", "Slot 1 unlocked");
      } else if (action == 0) { // Lock Slot 1
        servo1.write(90); // Set servo position for lock
        request->send(200, "text/plain", "Slot 1 locked");
      } else {
        request->send(400, "text/plain", "Invalid action");
      }
    } else if (slot == 2) {
      if (action == 1) { // Unlock Slot 2
        servo2.write(0); // Set servo position for unlock
        request->send(200, "text/plain", "Slot 2 unlocked");
      } else if (action == 0) { // Lock Slot 2
        servo2.write(90); // Set servo position for lock
        request->send(200, "text/plain", "Slot 2 locked");
      } else {
        request->send(400, "text/plain", "Invalid action");
      }
    } else {
      request->send(400, "text/plain", "Invalid slot");
    }
  } else {
    request->send(400, "text/plain", "Missing parameters");
  }
}

// Function to fetch sensor data and send it in JSON format
void fetchSensorData(AsyncWebServerRequest *request) {
  // Create a JSON document
  StaticJsonDocument<200> jsonDoc;

  // Fill JSON object with sensor readings
  jsonDoc["sensor1_current"] = sensor1_current;
  jsonDoc["sensor2_current"] = sensor2_current;
  jsonDoc["voltage"] = voltage;

  // Serialize JSON to string
  String jsonString;
  serializeJson(jsonDoc, jsonString);

  // Send JSON response
  request->send(200, "application/json", jsonString);
}
