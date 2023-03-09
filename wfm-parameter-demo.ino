/*
  WiFiManager Extra Parameters Demo
  wfm-parameter-demo.ino
  Demonstrates adding extra parameters to WiFiManager menu

  DroneBot Workshop 2022
  https://dronebotworkshop.com
*/

// Include WiFiManager Library
#include <WiFiManager.h>

void setup() {

  // Setup Serial Monitor
  Serial.begin(115200);

  // Create WiFiManager object
  WiFiManager wfm;

  // Supress Debug information
  wfm.setDebugOutput(false);

  // Remove any previous network settings
  wfm.resetSettings();

  // Define a text box, 50 characters maximum
  WiFiManagerParameter custom_text_box("my_text", "Enter your string here", "default string", 50);

  // Add custom parameter
  wfm.addParameter(&custom_text_box);

  if (!wfm.autoConnect("ESP32TEST_AP", "password")) {
    // Did not connect, print error message
    Serial.println("failed to connect and hit timeout");

    // Reset and try again
    ESP.restart();
    delay(1000);
  }

  // Connected!
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  

  // Print custom text box value to serial monitor
  Serial.print("Custom text box entry: ");
  Serial.println(custom_text_box.getValue());
}

void loop() {

  // Loop code

}
