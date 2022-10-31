
#ifndef HttpDownstream_h
#define HttpDownstream_h

#include "Arduino.h"
#include <Base64.h> 
#include <ArduinoJson.h>
#include <string.h>
#include <Client.h>


class HttpDownstreamClient{


 private:

 String _token;
 char* _base64;
 //String _deviceID;

 //Base64 encoder
 void base64(char* username, char* password);
 
 
 public:

 Client* _networkClient;
 
 HttpDownstreamClient(Client& networkClient);

 //Delete the already existed subscription
 void subscriptionDelete(char* user, char* password,char* URL, char* context,char* source);
 
 //Create subscription
 void subscriptionCreate(char* user, char* password, char* URL, char* device_ID,char* context ,char* SubName, char* API,char* typeFilter, char* fragmentsToCopy);
 
 //Create token 
 void tokenCreate(char* URL, char* Subname, char* Suber, int expiretime);
 
 //Create token by giving password
 void tokenCreatePassword(char* user, char* password, char* URL, char* Subname, char* Suber, int expiretime);

 //Open WSS
 void connectWSS(char* URL,char* Suber);


};


#endif
