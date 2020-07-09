#include <Arduino.h>
#include <Servo.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include <config.h>

ESP8266WebServer server(80);

Servo servo1;

void handleRoot()
{
  String message = "Hello, I'm fish feeder - possible messages /feed";
  server.send(200, "text/html", message);
}

void handleState()
{

  String message = "OK";
  server.send(200, "text/html", message);
}

void handleNotFound()
{
  handleRoot();
}

void handleFeed()
{

  String message = "OK\n\n";
  server.send(200, "text/plain", message);

  servo1.attach(15);
  servo1.write(50);
  delay(1000);
  servo1.write(135);
  delay(1000);
  servo1.write(50);
  delay(1000);
  servo1.detach();
}

void handleShake()
{

  String message = "OK\n\n";
  server.send(200, "text/plain", message);

  servo1.attach(15);
  for (int i = 0; i < 10; i++)
  {
    servo1.write(50);
    delay(100);
    servo1.write(100);
    delay(100);
  }
  delay(100);
  servo1.write(50);
  delay(1000);
  servo1.detach();
}

void setup()
{
  WiFi.begin(ssid, password);
  WiFi.softAPdisconnect(true);

  server.on("/", handleRoot);
  server.on("/state", handleState);
  server.on("/feed", handleFeed);
  server.on("/shake", handleShake);

  server.onNotFound(handleNotFound);
  server.begin();

  servo1.attach(15);
  servo1.write(50);
  delay(1000);
  servo1.detach();
}

int pos = 0;

void loop()
{
  server.handleClient();
}