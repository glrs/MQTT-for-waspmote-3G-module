#ifndef client_h
#define client_h

class Client {
  
public:
  virtual int8_t connect(const char *host, uint16_t port) = 0;
  
  virtual int available() = 0;
  virtual uint8_t connected();
  
  virtual uint16_t read(char *buf);
  virtual void stop() = 0;
  
  virtual size_t write(uint8_t) = 0;
  virtual boolean write(uint8_t *buf, uint16_t size) = 0;
  
protected:
};

#endif
