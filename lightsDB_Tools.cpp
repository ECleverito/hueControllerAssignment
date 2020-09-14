
#include <vector>
#include <string>
#include <iostream>

#include "dataTypes.h"
#include "lightsDB_Tools.h"

using namespace std;

int dbUpdateCheck(vector<struct light> * lightsVec, vector<struct light> * newLightData)
{

  char changeFlag = 0;

  for(int i=0;i<lightsVec->size();i++)
  {

    if(lightsVec->at(i).powerState != newLightData->at(i).powerState)
    {

        lightsVec->at(i).powerState = newLightData->at(i).powerState;
        outputLightDataChange(&lightsVec->at(i),0);

        changeFlag=1;
    }

    if(lightsVec->at(i).brightness != newLightData->at(i).brightness)
    {

        lightsVec->at(i).brightness = newLightData->at(i).brightness;
        outputLightDataChange(&lightsVec->at(i),1);

        changeFlag=1;
    }

  }
  return changeFlag;
}

string bool2Str(bool b)
{

  return b ? "true" : "false";

}


//'dataSelector' argument allows user to select data type that is output
//dataSelector = 0 returns 'on'
//dataSelector = 1 returns 'brightness'
void outputLightDataChange(struct light * myLight, char dataSelector)
{

  string selectedData;

  switch(dataSelector) {

    //Returns 'powerState' AKA 'on' property
    case 0:

      selectedData = "\"on\":\"" + bool2Str(myLight->powerState);
      selectedData +="\"";
      break;

    //Returns 'brightness' property
    case 1:

      selectedData = "\"bri\":\""+myLight->brightness+"\"";
      break;

    default:

      cout << "Invalid 'dataSelector' argument entered. 0 = 'on'; 1 = 'bri'" << endl;

  }

  cout << "{" << endl;
  cout << "\t" << "\"id\":\""+myLight->id+"\"," << endl;
  cout << "\t" << selectedData << endl;
  cout << "}" << endl;

}
