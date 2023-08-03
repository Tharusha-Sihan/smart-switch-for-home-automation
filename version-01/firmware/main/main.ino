#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include "SPIFFS.h"


int threshold = 20;

unsigned long last_pressed = millis();
int button_delay = 200;
int relay_state[3] = {};
int relay[] = {5, 18, 19};
int button[] = {27, 33, 32};

void gotTouch1() {
  if ( millis() - last_pressed > button_delay) {
    last_pressed = millis();
    relay_state[0] = !relay_state[0];
    for (int i = 0; i < 3; i++) {
      Serial.print(touchRead(button[i]));
      Serial.print(" ");
    }
    for (int i = 0; i < 3; i++) {
      Serial.print(relay_state[i]);
      Serial.print(" ");
    }
  }
}

void gotTouch2() {
  if ( millis() - last_pressed > button_delay) {
    last_pressed = millis();
    relay_state[1] = !relay_state[1];
    for (int i = 0; i < 3; i++) {
      Serial.print(touchRead(button[i]));
      Serial.print(" ");
    }
    for (int i = 0; i < 3; i++) {
      Serial.print(relay_state[i]);
      Serial.print(" ");
    }
  }
}

void gotTouch3() {
  if ( millis() - last_pressed > button_delay) {
    last_pressed = millis();
    relay_state[2] = !relay_state[2];
    for (int i = 0; i < 3; i++) {
      Serial.print(touchRead(button[i]));
      Serial.print(" ");
    }
    Serial.print(" | ");
    for (int i = 0; i < 3; i++) {
      Serial.print(relay_state[i]);
      Serial.print(" ");
    }
    Serial.println("");
  }
}

void set_relay() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(relay[i], relay_state[i]);
  }
}

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Search for parameter in HTTP POST request
const char* PARAM_INPUT_1 = "ssid";
const char* PARAM_INPUT_2 = "pass";
const char* PARAM_INPUT_3 = "ip";
const char* PARAM_INPUT_4 = "gateway";
bool switch1state = true;


//Variables to save values from HTML form
String ssid;
String pass;
String ip;
String gateway;

// File paths to save input values permanently
const char* ssidPath = "/ssid.txt";
const char* passPath = "/pass.txt";
const char* ipPath = "/ip.txt";
const char* gatewayPath = "/gateway.txt";

IPAddress localIP;
//IPAddress localIP(192, 168, 1, 200); // hardcoded

// Set your Gateway IP address
IPAddress localGateway;
//IPAddress localGateway(192, 168, 1, 1); //hardcoded
IPAddress subnet(255, 255, 225, 240);

// Timer variables
unsigned long previousMillis = 0;
const long interval = 10000;  // interval to wait for Wi-Fi connection (milliseconds)

// Set LED GPIO
const int ledPin = 2;
// Stores LED state


// Initialize SPIFFS
void initSPIFFS() {
  if (!SPIFFS.begin(true)) {
    Serial.println("An error has occurred while mounting SPIFFS");
  }
  Serial.println("SPIFFS mounted successfully");
}

// Read File from SPIFFS
String readFile(fs::FS &fs, const char * path) {
  Serial.printf("Reading file: %s\r\n", path);

  File file = fs.open(path);
  if (!file || file.isDirectory()) {
    Serial.println("- failed to open file for reading");
    return String();
  }

  String fileContent;
  while (file.available()) {
    fileContent = file.readStringUntil('\n');
    break;
  }
  return fileContent;
}

// Write file to SPIFFS
void writeFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Writing file: %s\r\n", path);

  File file = fs.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("- failed to open file for writing");
    return;
  }
  if (file.print(message)) {
    Serial.println("- file written");
  } else {
    Serial.println("- write failed");
  }
}

// Initialize WiFi
bool initWiFi() {
  if (ssid == "" || ip == "") {
    Serial.println("Undefined SSID or IP address.");
    return false;
  }

  WiFi.mode(WIFI_STA);
  localIP.fromString(ip.c_str());
  localGateway.fromString(gateway.c_str());


  if (!WiFi.config(localIP, localGateway, subnet)) {
    Serial.println("STA Failed to configure");
    return false;
  }
  WiFi.begin(ssid.c_str(), pass.c_str());
  Serial.println("Connecting to WiFi...");

  unsigned long currentMillis = millis();
  previousMillis = currentMillis;

  while (WiFi.status() != WL_CONNECTED) {
    currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      Serial.println("Failed to connect.");
      return false;
    }
  }

  Serial.println(WiFi.localIP());
  return true;
}

