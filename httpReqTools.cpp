
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include <Poco/Net/IPAddress.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/StreamCopier.h>
#include <Poco/Path.h>

#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/Parser.h>
#include <Poco/JSON/ParseHandler.h>

using namespace Poco::Net;
using namespace std;
using namespace Poco;

#include "dataTypes.h"
#include "httpReqTools.h"

//Function for sending GET requests to the bridge and specified path
//and returning the JSON objects in that path.
Dynamic::Var httpGetJSON(struct ipConfig myConfig,string myPath){

    //Start session
    HTTPClientSession session(myConfig.ipAddr, myConfig.port);

    //Create and send request
    HTTPRequest req(HTTPRequest::HTTP_GET, myPath, HTTPMessage::HTTP_1_1);
    session.sendRequest(req);

    //Get response and store in an input stream
    HTTPResponse res;
    istream &is = session.receiveResponse(res);

    //Create JSON parser and parse response
    JSON::Parser iparser;
    Dynamic::Var result = iparser.parse(is);

    return result;

}
