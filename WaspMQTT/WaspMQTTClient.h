/*
 *
 * 
 *  WaspMQTTClient.h
 *
 *  The WaspMQTTClient library implements the MQTT protocol to work
 *  with the waspmote's 3G module. There were no such implementation
 *  for waspmote, although the MQTT protocol is a very good solution,
 *  especially for remote, low energy cost applications with unreliable
 *  network connection.
 *
 *  Version:		1.0
 *
 *  Design:		Glaros Anastasios (glrs)
 *
 *  Implementation:	Glaros Anastasios (glrs)
 *
 */


#ifndef WaspMQTTClient_h
#define WaspMQTTClient_h

//includes
#include <Waspmote.h>
#include "Client.h"


/** DEFINE MQTT VERSION **/
#define MQTT_PROTOCOL_VERSION  3


/** DEFINE MAX SIZES **/
#define MQTT_MAX_PACKET_SIZE    256     // Maximum packet size
#define MQTT_MAX_TOPIC_SIZE     150     // Maximum topic size
#define MQTT_MAX_MESSAGE_SIZE   150     // Maximum message size


/** DEFINE KEEP ALIVE VALUE **/
#define MQTT_KEEPALIVE    120    // keepAlive interval in Seconds


/** DEFINED VALUES - MESSAGE TYPE **/
#define MQTT_Reserved     0 << 4  // Reserved
#define MQTT_CONNECT      1 << 4  // Client request to connect to Server
#define MQTT_CONNACK      2 << 4  // Connect Acknowledgment
#define MQTT_PUBLISH      3 << 4  // Publish message
#define MQTT_PUBACK       4 << 4  // Publish Acknowledgment
#define MQTT_PUBREC       5 << 4  // Publish Received (assured delivery part 1)
#define MQTT_PUBREL       6 << 4  // Publish Release (assured delivery part 2)
#define MQTT_PUBCOMP      7 << 4  // Publish Complete (assured delivery part 3)
#define MQTT_SUBSCRIBE    8 << 4  // Client Subscribe request
#define MQTT_SUBACK       9 << 4  // Subscribe Acknowledgment
#define MQTT_UNSUBSCRIBE  10 << 4  // Client Unsubscribe request
#define MQTT_UNSUBACK     11 << 4  // Unsubscribe Acknowledgment
#define MQTT_PINGREQ      12 << 4  // PING Request
#define MQTT_PINGRESP     13 << 4  // PING Response
#define MQTT_DISCONNECT   14 << 4  // Client is Disconnecting
#define MQTT_Reserved     15 << 4  // Reserved


/** DEFINED VALUES - QoS **/
#define MQTT_QOS0    0 << 1    // At most once (Fire and Forget)
#define MQTT_QOS1    1 << 1    // At least once (Acknowledged delivery)
#define MQTT_QOS2    2 << 1    // Exactly once (Assured delivery)




class WaspMQTTClient {
private:
  Client* _client;
  uint8_t packetBuffer[MQTT_MAX_PACKET_SIZE];
  char *ip;
  uint16_t port;
  uint16_t nextMsgId;
  char* host;
  char pubTopic[MQTT_MAX_PACKET_SIZE/2];
  //char mqttMessage[MQTT_MAX_MESSAGE_SIZE];
  
  unsigned long lastInActivity;
  unsigned long lastOutActivity;
  bool pingOutstanding;
  
  void (*callback)(char*,uint8_t*,unsigned int);
  boolean connect(char *, char *, char *, char *, uint8_t, uint8_t, char*);
  uint16_t writeString(char* string, uint8_t* buf, uint16_t pos);
  boolean write(uint8_t header, uint8_t* buffer, uint16_t length);
  uint16_t readPacket();
  
public:

  void test();
  
  WaspMQTTClient();
  WaspMQTTClient(char*, uint16_t, void(*)(char*, uint8_t*, unsigned int), Client& client);
  
  boolean connect(char *, char *, char *);
  boolean connect(char *, char *, uint8_t, uint8_t, char *);
  
  boolean publish(char*, char*);
  boolean publish(char*, uint8_t*, unsigned int);
  boolean publish(char*, uint8_t*, unsigned int, boolean);
  
  boolean subscribe(char *);
  
  boolean publish(char *, char *, char *, char *);
  
  boolean commandCompare(char *, byte *, unsigned int);
  boolean connected();
  void disconnect();
  boolean loop();
};


class Wasp3GMQTTClient : public Client {
public:
  Wasp3GMQTTClient();

  int8_t connect(const char *host, uint16_t port);
  
  size_t write(uint8_t) {size_t s; return s;}    // Not implemented
  boolean write(uint8_t *buf, uint16_t size);
  
  int available() {return 1;}    // Not implemented
  int read() {return 0;}  // Not implemented
  uint16_t read(char *buf);
  
  void stop();
  uint8_t connected();
  
private:
  uint8_t isConnected;
};

int parse(const char*);
int countDigits(uint16_t);

#endif
  
  
  
  
  
  
  
  
  
  
