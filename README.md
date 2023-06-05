# ur-ArduinoMicrocontroller-library

A library created by Yingzhe and Luis from University Relation, Software AG

This library enables you to obtain the real-time data, alarm and events from the Cumulocity IoT platform to your edge device.

The library is only used and tested for MKR WIFI 1010!! If you are the user from ESP32 and ESP86, then you have to modify the code. Sorry for that! 

**Prerequisite**
### Library to be included

1. WiFi liraries, e.g., WiFiNINA, WiFi101.

# API

## Subscription Delete

```
void subscriptionDelete(char* user, char* password,char* URL, char* context,char* source);
```
- `char* user` user name for your tenant logging  
- `char* URL` The URL where your tenant is. The format should be: *MyTenant.cumulocity.com*
- `char* password` The password of your tenant
- `char* context` The context within which the subscription should cover. It can be either "mo" or "tenant". 
- `char* source` ID device of the source when the context is "mo". 

## Subscription Creation
```
 void subscriptionCreate(char* user, char* password, char* URL, char* device_ID,char* context ,char* SubName, char* API,char* typeFilter, char* fragmentsToCopy);
```
- `char* user` user name for your tenant logging  
- `char* password` The password of your tenant
- `char* URL` The URL where your tenant is. The format should be: *MyTenant.cumulocity.com*
- `char* device_ID` ID device of the source when the context is "mo". 
- `char* context` The context within which the subscription should cover. It can be either "mo" or "tenant". 
- `char* Subname` The name of the subscription
- `char* API` The apis you want to subscribe to. It could be "alarms", "events", "managedobjects", "measurements", "operations" or "*" which means wildcard.
- `char* typeFilter` The data needs to have the specified value in its type property to meet the filter criteria.
- `char* fragmentsToCopy` Transforms the data to only include specified custom fragments. Each custom fragment is identified by a unique name. If nothing is specified here, the data is forwarded as-is.

## Token Creation
```
 void tokenCreate(char* URL, char* Subname, char* Suber, int expiretime);
```
- `char* URL` The URL where your tenant is. The format should be: *MyTenant.cumulocity.com*
- `char* Subname` The name of the subscription
- `char* Suber` The subscriber which subscribes to the subscription
- `int expiretime` The time for expiration in minutes.


## Token Creation with password
```
void tokenCreatePassword(char* user, char* password, char* URL, char* Subname, char* Suber, int expiretime);
```
- `char* user` user name for your tenant logging 
- `char* password` The password of your tenant
- `char* URL` The URL where your tenant is. The format should be: *MyTenant.cumulocity.com*
- `char* Subname` The name of the subscription
- `char* Suber` The subscriber which subscribes to the subscription
- `int expiretime` The time for expiration in minutes.


## Connect WSS via Websocket
```
void connectWSS(char* URL,char* Suber);
```
- `char* URL` The URL where your tenant is. The format should be: *MyTenant.cumulocity.com*
- `char* Suber` The subscriber which subscribes to the subscription


----
These tools are provided as-is and without warranty or support. They do not constitute part of the Software AG product suite. Users are free to use, fork and modify them, subject to the license agreement. While Software AG welcomes contributions, we cannot guarantee to include every contribution in the master project.
