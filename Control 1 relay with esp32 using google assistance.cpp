/*
This code will connect the ESP32 to a WiFi network with the specified SSID and password. 
It will then set up the Google Assistant library and define a callback function 
that is called whenever a command is recognized by the assistant. In this case, 
the callback function checks if the command is to turn on or turn off the relay, 
and if it is, it will set the relay to the appropriate state.

You will need to install the WiFi.h and GoogleAssistant.h libraries in the 
Arduino IDE, and replace "YOUR_PROJECT_ID" and "YOUR_MODEL_ID" with the actual 
Project ID and Model ID for your Google Assistant project. You will also need to 
replace "YOUR_SSID" and "YOUR_PASSWORD" with the SSID and password for your WiFi network.
*/


#include <WiFi.h>
#include <GoogleAssistant.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// Replace with your own Project ID and Model ID
const char* projectId = "YOUR_PROJECT_ID";
const char* modelId = "YOUR_MODEL_ID";

#define RELAY_PIN 32

GoogleAssistant assistant(projectId, modelId, [] (const char* command) {
  // Check if the command is to turn on the relay
  if (strstr(command, "turn on the relay")) {
    digitalWrite(RELAY_PIN, HIGH);
    return "Turned on the relay";
  }
  // Check if the command is to turn off the relay
  if (strstr(command, "turn off the relay")) {
    digitalWrite(RELAY_PIN, LOW);
    return "Turned off the relay";
  }
  // If the command is not recognized, return a default response
  return "Sorry, I didn't get that. Could you please repeat it?";
});

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  assistant.begin();
}

void loop() {
  assistant.loop();
}