void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(relay[i], OUTPUT);
  }
  // Serial port for debugging purposes
  Serial.begin(115200);
  touchAttachInterrupt(button[0], gotTouch1, threshold);
  touchAttachInterrupt(button[1], gotTouch2, threshold);
  touchAttachInterrupt(button[2], gotTouch3, threshold);

  initSPIFFS();

  // Set GPIO 2 as an OUTPUT
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // Load values saved in SPIFFS
  ssid = readFile(SPIFFS, ssidPath);
  pass = readFile(SPIFFS, passPath);
  ip = readFile(SPIFFS, ipPath);
  gateway = readFile (SPIFFS, gatewayPath);
  Serial.println(ssid);
  Serial.println(pass);
  Serial.println(ip);
  Serial.println(gateway);

  if (!(initWiFi())) {
    Serial.println("Setting AP (Access Point)");
    // NULL sets an open Access Point
    WiFi.mode(WIFI_AP_STA);
    WiFi.softAP("Smart-Hub", NULL);

    delay(2000);
    // Set static IP
    IPAddress AP_LOCAL_IP(192, 168, 1, 200);
    IPAddress AP_GATEWAY_IP(192, 168, 1, 4);
    IPAddress AP_NETWORK_MASK(255, 255, 255, 0);
    if (!WiFi.softAPConfig(AP_LOCAL_IP, AP_GATEWAY_IP, AP_NETWORK_MASK)) {
      Serial.println("AP Config Failed");
      return;
    }
    // Show the local IP
    Serial.print("AP IP address: ");
    IPAddress IP = WiFi.softAPIP();
    Serial.println(IP);
  }
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/wifimanager.html", "text/html");
  });

  server.serveStatic("/", SPIFFS, "/");

  // toggle switch 1
  server.on("/toggleswitch1", HTTP_GET, [](AsyncWebServerRequest * request) {

    relay_state[0] = !relay_state[0];

    request->send(200, "text/plain", String(relay_state[0]));
    //delay(3000);
  });

  // toggle switch 2
  server.on("/toggleswitch2", HTTP_GET, [](AsyncWebServerRequest * request) {

    relay_state[1] = !relay_state[1];

    request->send(200, "text/plain", String(relay_state[1]));
    //delay(3000);
  });

  // toggle switch 3
  server.on("/toggleswitch3", HTTP_GET, [](AsyncWebServerRequest * request) {

    relay_state[2] = !relay_state[2];

    request->send(200, "text/plain", String(relay_state[2]));
    //delay(3000);
  });

  // get switch 1 status
  server.on("/getSwitch1Status", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "text/plain", String(relay_state[0]));
    //delay(3000);
  });

  // get switch 2 status
  server.on("/getSwitch2Status", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "text/plain", String(relay_state[1]));
    //delay(3000);
  });

  // get switch 3 status
  server.on("/getSwitch3Status", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "text/plain", String(relay_state[2]));
    //delay(3000);
  });

  server.on("/", HTTP_POST, [](AsyncWebServerRequest * request) {
    int params = request->params();
    for (int i = 0; i < params; i++) {
      AsyncWebParameter* p = request->getParam(i);
      if (p->isPost()) {
        // HTTP POST ssid value
        if (p->name() == PARAM_INPUT_1) {
          ssid = p->value().c_str();
          Serial.print("SSID set to: ");
          Serial.println(ssid);
          // Write file to save value
          writeFile(SPIFFS, ssidPath, ssid.c_str());
        }
        // HTTP POST pass value
        if (p->name() == PARAM_INPUT_2) {
          pass = p->value().c_str();
          Serial.print("Password set to: ");
          Serial.println(pass);
          // Write file to save value
          writeFile(SPIFFS, passPath, pass.c_str());
        }
        // HTTP POST ip value
        if (p->name() == PARAM_INPUT_3) {
          ip = p->value().c_str();
          Serial.print("IP Address set to: ");
          Serial.println(ip);
          // Write file to save value
          writeFile(SPIFFS, ipPath, ip.c_str());
        }
        // HTTP POST gateway value
        if (p->name() == PARAM_INPUT_4) {
          gateway = p->value().c_str();
          Serial.print("Gateway set to: ");
          Serial.println(gateway);
          // Write file to save value
          writeFile(SPIFFS, gatewayPath, gateway.c_str());
        }
        //Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
      }
    }
    request->send(200, "text/plain", "Done. ESP will restart, connect to your router and go to IP address: " + ip);
    delay(3000);
    ESP.restart();
  });
  server.begin();
}

void loop() {

  set_relay();
  delay(100);
}
