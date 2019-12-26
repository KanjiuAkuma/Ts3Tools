/**
  * Created by Joscha Vack on 12/9/2019.
  * Required ts3 functions for plugin to load and work
  **/

#ifndef TS3TOOLS_PLUGIN_H
#define TS3TOOLS_PLUGIN_H

/* Disable compiler warnings */
#pragma warning (disable : 4100)  /* Disable Unreferenced parameter warning */

#include <Windows.h>
#include <teamspeak/public_definitions.h>

#include "Macros.h"

extern "C" {
    // Dll Startup
    BOOL WINAPI DllMain (HINSTANCE const instance, DWORD const reason, LPVOID const reserved);

    // Plugin info
    PLUGINS_EXPORTDLL int ts3plugin_apiVersion();
    PLUGINS_EXPORTDLL const char* ts3plugin_name();
    PLUGINS_EXPORTDLL const char* ts3plugin_version();
    PLUGINS_EXPORTDLL const char* ts3plugin_author();
    PLUGINS_EXPORTDLL const char* ts3plugin_description();
    PLUGINS_EXPORTDLL const char* ts3plugin_commandKeyword();

    // Plugin base functions
    PLUGINS_EXPORTDLL void ts3plugin_setFunctionPointers(struct TS3Functions funcs);
    PLUGINS_EXPORTDLL int ts3plugin_init();
    PLUGINS_EXPORTDLL void ts3plugin_shutdown();
    PLUGINS_EXPORTDLL void ts3plugin_registerPluginID(const char* id);
    PLUGINS_EXPORTDLL void ts3plugin_freeMemory(void* data);
    PLUGINS_EXPORTDLL int ts3plugin_requestAutoload();

    // Plugin required functions
    PLUGINS_EXPORTDLL void ts3plugin_currentServerConnectionChanged(uint64 serverConnectionHandlerID);
    PLUGINS_EXPORTDLL void ts3plugin_onConnectStatusChangeEvent(uint64 serverConnectionHandlerID, int newStatus, unsigned int errorNumber);
    PLUGINS_EXPORTDLL int  ts3plugin_onServerErrorEvent(uint64 serverConnectionHandlerID, const char* errorMessage, unsigned int error, const char* returnCode, const char* extraMessage);
    PLUGINS_EXPORTDLL void ts3plugin_onClientMoveEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, const char* moveMessage);
    PLUGINS_EXPORTDLL void ts3plugin_onClientMoveSubscriptionEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility);
    PLUGINS_EXPORTDLL void ts3plugin_onClientMoveTimeoutEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, const char* timeoutMessage);
    PLUGINS_EXPORTDLL void ts3plugin_onClientMoveMovedEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, anyID moverID, const char* moverName, const char* moverUniqueIdentifier, const char* moveMessage);
    PLUGINS_EXPORTDLL void ts3plugin_onClientKickFromChannelEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, anyID kickerID, const char* kickerName, const char* kickerUniqueIdentifier, const char* kickMessage);
    PLUGINS_EXPORTDLL void ts3plugin_onClientKickFromServerEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, anyID kickerID, const char* kickerName, const char* kickerUniqueIdentifier, const char* kickMessage);

    // Plugin menu and hotkeys setup
    PLUGINS_EXPORTDLL void ts3plugin_initMenus(struct PluginMenuItem*** menuItems, char** menuIcon);
    PLUGINS_EXPORTDLL void ts3plugin_initHotkeys(struct PluginHotkey*** hotkeys);

    // Plugin menu, hotkey and command callbacks
    PLUGINS_EXPORTDLL void ts3plugin_onMenuItemEvent(uint64 serverConnectionHandlerID, enum PluginMenuType type, int menuItemID, uint64 selectedItemID);
    PLUGINS_EXPORTDLL void ts3plugin_onHotkeyEvent(const char* keyword);
    PLUGINS_EXPORTDLL int ts3plugin_processCommand(uint64 serverConnectionHandlerID, const char* command);

    // Plugin info data
    PLUGINS_EXPORTDLL const char* ts3plugin_infoTitle();
    PLUGINS_EXPORTDLL void ts3plugin_infoData(uint64 serverConnectionHandlerID, uint64 id, enum PluginItemType type, char** data);


};

#endif //TS3TOOLS_PLUGIN_H
