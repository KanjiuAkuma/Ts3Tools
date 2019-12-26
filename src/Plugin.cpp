/**
  * Created by Joscha Vack on 12/9/2019.
  * Required ts3 functions for plugin to load and work
  **/

#include "Plugin.h"

#include <ts3_functions.h>

#include "GlobalDefinitions.h"
#include "logger/Logger.h"

#include "util/Util.h"

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
    if (fdwReason == DLL_PROCESS_ATTACH) {
        Logger::init();
    }
    return TRUE;
}

/** Plugin info **/

const char* ts3plugin_name() {
    TS3_CALLBACK;
    return APPEND_DEBUG(PLUGIN_NAME);
}

const char* ts3plugin_version() {
    TS3_CALLBACK;
    return APPEND_DEBUG(PLUGIN_VERSION);
}

int ts3plugin_apiVersion() {
    TS3_CALLBACK;
    return PLUGIN_API_VERSION;
}

const char* ts3plugin_author() {
    TS3_CALLBACK;
    return PLUGIN_AUTHOR;
}

const char* ts3plugin_description() {
    TS3_CALLBACK;
    return APPEND_DEBUG_NL(PLUGIN_DESCRIPTION);
}

const char* ts3plugin_commandKeyword() {
    TS3_CALLBACK;
    return PLUGIN_COMMAND_PREFIX;
}

/** Plugin base functions **/

void ts3plugin_setFunctionPointers(const struct TS3Functions funcs) {
    TS3_CALLBACK;
    ts3Functions = funcs;
}

/*
 * Custom code called right after loading the plugin. Returns 0 on success, 1 on failure.
 * If the function returns 1 on failure, the plugin will be unloaded again.
 *
 * Initialize return codes here if needed
 * return: 0 = success, 1 = failure, -2 = failure but client will not show a "failed to load" warning
 */
int ts3plugin_init() {
    TS3_CALLBACK;

    /* Initialisation code */

    CORE_DEBUG("Plugin initialized");
    return 0;
}

/* Custom code called right before the plugin is unloaded */
void ts3plugin_shutdown() {
    TS3_CALLBACK;

    /* Cleanup code */

    /* Free pluginID */
    free(pluginID);
    pluginID = nullptr;
    CORE_DEBUG("Plugin shut down");
}

/* Register our plugin id so we can use all features */
void ts3plugin_registerPluginID(const char* id) {
    TS3_CALLBACK;
    const size_t sz = strlen(id) + 1;
    pluginID = (char*) malloc(sz * sizeof(char));
    _strcpy(pluginID, sz, id);  /* The id buffer will invalidate after exiting this function */
    CORE_DEBUG("Plugin id: {}", id);
}

/* Required to release the memory for parameter "data" allocated in ts3plugin_infoData and ts3plugin_initMenus */
void ts3plugin_freeMemory(void* data) {
    TS3_CALLBACK;
    free(data);
}

/*
 * Plugin requests to be always automatically loaded by the TeamSpeak 3 client unless
 * the user manually disabled it in the plugin dialog.
 * This function is optional. If missing, no autoload is assumed.
 */
int ts3plugin_requestAutoload() {
    TS3_CALLBACK;
    return 0;  /* 1 = request autoloaded, 0 = do not request autoload */
}

/** Plugin required functions **/

void ts3plugin_currentServerConnectionChanged(uint64 serverConnectionHandlerID) {
    TS3_CALLBACK_ARG("ServerConnectionHandlerID: {}", serverConnectionHandlerID);
    if (serverList.isServerNotListed(serverConnectionHandlerID)) {
        serverList.onConnectionOpened(serverConnectionHandlerID);
    }
}

void ts3plugin_onConnectStatusChangeEvent(uint64 serverConnectionHandlerID, int newStatus, unsigned int errorNumber) {
    TS3_CALLBACK_ARG("ServerConnectionHandlerID: {}, NewStatus: {}, ErrorNumber: {}", serverConnectionHandlerID, newStatus, errorNumber);
    if (newStatus == 0) { // disconnected
        serverList.onConnectionClosed(serverConnectionHandlerID);
    }
    else {
		if (serverList.isServerNotListed(serverConnectionHandlerID)) {
			serverList.onConnectionOpened(serverConnectionHandlerID);
		}
        serverList.getServer(serverConnectionHandlerID)->onConnectStatusChangeEvent(newStatus, errorNumber);
    }
}

