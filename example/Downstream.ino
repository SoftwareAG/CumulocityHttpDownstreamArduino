
#include "HttpDownstream.h"
#include "arduino_secrets.h" //optional file for wifi SSID and password
#include <WiFiNINA.h>

WiFiSSLClient nwc; //initiate the WiFiSSL client
HttpDownstreamClient c8yclient(nwc); //initiate the HttpDownstreamClient 

int status = WL_IDLE_STATUS;


char* host = "yourtenant.cumulocity.com";
char* username = "username";
char* password = "password";
char* device_id = "deviceid";

//Subscription Test
char* SubscriptionName = "NotificationV2Test";
char* SubscriberName = "Test2Sub1";
char* APIs = "measurements";
char* typeFilter= "";
char* fragmentsToCopy= "";
int expiretime = 1100;


char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }
  
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 5 seconds for connection:
    delay(5000);
  }

  Serial.println("Connected to WiFi");
  
  c8yclient.subscriptionCreate(username,password,host, device_id,"mo" ,SubscriptionName, APIs,typeFilter,fragmentsToCopy);
  delay(4000);
  c8yclient.tokenCreate(host, SubscriptionName, SubscriberName, expiretime);
  c8yclient.connectWSS(host,SubscriberName);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  while (nwc.available()) {
    char c = nwc.read();
    Serial.print(c);
  }

}
