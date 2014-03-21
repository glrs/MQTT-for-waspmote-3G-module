/*
 *
 * 
 *  WaspMQTTUtils.cpp
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



#include "WaspMQTTUtils.h"


MQTTUtils::MQTTUtils(boolean flag){
  memset(&json[0], 0, sizeof(json));
  startJsonObject(flag);
}

MQTTUtils::MQTTUtils(){
  memset(&json[0], 0, sizeof(json));
  startJsonObject(true);
}

/*JSONArray::JSONArray(){
  startJsonArray(true);
}

JSON::JSON(boolean flag){
    startJsonObject(flag);
}*/
/*void JSONArray::startJsonArray(boolean newArray) {
  if(newArray) {
    if(strlen(json) > 1) {
      memset(&json[0], 0, sizeof(json));
    }
  }
  sprintf(json, "%s%s", json, "[");
}

void JSONArray::endJsonArray(void) {
  sprintf(json, "%s%s%c", json, "]", '\0');
  USB.println(json);
}*/


void MQTTUtils::startJsonObject(boolean newObject) {
  if(newObject) {
    if(strlen(json) > 0) {
      memset(&json[0], 0, sizeof(json));
    }
  }
  sprintf(json, "%s%s", json, "{");
}

void MQTTUtils::endJsonObject(void) {
  sprintf(json, "%s%s%c", json, "}", '\0');
  //USB.println(json);
}

char* MQTTUtils::getMessage(void) {
  return json;
}


void MQTTUtils::addKeyValuePair(char* key, char *value) {
  if(strlen(json) > 1) {
    sprintf(json, "%s%s", json, ",");
  }
  sprintf(json, "%s%s", json, "\"");
  sprintf(json, "%s%s", json, key);
  sprintf(json, "%s%s", json, "\":\"");
  sprintf(json, "%s%s", json, value);
  sprintf(json, "%s%s", json, "\"");

  //USB.println(json);
}

void MQTTUtils::addKeyValuePair(char* key, int value) {
  if(strlen(json) > 1) {
    sprintf(json, "%s%s", json, ",");
  }
  sprintf(json, "%s%s", json, "\"");
  sprintf(json, "%s%s", json, key);
  sprintf(json, "%s%s", json, "\":");
  sprintf(json, "%s%d", json, value);
  
  //USB.println(json);
}

void MQTTUtils::addKeyValuePair(char* key, boolean value) {
  if(strlen(json) > 1) {
    sprintf(json, "%s%s", json, ",");
  }
  sprintf(json, "%s%s", json, "\"");
  sprintf(json, "%s%s", json, key);
  sprintf(json, "%s%s", json, "\":");
  if(value) {
    sprintf(json, "%s%s", json, "true");
  }
  else {
    sprintf(json, "%s%s", json, "false");
  }
  
  //USB.println(json);
}


boolean MQTTUtils::sendMessage(WaspMQTTClient client){
  return client.publish(getTopic(), (uint8_t*)getMessage(), strlen(getMessage()), false);
}


void MQTTUtils::setDomainNodeSensor(const char PROGMEM *domain, const char PROGMEM *node, const char PROGMEM *sensor) {
  memset(&topic[0], 0, sizeof(topic));

  //USB.println(F("- setDomainStuffThing: Enter"));

  sprintf(topic, "%s%s", topic, domain);
  sprintf(topic, "%s%s", topic, "/");
  
  sprintf(topic, "%s%s", topic, node);
  sprintf(topic, "%s%s", topic, "/");
  
  sprintf(topic, "%s%s", topic, sensor);
  
  //USB.print(F("Topic= "));
  //USB.println(topic);
}

void MQTTUtils::setTopic(char* newTopic){
  memset(&topic[0], 0, sizeof(topic));
  sprintf(topic, "%s%s%c", topic, newTopic, '\0');
}

char* MQTTUtils::getTopic(){
  return topic;
}

