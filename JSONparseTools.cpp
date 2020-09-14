#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/Parser.h>
#include <Poco/JSON/ParseHandler.h>
#include <Poco/JSON/Query.h>

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "JSONparseTools.h"
#include "httpReqTools.h"
#include "dataTypes.h"

using namespace std;
using namespace Poco;

string pocoDynVar2String(Dynamic::Var lightsReqResp)
{

  JSON::Object::Ptr obj = lightsReqResp.extract<JSON::Object::Ptr>();

  if ( lightsReqResp.type() == typeid(Poco::JSON::Object::Ptr) )
   obj = lightsReqResp.extract<Poco::JSON::Object::Ptr>();
  else
  {
    cout << "\nNot a valid type.\n";
    cout << lightsReqResp.type().name() << "\n";
  }

  stringstream parsedJSONstrm;
  string parsedJSONstrn;
  obj->stringify(parsedJSONstrm);
  parsedJSONstrn = parsedJSONstrm.str();

  return parsedJSONstrn;

}

int updateLightStates(struct light * myLight, Dynamic::Var lightStateReqResp)
{
  JSON::Object::Ptr obj = lightStateReqResp.extract<JSON::Object::Ptr>();

  if ( lightStateReqResp.type() == typeid(Poco::JSON::Object::Ptr) )
   obj = lightStateReqResp.extract<Poco::JSON::Object::Ptr>();
  else
  {
    cout << "\nNot a valid type.\n";
    cout << lightStateReqResp.type().name() << "\n";
  }

  Dynamic::Var state = obj->get("state");

  JSON::Query stateQuery(state);

  myLight->powerState = stateQuery.findValue("on",false);
  myLight->brightness = stateQuery.findValue("bri","0");

  return 0;
}

vector<struct light> createLightsVec(Dynamic::Var lightsReqResp)
{
  JSON::Object::Ptr obj = lightsReqResp.extract<JSON::Object::Ptr>();

  vector<struct light> lightsVec;

  vector<string> lightNames;
  obj->getNames(lightNames);

  struct light placeholderLight;
  Dynamic::Var placeholderLightVar;
  JSON::Object::Ptr nameObj;

  for(string i : lightNames)
  {
      placeholderLight.id = i;

      placeholderLightVar = obj->get(i);
      nameObj = placeholderLightVar.extract<JSON::Object::Ptr>();
      placeholderLightVar = nameObj->get("name");

      placeholderLight.name = placeholderLightVar.toString();

      lightsVec.push_back(placeholderLight);
  }

  return lightsVec;
}

int updateLightsVec(vector<struct light> * lightsVec,struct ipConfig simulatorIPConfig)
{

  string lightPathBaseString = "/api/newdeveloper/lights/";
  string lightPathString;

  Dynamic::Var lightStateReqResp;

  for(int i=0;i<lightsVec->size();i++)
  {

    lightPathString = lightPathBaseString + lightsVec->at(i).id;

    lightStateReqResp = httpGetJSON(simulatorIPConfig,lightPathString);

    updateLightStates(&lightsVec->at(i), lightStateReqResp);

  }

  return 0;
}
