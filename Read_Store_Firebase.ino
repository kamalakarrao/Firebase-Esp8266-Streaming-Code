
/**
   Created by Kamal

   Email: kamalakar.sambaraj@gmail.com

   Insta: @kamal_01_23

   Github: https://github.com/kamalakarrao

   Inspired from https://github.com/mobizt/Firebase-ESP8266


*/

#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

//---------------------1. YOU Need to Change the following info--------------------------------
#define WIFI_SSID "WIFI_AP"
#define WIFI_PASSWORD "WIFI_PASSWORD"
#define FIREBASE_HOST "PROJECT_ID.firebaseio.com"
#define FIREBASE_AUTH "DATABASE_SECRET"

//----------------------------------------------------------------------------------------------


//---------------------2. Define FirebaseESP8266 data object for data sending and receiving-------------------------

FirebaseData fbdo;

//----------------------------------------------------------------------------------------------


void setup()
{
   
//-------------------3.This Line is used to Enable to Display the process on Serial Monitor ---------------------------------------------------------------------------
//Serial.println("Test"); is used to print 'Test' on Serial Monitor
  Serial.begin(115200);
   
//----------------------------------------------------------------------------------------------

//-------------------4.This Block of Code connect Nodemcu to Wi-Fi---------------------------------------------------------------------------

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


//-------------------5.This Initializes Firebase Functionality---------------------------------------------------------------------------

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
   
//----------------------------------------------------------------------------------------------


//-------------------6. Enable auto reconnect the WiFi when connection lost---------------------------------------------------------------------------
   
  Firebase.reconnectWiFi(true);

//----------------------------------------------------------------------------------------------


  //------------------- 7. Try to set int data to Firebase------------------------
   
  //The set function returns bool for the status of operation
  //fbdo requires for sending the data
  if(Firebase.setInt(fbdo, "/LED_Status_set", 1))
  {
    //Success
     Serial.println("Set int data success");

  }else{
    //Failed?, get the error reason from fbdo

    Serial.print("Error in setInt, ");
    Serial.println(fbdo.errorReason());
  }

 //----------------------------------------------------------------------------------------------


  //------------------- 8. Try to get int data from Firebase------------------------

  //The get function returns bool for the status of operation
  //fbdo requires for receiving the data
  if(Firebase.getInt(fbdo, "/LED_Status_get"))
  {
    //Success
    Serial.print("Get int data success, int = ");
    Serial.println(fbdo.intData());

  }else{
    //Failed?, get the error reason from fbdo

    Serial.print("Error in getInt, ");
    Serial.println(fbdo.errorReason());
  }
   
//----------------------------------------------------------------------------------------------


}

void loop()
{
   //As of now , We're not running anything in loop.
}
