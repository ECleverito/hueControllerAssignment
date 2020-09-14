#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>

#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/Parser.h>
#include <Poco/JSON/ParseHandler.h>
#include <Poco/JSON/Query.h>

#include "httpReqTools.h"
#include "JSONparseTools.h"
#include "lightsDB_Tools.h"
#include "dataTypes.h"

using namespace std;
using namespace Poco;

int main(int argc, char * argv[]){

  string ipConfigPortStr;
  struct ipConfig simulatorIPConfig;

  cout << endl << "Please enter the bridge's IP Address: ";
  cin >> simulatorIPConfig.ipAddr;
  cout << endl;

  cout << endl << "Thank you. Now please enter the port #: ";
  cin >> ipConfigPortStr;
  cout << endl;

  simulatorIPConfig.port = stoi(ipConfigPortStr);

  string lightsPath = "/api/newdeveloper/lights";

  vector<struct light> lightsVec = createLightsVec(httpGetJSON(simulatorIPConfig, lightsPath));

  updateLightsVec(&lightsVec, simulatorIPConfig);

  for(struct light i : lightsVec)
  {

    cout << "{" << endl;
    cout << "\t" << "\"name\":\""+i.name+"\"," << endl;
    cout << "\t" << "\"id\":\""+i.id+"\"," << endl;
    cout << "\t" << "\"on\":\""+bool2Str(i.powerState)+"\"," << endl;
    cout << "\t" << "\"bri\":\""+i.brightness+"\"," << endl;
    cout << "}" << endl;

  }

  vector<struct light> lightsOnBridge = createLightsVec(httpGetJSON(simulatorIPConfig, lightsPath));

  while(1)
  {

    usleep(250000);

    updateLightsVec(&lightsOnBridge, simulatorIPConfig);

    dbUpdateCheck(&lightsVec, &lightsOnBridge);


  }

  return 0;

}
