#include "HttpDownstream.h"


HttpDownstreamClient::HttpDownstreamClient(Client& networkClient) {

  _networkClient = &networkClient;

}


//Base64 encoder
void HttpDownstreamClient::base64(char* username, char* password) {
  char temp[100];

  strcpy(temp , username);
  strcat(temp, ":");
  strcat(temp, password);
  Serial.println();
  //For debugging
  Serial.print("Information needs to be coded is:");
  Serial.println(temp);

  int inputStringLength = strlen(temp);
  int encodedLength = Base64.encodedLength(inputStringLength);
  char encodedString[encodedLength];
  Base64.encode(encodedString, temp, inputStringLength);
  //Serial.print("Encoded string is: ");
  //Serial.println(encodedString);
  //Memory allocation
  if (_base64) free (_base64);
  _base64 = (char*) malloc(sizeof(char) * strlen(encodedString));
  strcpy(_base64, encodedString);

  Serial.print("Stored Based64 string is: ");
  Serial.println(_base64);
}



void HttpDownstreamClient::subscriptionDelete(char* user, char* password,char* URL,char* context,char* source){
  
  base64(user, password);
  //Serial.println(_base64);

  if (_networkClient->connect(URL, 443)){
    Serial.println("Start to clear the subscription");
    // Make a HTTP request:
    _networkClient->print("DELETE /notification2/subscriptions?context=");
    _networkClient->print(context);
    _networkClient->print("&");
    _networkClient->print("source=");
    _networkClient->print(source);
    _networkClient->println(" HTTP/1.1");
    _networkClient->print("Host: ");
    _networkClient->println(URL);
    _networkClient->println("Accept: application/vnd.com.nsn.cumulocity.error+json");
    _networkClient->print("Authorization: Basic ");
    _networkClient->println(_base64);
    
    }
  
  }

void HttpDownstreamClient::subscriptionCreate(char* user, char* password, char* URL, char* device_ID, char* context , char* SubName, char* API, char* type_Filter, char* fragments_To_Copy) {

  //Serial.print("The subscription is associated with the device: ");
  //Serial.println(device_ID);

  base64(user, password);
  Serial.println(_base64);

  StaticJsonDocument<400> root;
  root["context"] = context;
  
  if(context == "mo"){
    if(device_ID != NULL){
  
  JsonObject source  = root.createNestedObject("source");
  source["id"] = device_ID;
  
      }else{
        Serial.println("Please enter the device ID");
        }
    }
  //JsonObject source  = root.createNestedObject("source");
  //source["id"] = device_ID;

  root["subscription"] = SubName;
  
  JsonObject subFilter = root.createNestedObject("subscriptionFilter");
  if (*type_Filter != NULL) {
    subFilter["typeFilter"] = type_Filter;
  } else {}

  JsonArray apis = subFilter.createNestedArray("apis");
  apis.add(API);

  if (*fragments_To_Copy != NULL) {
    JsonArray fragtocopy = root.createNestedArray("fragmentsToCopy");
    fragtocopy.add(fragments_To_Copy);
  } else {}


  String body2send = "";
  serializeJsonPretty(root, body2send);
  Serial.println(body2send);

  if (_networkClient->connect(URL, 443)) {
    Serial.println("Connected to the server");
    // Make a HTTP request:
    _networkClient->println("POST /notification2/subscriptions HTTP/1.1");
    _networkClient->print("Host: ");
    _networkClient->println(URL);
    _networkClient->println("Content-Type: application/json");
    _networkClient->print("Content-Length: ");
    _networkClient->println(body2send.length());
    _networkClient->println("Accept: application/json");
    _networkClient->print("Authorization: Basic ");
    _networkClient->print(_base64);
    _networkClient->println();
    _networkClient->println();
    _networkClient->println(body2send);

  } else {
    Serial.println("Connection fail!");
  }
}


