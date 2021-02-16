/**
   Created by Kamal

   Email: kamalakar.sambaraj@gmail.com

   Insta: @kamal_01_23

   Github: https://github.com/kamalakarrao

   Inspired from https://github.com/mobizt/Firebase-ESP8266


*/

#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

//---------------------1. YOU Need to Change the following info--------------------------------

// SSID & PASSWORD for Connecting to Wi-Fi
#define WIFI_SSID "YOUR WIFI SSID"
#define WIFI_PASSWORD "YOUR WIFI PASSWORD"

// Linking to your Firebase Project 
//Eg: PROJECT_ID.firebaseio.com [Please Don't include 'https' or '/']
#define FIREBASE_HOST "YOUR FIREBASE DATABASE URL"
#define FIREBASE_AUTH "YOUR FIREBASE DATABASE SECRET KEY"

//----------------------------------------------------------------------------------------------






//---------------------2.Firebase Will be actively listening to 'DEVICE_STREAM_PATH' and triggeres if any change is made under this path------------------------------

String DEVICE_ID = "device1";

String DEVICE_STREAM_PATH = "Devices/" + DEVICE_ID;

//----------------------------------------------------------------------------------------------





//---------------------3. Assigning LED_BUILTIN to switch1 variable and this variable will used in Firebase Stream Code--------------------------------

int switch1 = LED_BUILTIN;

//----------------------------------------------------------------------------------------------





//---------------------4.Define Firebase Data objects-----------------------------------------------------

//This Object is to Store Some data for initial start up
FirebaseData fbdo1;

//This Object is to stream that data and change LED when there is change in database.
FirebaseData fbdo2;

//----------------------------------------------------------------------------------------------





void setup()
{

//---------------------5.We have set pinMode as OUTPUT - This means we're saying Nodemcu that there is a output LED attached-----------------------------------------------------
 
  pinMode(switch1, OUTPUT);

//----------------------------------------------------------------------------------------------
   
   
   
   
   
  //-------------------6.This Line is used to Enable to Display the process on Serial Monitor ---------------------------------------------------------------------------

  Serial.begin(115200);
   
  //----------------------------------------------------------------------------------------------

   
   
//-------------------7.This Block of Code connect Nodemcu to Wi-Fi---------------------------------------------------------------------------

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

//----------------------------------------------------------------------------------------------
   
   

//-------------------8.This Initializes Firebase Functionality---------------------------------------------------------------------------

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
   
//----------------------------------------------------------------------------------------------

   
   
//-------------------9. Enable auto reconnect the WiFi when connection lost---------------------------------------------------------------------------

  Firebase.reconnectWiFi(true);
   
//----------------------------------------------------------------------------------------------


//-------------------10. In order to maintain simplicity, I would suggest to consider them as defaults---------------------------------------------------------------------------

  //Set the size of WiFi rx/tx buffers in the case where we want to work with large data.
  fbdo1.setBSSLBufferSize(1024, 1024);

  //Set the size of HTTP response buffers in the case where we want to work with large data.
  fbdo1.setResponseSize(1024);

  //Set the size of WiFi rx/tx buffers in the case where we want to work with large data.
  fbdo2.setBSSLBufferSize(1024, 1024);

  //Set the size of HTTP response buffers in the case where we want to work with large data.
  fbdo2.setResponseSize(1024);

//----------------------------------------------------------------------------------------------

   
//-------------------11. For the first time, The database is initially empty and you need to set some data in order to stream---------------------------------------------------------------------------

  // If data exists then we will set the data 
  if (Firebase.pathExist(fbdo1, DEVICE_STREAM_PATH)) {
    // This will simply put "off" in 'Devices/device1/switch1' where DEVICE_STREAM_PATH = "Devices/device1"
    // [Devices/device1/switch1]
    Firebase.setString(fbdo1, DEVICE_STREAM_PATH + "/switch1", "off");

  }
//----------------------------------------------------------------------------------------------

   
   
//-------------------12. This Block will Initiate the Stream---------------------------------------

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

//----------------------------------------------------------------------------------------------



void loop()
{
//Everything inside loop will run continously in repeated manner
   
  //-------------------13. This Block will Check if Stream is connected---------------------------------------
 
  if (!Firebase.readStream(fbdo2))
  {
    Serial.println("Can't read stream data");
    Serial.println("REASON: " + fbdo2.errorReason());
    Serial.println();
  }
//----------------------------------------------------------------------------------------------
   
   
   //-------------------14. This Block helps you to resume streaming in case of any interruption---------------------------------------

  if (fbdo2.streamTimeout())
  {
    Serial.println("Stream timeout, resume streaming...");
    Serial.println();
  }
//----------------------------------------------------------------------------------------------

   
    //-------------------15. This Block is trigerred when there is a change in database and we need to toggle the LED accordingly---------------------------------------

  if (fbdo2.streamAvailable())
  {
    Serial.println("------------------------------------");
    Serial.println("Stream Data Available...");
    Serial.println("STREAM PATH: " + fbdo2.streamPath());
    Serial.println("EVENT PATH: " + fbdo2.dataPath());
    Serial.println("DATA TYPE: " + fbdo2.dataType());
    Serial.println("EVENT TYPE: " + fbdo2.eventType());
    Serial.print("VALUE: ");

    //if switch1 exists in Event Path then toggle the LED  
     // fbdo2.dataPath().indexOf("switch1") gives you -1 if switch1 doesn't exist
    if (fbdo2.dataPath().indexOf("switch1") != -1) {
       // if value of switch is 'on' then turn on the LED
      if (fbdo2.stringData() == "on") {
         
        digitalWrite(switch1, LOW);
         // if value of switch is 'off' then turn off the LED
      } else if (fbdo2.stringData() == "off") {
         
        digitalWrite(switch1, HIGH);
      }

    }
  }

//----------------------------------------------------------------------------------------------

}

