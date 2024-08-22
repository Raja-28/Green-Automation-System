#include <ESP8266WiFi.h>
#include <DHT.h>

// Replace with your network credentials
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// Replace with your server URL
const char* serverName = "http://yourserver.com/update";

// Sensor pins
const int soilMoisturePin = A0;
const int ldrPin = A1;
#define DHTPIN 2
#define DHTTYPE DHT22

// Initialize sensors
DHT dht(DHTPIN, DHTTYPE);

WiFiClient client;

void setup() {
  Serial.begin(9600);
  dht.begin();
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  // Read soil moisture
  int soilMoistureValue = analogRead(soilMoisturePin);
  
  // Read light level
  int lightLevel = analogRead(ldrPin);
  
  // Read temperature and humidity
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  
  // Check if readings are valid
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Send data to server
  if (client.connect(serverName, 80)) {
    String postData = "soilMoisture=" + String(soilMoistureValue) +
                      "&temperature=" + String(temperature) +
                      "&humidity=" + String(humidity) +
                      "&lightLevel=" + String(lightLevel);
    
    client.println("POST /update HTTP/1.1");
    client.println("Host: yourserver.com");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Content-Length: " + String(postData.length()));
    client.println();
    client.println(postData);
    client.stop();
  } else {
    Serial.println("Connection to server failed");
  }

  delay(60000); // Wait for 1 minute before sending the next update
}
