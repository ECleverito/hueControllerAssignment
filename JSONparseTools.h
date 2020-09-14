#ifndef JSON_PARSE_TOOLS_H
#define JSON_PARSE_TOOLS_H

std::string pocoDynVar2String(Poco::Dynamic::Var);

int updateLightStates(struct light *,Poco::Dynamic::Var);

std::vector<struct light> createLightsVec(Poco::Dynamic::Var);

int updateLightsVec(std::vector<struct light> *, struct ipConfig);

#endif