int ts3plugin_onServerErrorEvent(uint64 serverConnectionHandlerID, const char* errorMessage, unsigned int error,
                                 const char* returnCode, const char* extraMessage) {
    TS3_CALLBACK_ARG("ServerConnectionHandlerID: {}, ErrorMessage: {}, Error: {}, ReturnCode: {}, ExtraMessage: {}",
            serverConnectionHandlerID, errorMessage, error, returnCode, extraMessage);
    return 0;
}

/* Called when a client moved */
void ts3plugin_onClientMoveEvent(uint64 serverConnectionHandlerID,
                                 anyID clientID, uint64 oldChannelID, uint64 newChannelID,
                                 int visibility, const char* moveMessage) {
    TS3_CALLBACK_ARG("ServerConnectionID: {}, ClientID: {}, OldChannelID: {}, NewChannelID: {}, Visibility: {}, MoveMessage: {}",
                     serverConnectionHandlerID, clientID, oldChannelID, newChannelID, visibility, moveMessage);
    Server* server = serverList.getServer(serverConnectionHandlerID);
    if (oldChannelID == 0) {        // client connected
        ASSERT(newChannelID != 0);
        server->onClientConnected(clientID, newChannelID, moveMessage);
    }
    else if (newChannelID == 0) {   // client disconnected
        ASSERT(oldChannelID != 0);
        server->onClientDisconnected(clientID, oldChannelID, moveMessage);
    }
    else {                          // real client move
        server->onClientMoved(clientID, oldChannelID, newChannelID, moveMessage);
    }
}

void ts3plugin_onClientMoveSubscriptionEvent(uint64 serverConnectionHandlerID,
                                             anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility) {
    TS3_CALLBACK_ARG("ServerConnectionID: {}, ClientID: {}, OldChannelID: {}, NewChannelID: {}, Visibility: {}",
                     serverConnectionHandlerID, clientID, oldChannelID, newChannelID, visibility);

    Server* server = serverList.getServer(serverConnectionHandlerID);
    // subscription events are sent upon joining the server so we need to ignore these
    if (server->isConnectionReady()) server->onClientMovedSubscription(clientID, oldChannelID, newChannelID);
}

void ts3plugin_onClientMoveTimeoutEvent(uint64 serverConnectionHandlerID,
                                        anyID clientID, uint64 oldChannelID, uint64 newChannelID,
                                        int visibility, const char* timeoutMessage) {
    TS3_CALLBACK_ARG("ServerConnectionID: {}, ClientID: {}, OldChannelID: {}, NewChannelID: {}, Visibility: {}, TimeoutMessage: {}",
                     serverConnectionHandlerID, clientID, oldChannelID, newChannelID, visibility, timeoutMessage);
    ASSERT(newChannelID == 0);
    serverList.getServer(serverConnectionHandlerID)->onClientDisconnected(clientID, oldChannelID, timeoutMessage);
}

/* Called when a client was moved */
void ts3plugin_onClientMoveMovedEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID,
                                      uint64 newChannelID, int visibility, anyID moverID, const char* moverName,
                                      const char* moverUniqueIdentifier, const char* moveMessage) {
    TS3_CALLBACK_ARG(
            "ServerConnectionHandlerID: {}, ClientID: {}, OldChannelID: {}, NewChannelID: {}, Visibility: {}, MoverID: {}, MoverName: {}, MoverUniqueIdentifier: {}, MoveMessage: {}",
            serverConnectionHandlerID, clientID, oldChannelID, newChannelID, visibility, moverID, moverName, moverUniqueIdentifier, moveMessage);
    serverList.getServer(serverConnectionHandlerID)->onClientWasMoved(clientID, oldChannelID, newChannelID, moverID, moveMessage);
}

void ts3plugin_onClientKickFromChannelEvent(uint64 serverConnectionHandlerID,
                                            anyID clientID, uint64 oldChannelID, uint64 newChannelID,
                                            int visibility, anyID kickerID, const char* kickerName,
                                            const char* kickerUniqueIdentifier, const char* kickMessage) {
    TS3_CALLBACK_ARG(
            "ServerConnectionHandlerID: {}, ClientID: {}, OldChannelID: {}, NewChannelID: {}, Visibility: {}, KickerID: {}, KickerName: {}, KickerUniqueIdentifier: {}, KickMessage: {}",
            serverConnectionHandlerID, clientID, oldChannelID, newChannelID, visibility, kickerID, kickerName, kickerUniqueIdentifier, kickMessage);
    serverList.getServer(serverConnectionHandlerID)->onClientKickedFromChannel(clientID, oldChannelID, newChannelID, kickerID, kickMessage);
}

