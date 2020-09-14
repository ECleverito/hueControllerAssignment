
#ifndef DATATYPES_H
#define DATATYPES_H

struct light{

  std::string name,id,brightness;
  bool powerState;

};

struct ipConfig{

  std::string ipAddr;
  int port;

};

#endif
