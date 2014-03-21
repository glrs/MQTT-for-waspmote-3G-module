#include <Wasp3G.h>
#include <WaspFrame.h>
#include "WaspMQTTClient.h"
#include "WaspMQTTUtils.h"


char MQTT_USERNAME[] = "";
char MQTT_PASSWORD[] = "";
char MQTT_DEVICE_ID[] = "Node_A";  // Used as client_id, if we suppose that one device represents one client.
char MQTT_TOPIC[] = "a/b/c";
char MQTT_HOST[] = "localhost";
long MQTT_PORT = 1883;

int8_t answer;

MQTTUtils j;
WaspMQTTClient c;
Wasp3GMQTTClient client;

void cmdCallBack(char *topic, uint8_t* message, unsigned int len);

void setup() {
  boolean ans = false;

  USB.ON();
  USB.println(F("> USB port started."));
  
  client = Wasp3GMQTTClient();

  c = WaspMQTTClient(MQTT_HOST, MQTT_PORT, cmdCallBack, client);
  
  answer = 0;
  
  while(answer != 1) {
    answer = c.connect(MQTT_DEVICE_ID, MQTT_USERNAME, MQTT_PASSWORD);
    if(answer != 1)
    {
      USB.println(F("Unable to connect to network."));
    }
  }
  
  // Subscribe to the topic
  while(!ans) {
    ans = c.subscribe(MQTT_TOPIC);
    if(ans) {
      USB.print(F("Successfully subscribed in topic \""));
      USB.print(MQTT_TOPIC);
      USB.println(F("\"."));
    }
    else {
      USB.println(F("Can't subscribe."));
	}
  }
}


void loop() {
  
  delay(200);
  if(!c.loop()) {
    // Handle needed here.
	
    USB.print(F("MQTT loop failure."));
  }
}


void cmdCallBack(char *inTopic, uint8_t *message, unsigned int len) {
  boolean lightOn;
  boolean lightOff;
  
  //USB.println(F("Command Recieved"));
  
  j.setTopic("a/b/lights");
  
  USB.print(inTopic);
  
  USB.print(F(" "));
  for(int i = 0; i < len; i++) {
    USB.print((byte)message[i]);
  }
  USB.println();

  if (c.commandCompare("light on", message, len)) {
    Utils.setLED(LED0, LED_ON);
	lightOn = true;

	// Create JSON response to publish
    j.startJsonObject(true);
    j.addKeyValuePair("light on", lightOn);
    j.endJsonObject();
	
    if(c.publish(j.getTopic(), j.getMessage())) {
      USB.println(F("Response Sent."));
    }
    else {
      USB.println(F("Response does not sent."));
    }

  } else if (c.commandCompare("light off", message, len)) {    
    Utils.setLED(LED0, LED_OFF);
	lightOff = true;
    
	// Use this function instead to send a quick JSON response
	if(j.sendKeyValuePair(c, "light off", lightOff);) {
      USB.println(F("Response Sent."));
    }
    else {
      USB.println(F("Response does not Sent."));
    }
	
    //j.startJsonObject(true);
    //j.addKeyValuePair("light off", lightOff);
    //j.endJsonObject();
/*
    if(c.publish(j.getTopic(), j.getMessage())) {
      USB.println(F("Response Sent."));
    }
    else {
      USB.println(F("Response does not sent."));
    }
*/
  } else {
    USB.println(F("> No match."));
  }
}

