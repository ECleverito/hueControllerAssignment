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

  //Obtaining IP address and port of bridge
  string ipConfigPortStr;
  struct ipConfig simulatorIPConfig;

  cout << endl << "Please enter the bridge's IP Address: ";
  cin >> simulatorIPConfig.ipAddr;
  cout << endl;

  cout << endl << "Thank you. Now please enter the port #: ";
  cin >> ipConfigPortStr;
  cout << endl;

  simulatorIPConfig.port = stoi(ipConfigPortStr);

  //Obtaining lights currently on the bridge
  string lightsPath = "/api/newdeveloper/lights";

  //Creating vector of lights on the bridge and populating with the JSON data
  vector<struct light> lightsVec = createLightsVec(httpGetJSON(simulatorIPConfig, lightsPath));

  updateLightsVec(&lightsVec, simulatorIPConfig);

  //Initial display of all lights and their states
  for(struct light i : lightsVec)
  {

    cout << "{" << endl;
    cout << "\t" << "\"name\":\""+i.name+"\"," << endl;
    cout << "\t" << "\"id\":\""+i.id+"\"," << endl;
    cout << "\t" << "\"on\":\""+bool2Str(i.powerState)+"\"," << endl;
    cout << "\t" << "\"bri\":\""+i.brightness+"\"," << endl;
    cout << "}" << endl;

  }

  //Creating a comparison vector of lights containing continuously updated
  //data from bridge
  vector<struct light> lightsOnBridge = createLightsVec(httpGetJSON(simulatorIPConfig, lightsPath));

  //Continuously gather data from bridge to detect changes in states.
  //This is perfromed every 250 ms.
  while(1)
  {

    usleep(250000);

    updateLightsVec(&lightsOnBridge, simulatorIPConfig);

    //If a change is detected in either brightness or power state,
    //the data in the original vector is updated and the change is output.
    dbUpdateCheck(&lightsVec, &lightsOnBridge);

  }

  return 0;

}