boolean MQTTUtils::sendKeyValuePair(WaspMQTTClient client, char *key, char *value) {
  char message[MQTT_MAX_MESSAGE_SIZE];
  memset(&message[0], 0, sizeof(message));
  
  sprintf(message, "%s%s", message, "{\"");
  sprintf(message, "%s%s", message, key);
  sprintf(message, "%s%s", message, "\":\"");
  sprintf(message, "%s%s", message, value);
  sprintf(message, "%s%s%c", message, "\"}", '\0');
  
  if(topic != NULL) {
    return client.publish(getTopic(), (uint8_t*)message, strlen(message), false);  // check if false passes.. if not: boolean val = false and pass val
  }
  else {
    USB.println(F("> There is no specified Topic.\n> Please set a Topic first. "));
    return false;
  }
}

boolean MQTTUtils::sendKeyValuePair(WaspMQTTClient client, char *key, int value) {
  char message[MQTT_MAX_MESSAGE_SIZE];
  memset(&message[0], 0, sizeof(message));
  
  sprintf(message, "%s%s", message, "{\"");
  sprintf(message, "%s%s", message, key);
  sprintf(message, "%s%s", message, "\":");
  sprintf(message, "%s%d", message, value);
  sprintf(message, "%s%s%c", message, "}", '\0');
  
  if(topic != NULL) {
    return client.publish(getTopic(), (uint8_t*)message, strlen(message), false);  // check if false passes.. if not: boolean val = false and pass val
  }
  else {
    USB.println(F("> There is no specified Topic.\n> Please set a Topic first. "));
    return false;
  }
}

boolean MQTTUtils::sendKeyValuePair(WaspMQTTClient client, char *key, boolean value) {
  char message[MQTT_MAX_MESSAGE_SIZE];
  memset(&message[0], 0, sizeof(message));

  sprintf(message, "%s%s", message, "{\"");
  sprintf(message, "%s%s", message, key);
  sprintf(message, "%s%s", message, "\":");
  if(value) {
    sprintf(message, "%s%s", message, "true");
  }
  else {
    sprintf(message, "%s%s", message, "false");
  }
  sprintf(message, "%s%s%c", message, "}", '\0');

  if(topic != NULL) {
    return client.publish(getTopic(), (uint8_t*)message, strlen(message), false);  // check if false passes.. if not: boolean val = false and pass val
  }
  else {
    USB.println(F("> There is no specified Topic.\n> Please set a Topic first. "));
    return false;
  }
}


boolean MQTTUtils::registerForCommands(WaspMQTTClient client) {
  char cmdTopic[MQTT_MAX_TOPIC_SIZE];
  memset(&cmdTopic[0], 0, sizeof(cmdTopic));
  
  //USB.println(F("- registerForCommands: Enter."));
  
  sprintf(cmdTopic, "%s%s", cmdTopic, getTopic());
  sprintf(cmdTopic, "%s%s", cmdTopic, "/cmd");
  
  USB.print(F("cmdTopic= "));
  USB.println(cmdTopic);
  boolean answer;
  answer = client.subscribe(cmdTopic);
  
  if(answer == true) {
    USB.println(F("- registerForCommands: subscribe: True!"));
    return true;
    //int len = readPacket();
    //USB.println(len, DEC);
  }
  else {
    USB.println(F("- registerForCommands: subscribe: False."));
    return false;
  }
}


boolean MQTTUtils::registerForCommands(char* newTopic, WaspMQTTClient client) {
  char cmdTopic[MQTT_MAX_TOPIC_SIZE];
  memset(&cmdTopic[0], 0, sizeof(cmdTopic));
  
  //USB.println(F("- registerForCommands: Enter."));
  
  sprintf(cmdTopic, "%s%s", cmdTopic, newTopic);
  sprintf(cmdTopic, "%s%s", cmdTopic, "/cmd");
  
  USB.print(F("cmdTopic= "));
  USB.println(cmdTopic);
  boolean answer;
  answer = client.subscribe(cmdTopic);
  
  if(answer == true) {
    USB.println(F("- registerForCommands: subscribe: True!"));
    return true;
  }
  else {
    USB.println(F("- registerForCommands: subscribe: False."));
    return false;
  }
}



