/**
   Created by Kamal

   Email: kamalakar.sambaraj@gmail.com

   Insta: @kamal_01_23

   Github: https://github.com/kamalakarrao

   Inspired from https://github.com/mobizt/Firebase-ESP8266


*/

#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

#define WIFI_SSID "YOUR WIFI SSID"
#define WIFI_PASSWORD "YOUR WIFI PASSWORD"

#define FIREBASE_HOST "YOUR FIREBASE DATABASE URL"
#define FIREBASE_AUTH "YOUR FIREBASE DATABASE SECRET KEY"


String DEVICE_ID = "device1";

String DEVICE_STREAM_PATH = "Devices/" + DEVICE_ID;

int switch1 = 13;


//Define Firebase Data objects
FirebaseData fbdo1;
FirebaseData fbdo2;

void setup()
{

  pinMode(switch1, OUTPUT);

  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();


  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  //Set the size of WiFi rx/tx buffers in the case where we want to work with large data.
  fbdo1.setBSSLBufferSize(1024, 1024);

  //Set the size of HTTP response buffers in the case where we want to work with large data.
  fbdo1.setResponseSize(1024);

  //Set the size of WiFi rx/tx buffers in the case where we want to work with large data.
  fbdo2.setBSSLBufferSize(1024, 1024);

  //Set the size of HTTP response buffers in the case where we want to work with large data.
  fbdo2.setResponseSize(1024);


  if (Firebase.pathExist(fbdo1, DEVICE_STREAM_PATH)) {

    Firebase.setString(fbdo1, DEVICE_STREAM_PATH + "/switch1", "off");

  }


  Serial.println("Begin stream 1...");
  if (!Firebase.beginStream(fbdo2, DEVICE_STREAM_PATH ))
  {
    Serial.println("FAILED");
    Serial.println("REASON: " + fbdo2.errorReason());
    Serial.println();
  }
  else
  {
    Serial.println("PASSED");
    Serial.println("------------------------------------");
    Serial.println();
  }
}

void loop()
{

  if (!Firebase.readStream(fbdo2))
  {
    Serial.println("Can't read stream data");
    Serial.println("REASON: " + fbdo2.errorReason());
    Serial.println();
  }

  if (fbdo2.streamTimeout())
  {
    Serial.println("Stream timeout, resume streaming...");
    Serial.println();
  }

  if (fbdo2.streamAvailable())
  {
    Serial.println("------------------------------------");
    Serial.println("Stream Data Available...");
    Serial.println("STREAM PATH: " + fbdo2.streamPath());
    Serial.println("EVENT PATH: " + fbdo2.dataPath());
    Serial.println("DATA TYPE: " + fbdo2.dataType());
    Serial.println("EVENT TYPE: " + fbdo2.eventType());
    Serial.print("VALUE: ");


    if (fbdo2.dataPath().indexOf("switch1") != -1) {
      if (fbdo2.stringData() == "on") {
        digitalWrite(switch1, LOW);
      } else if (fbdo2.stringData() == "off") {
        digitalWrite(switch1, HIGH);
      }

    }
  }



}

