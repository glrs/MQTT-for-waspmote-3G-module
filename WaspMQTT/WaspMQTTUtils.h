/*
 *
 * 
 *  WaspMQTTUtils.h
 *
 *  The WaspMQTTUtils is an auxiliary library for the users of
 *  WaspMQTTClient library. It provides some functions in order
 *  to help people write their own code easily and make it more
 *  readable.
 *
 *  Version:		1.0
 *
 *  Design:		Glaros Anastasios (glrs)
 *
 *  Implementation:	Glaros Anastasios (glrs)
 *
 */


#ifndef WaspMQTTUtils_h
#define WaspMQTTUtils_h

#include <Waspmote.h>
#include "WaspMQTTClient.h"

#define MQTT_MAX_PACKET_SIZE    250     // Maximum packet size

class MQTTUtils {
private:
  char json[MQTT_MAX_PACKET_SIZE/2];
  char topic[MQTT_MAX_PACKET_SIZE/2];
  
public:
  MQTTUtils();
  MQTTUtils(boolean);
  
  void startJsonObject(boolean);
  void addKeyValuePair(char *, char *);
  void addKeyValuePair(char *, int);
  void addKeyValuePair(char *, boolean);

  void endJsonObject(void);
  
  boolean sendMessage(WaspMQTTClient);
  
  void setDomainNodeSensor(const char PROGMEM *, const char PROGMEM *, const char PROGMEM *);
  
  void setTopic(char *);
  char* getMessage(void);
  char* getTopic(void);
  
  boolean sendKeyValuePair(WaspMQTTClient, char *, char *);
  boolean sendKeyValuePair(WaspMQTTClient, char *, int);
  boolean sendKeyValuePair(WaspMQTTClient, char *, boolean);
  
  boolean registerForCommands(WaspMQTTClient);
  boolean registerForCommands(char*, WaspMQTTClient);
};





/*class JSONArray {
private:
  
  void startJsonArray(boolean);
  void endJsonArray(void);
  
public:
  JSONArray();
};


class JSON {
private:
  

  //void startJsonObject(boolean);
  //void endJsonObject(void);
  
  //void startJsonArray(boolean);
  //void endJsonArray(void);
  
  
public:
  //JSONObject();
  JSON(boolean);
  
  void addKeyValuePair(char *, char *);
  void addKeyValuePair(char *, int);
  void addKeyValuePair(char *, boolean);

  char* getMessage(void);
};
*/

#endif

