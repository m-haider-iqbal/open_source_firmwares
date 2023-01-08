#include <WiFi.h>

const char* ssid = "your-ssid";
const char* password = "your-password";

int relayPin = 4; // GPIO pin where the relay is connected

WiFiServer server(80);

void setup() {
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); // set relay to off state

  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  client.flush();

  // Match the request
  if (request.indexOf("/on") != -1)  {
    digitalWrite(relayPin, HIGH);
  }
  if (request.indexOf("/off") != -1) {
    digitalWrite(relayPin, LOW);
  }

  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<body style='text-align: center;'>");
  client.println("<h1 style='color: #444;'>ESP32 Web Server</h1>");
  client.println("<h2>Relay is now: " + (digitalRead(relayPin) ? "ON" : "OFF") + "</h2>");
  client.println("<br><br>");
  client.println("<a href='/on' style='color: #fff; background-color: #444; padding: 15px 30px; text-decoration: none;'>ON</a>");
  client.println("<a href='/off' style='color: #fff; background-color: #444; padding: 15px 30px; text-decoration: none;'>OFF</a>");
  client.println("</body>");
  client.println("</html>");

  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
}
