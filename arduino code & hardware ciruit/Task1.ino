#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <FirebaseESP8266HTTPClient.h>
#include <FirebaseFS.h>
#include <FirebaseJson.h>

// Configure Firebase Variables
#define WIFI_SSID "STUDBME2"
#define WIFI_PASSWORD "BME2Stud"
#define FIREBASE_HOST "ourtask-db996.firebaseio.com"
#define FIREBASE_AUTH "vFMa44z9V4NYE2QJxZVsgPyDag1gA1twT52PIuzt"

// Declare the Firebase Data object in the global scope
FirebaseData firebaseData;
  
void setup()
{
    // Debug console
    Serial.begin(115200);
  
    // connect to wifi.
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("connecting");
  
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }
    Serial.println();
    Serial.print("connected: ");
    Serial.println(WiFi.localIP());
    
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
        
    // Enable auto reconnect the WiFi when connection lost
    Firebase.reconnectWiFi(true);
}


void loop()

{
 
    double Vout, Rth, temp, adc_value; 

  adc_value = analogRead(12);
  Vout = ((adc_value)/1024)*5;
    Serial.println();
    
    if (Firebase.setFloat(firebaseData, "/Temperature_readings/Read data", Vout)) {
        // Success
        Serial.println("Set int data success");
        Serial.println(Vout);
    } else {
        // Failed?, get the error reason from firebaseDate
        Serial.print("Error in setInt, ");
        Serial.println(firebaseData.errorReason());
    }
  
    delay(200);
}
