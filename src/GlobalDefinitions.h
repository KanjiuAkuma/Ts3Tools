/**
  * Created by Joscha Vack on 12/9/2019.
  *
  **/

#ifndef TS3TOOLS_GLOBALDEFINITIONS_H
#define TS3TOOLS_GLOBALDEFINITIONS_H

#include "ts3_functions.h"
#include "base/server/ServerList.h"
#include "commandProcessor/CommandProcessor.h"

extern TS3Functions ts3Functions;
extern char* pluginID;
extern ServerList serverList;
extern CommandProcessor commandProcessor;

#endif //TS3TOOLS_GLOBALDEFINITIONS_H