void ts3plugin_onClientKickFromServerEvent(uint64 serverConnectionHandlerID,
                                           anyID clientID, uint64 oldChannelID, uint64 newChannelID,
                                           int visibility, anyID kickerID, const char* kickerName,
                                           const char* kickerUniqueIdentifier, const char* kickMessage) {
    TS3_CALLBACK_ARG(
            "ServerConnectionHandlerID: {}, ClientID: {}, OldChannelID: {}, NewChannelID: {}, Visibility: {}, KickerID: {}, KickerName: {}, KickerUniqueIdentifier: {}, KickMessage: {}",
            serverConnectionHandlerID, clientID, oldChannelID, newChannelID, visibility, kickerID, kickerName, kickerUniqueIdentifier, kickMessage);
    ASSERT(newChannelID == 0);
    serverList.getServer(serverConnectionHandlerID)->onClientKickFromServer(clientID, oldChannelID, kickerID, kickMessage);
}

/** Plugin menu and hotkeys setup **/

/* Helper function to create a menu item */
static struct PluginMenuItem* createMenuItem(enum PluginMenuType type, int id, const char* text, const char* icon) {
    auto* menuItem = (struct PluginMenuItem*)malloc(sizeof(struct PluginMenuItem));
    menuItem->type = type;
    menuItem->id = id;
    _strcpy(menuItem->text, PLUGIN_MENU_BUFSZ, text);
    _strcpy(menuItem->icon, PLUGIN_MENU_BUFSZ, icon);
    return menuItem;
}

/* Some makros to make the code to create menu items a bit more readable */
#define BEGIN_CREATE_MENUS(x) const size_t sz = x + 1; size_t n = 0; *menuItems = (struct PluginMenuItem**)malloc(sizeof(struct PluginMenuItem*) * sz);
#define CREATE_MENU_ITEM(a, b, c, d) (*menuItems)[n++] = createMenuItem(a, b, c, d);
#define END_CREATE_MENUS (*menuItems)[n++] = NULL; assert(n == sz);
#define NO_MENUS BEGIN_CREATE_MENUS(0); END_CREATE_MENUS

/* Initialized plugin menus (called when plugin is loaded */
void ts3plugin_initMenus(struct PluginMenuItem*** menuItems, char** menuIcon) {
    TS3_CALLBACK;
    /** !! Use NO_MENUS if you don't want to use menus or else Ts3 will crash !! **/
    NO_MENUS;
}

/* Helper function to create a hotkey */
static struct PluginHotkey* createHotkey(const char* keyword, const char* description) {
    auto* hotkey = (struct PluginHotkey*)malloc(sizeof(struct PluginHotkey));
    _strcpy(hotkey->keyword, PLUGIN_HOTKEY_BUFSZ, keyword);
    _strcpy(hotkey->description, PLUGIN_HOTKEY_BUFSZ, description);
    return hotkey;
}

/* Some makros to make the code to create hotkeys a bit more readable */
#define BEGIN_CREATE_HOTKEYS(x) const size_t sz = x + 1; size_t n = 0; *hotkeys = (struct PluginHotkey**)malloc(sizeof(struct PluginHotkey*) * sz);
#define CREATE_HOTKEY(a, b) (*hotkeys)[n++] = createHotkey(a, b);
#define END_CREATE_HOTKEYS (*hotkeys)[n++] = NULL; assert(n == sz);
#define NO_HOTKEYS BEGIN_CREATE_HOTKEYS(0); END_CREATE_HOTKEYS

/* Initialized plugin hotkeys (called when plugin is loaded */
void ts3plugin_initHotkeys(struct PluginHotkey*** hotkeys) {
    TS3_CALLBACK;
    /** !! Use NO_HOTKEYS if you don't want to use hotkeys or Ts3 will crash !! **/
    NO_HOTKEYS;
}

/** Plugin menu, hotkey and command callbacks **/

void ts3plugin_onMenuItemEvent(uint64 serverConnectionHandlerID, enum PluginMenuType type, int menuItemID,
                               uint64 selectedItemID) {
    TS3_CALLBACK;
}

void ts3plugin_onHotkeyEvent(const char* keyword) {
    TS3_CALLBACK;
}

int ts3plugin_processCommand(uint64 serverConnectionHandlerID, const char* command) {
    TS3_CALLBACK_ARG("serverConnectionHandlerID: {}, Command: {}", serverConnectionHandlerID, command);
    commandProcessor.processCommand(serverList.getServer(serverConnectionHandlerID), command);
    return 0;
}

/** Plugin info data **/

const char* ts3plugin_infoTitle() {
    TS3_CALLBACK;
    return "Info: ";
}

void ts3plugin_infoData(uint64 serverConnectionHandlerID, uint64 id, enum PluginItemType type, char** data) {
    TS3_CALLBACK;
}
