#pragma once

#include <Arduino.h>
#include <Preferences.h>
#include <vector>
#include <functional>

struct ConfigEntry {
    const char* key;
    void* ptr;
    enum Type {
        TYPE_BOOL,
        TYPE_INT,
        TYPE_INT8,
        TYPE_UINT8,
        TYPE_STRING
    } type;
    size_t maxLen;
    int32_t defaultInt;
    const char* defaultStr;
};

class GS32Config {
public:
    GS32Config();
    
    bool begin(const char* nameSpace = "gs32_cfg");

    void addBool(const char* key, bool* ptr, bool defaultVal = false);
    void addInt(const char* key, int* ptr, int defaultVal = 0);
    void addInt8(const char* key, int8_t* ptr, int8_t defaultVal = 0);
    void addUInt8(const char* key, uint8_t* ptr, uint8_t defaultVal = 0);

    void addText(const char* key, char* ptr, size_t maxLen, const char* defaultVal = "");

    void load();
    void save();
    void factoryReset();

    const std::vector<ConfigEntry>& getEntries() const { return _entries; }

private:
    Preferences _prefs;
    const char* _ns;
    std::vector<ConfigEntry> _entries;
};
