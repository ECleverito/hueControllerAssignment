#ifndef LIGHTSDB_TOOLS_H
#define LIGHTSDB_TOOLS_H

int dbUpdateCheck(std::vector<struct light> *, std::vector<struct light> *);

void outputLightDataChange(struct light *, char);

std::string bool2Str(bool);

#endif