void HttpDownstreamClient::tokenCreate(char* URL, char* Subname, char* Suber, int expiretime) {

  Serial.print("The subscription is associated with the Subscripter: ");
  Serial.println(Suber);

  StaticJsonDocument<150> root;

  root["subscriber"] = Suber;
  root["subscription"] = Subname;
  root["expiresInMinutes"] = expiretime;
  String body2send = "";

  serializeJsonPretty(root, body2send);
  //Serial.println(body2send);
  Serial.println("Start to connect to the server!");
  if (_networkClient->connect(URL, 443)) {
    Serial.println("Connected to the server");
    // Make a HTTP request:
    _networkClient->println("POST /notification2/token HTTP/1.1");
    _networkClient->print("Host: ");
    _networkClient->println(URL);
    _networkClient->print("Authorization: Basic ");
    _networkClient->println(_base64);
    _networkClient->println("Content-Type: application/json");
    _networkClient->print("Content-Length: ");
    _networkClient->println(body2send.length());
    _networkClient->println("Accept: application/json");
    _networkClient->println();
    _networkClient->println(body2send);

  }

while (_token.length() == 0) {
    String msg = "";
    while (_networkClient->available()) {
      char c = _networkClient->read();
      msg += c;
    }
    Serial.println(msg);
    int start_init = msg.indexOf("\"token\"");
    int start = msg.indexOf(":",start_init);
    int until_n = msg.indexOf("\"", start + 3);
    Serial.println(until_n);
    if (start != -1 && until_n != -1 ) {
      _token = msg.substring(start + 2, until_n);
      Serial.print("Token is: ");
      Serial.println(_token);
     }
  }
 
}


void HttpDownstreamClient::tokenCreatePassword(char* user, char* password, char* URL, char* Subname, char* Suber, int expiretime) {
  base64(user, password);
  Serial.println(_base64);

  Serial.print("The subscription is associated with the Subscripter: ");
  Serial.println(Suber);

  StaticJsonDocument<150> root;

  root["subscriber"] = Suber;
  root["subscription"] = Subname;
  root["expiresInMinutes"] = expiretime;
  String body2send = "";

  serializeJsonPretty(root, body2send);
  //Serial.println(body2send);

  if (_networkClient->connect(URL, 443)) {
    Serial.println("Connected to the server");
    // Make a HTTP request:
    _networkClient->println("POST /notification2/token HTTP/1.1");
    _networkClient->print("Host: ");
    _networkClient->println(URL);
    _networkClient->print("Authorization: Basic ");
    _networkClient->println(_base64);
    _networkClient->println("Content-Type: application/json");
    _networkClient->print("Content-Length: ");
    _networkClient->println(body2send.length());
    _networkClient->println("Accept: application/json");
    _networkClient->println();
    _networkClient->println(body2send);

  }

  while (_token.length() == 0) {
    String msg = "";
    while (_networkClient->available()) {
      char c = _networkClient->read();
      msg += c;
    }
    Serial.println(msg);
    int start_init = msg.indexOf("\"token\"");
    int start = msg.indexOf(":",start_init);
    int until_n = msg.indexOf("\"", start + 3);
    Serial.println(until_n);
    if (start != -1 && until_n != -1 ) {
      _token = msg.substring(start + 2, until_n);
      Serial.print("Token is: ");
      Serial.println(_token);
     }
  }


}



void HttpDownstreamClient::connectWSS(char* URL, char* Suber) {
  if (_token.length() != 0) {
    if (_networkClient->connect(URL, 443)) {
      Serial.println("Websocket port is opened");
      // Make a HTTP request:
      _networkClient->print("GET ");
      _networkClient->print("/notification2/consumer/?token=");
      _networkClient->print(_token);
      _networkClient->print("&consumer=");
      _networkClient->print(Suber);
      _networkClient->println(" HTTP/1.1");

      _networkClient->print("Host: ");
      _networkClient->println(URL);
      _networkClient->println("Sec-WebSocket-Key: q4xkcO32u266gldTkKaSOw==");
      _networkClient->println("Upgrade: websocket");
      _networkClient->println("Connection: Upgrade");
      _networkClient->println("Sec-WebSocket-Version: 13");
      _networkClient->println();
    }
  }
}
