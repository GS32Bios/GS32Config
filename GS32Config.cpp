#include "GS32Config.h"

GS32Config::GS32Config() : _ns("gs32_cfg") {}

bool GS32Config::begin(const char* nameSpace) {
    _ns = nameSpace;
    return _prefs.begin(_ns, false);
}

void GS32Config::addBool(const char* key, bool* ptr, bool defaultVal) {
    ConfigEntry entry = {String(key), (void*)ptr, ConfigEntry::TYPE_BOOL, 0, defaultVal ? 1 : 0, ""};
    *ptr = defaultVal;
    _entries.push_back(entry);
}

void GS32Config::addInt(const char* key, int* ptr, int defaultVal) {
    ConfigEntry entry = {String(key), (void*)ptr, ConfigEntry::TYPE_INT, 0, defaultVal, ""};
    *ptr = defaultVal;
    _entries.push_back(entry);
}

void GS32Config::addInt8(const char* key, int8_t* ptr, int8_t defaultVal) {
    ConfigEntry entry = {String(key), (void*)ptr, ConfigEntry::TYPE_INT8, 0, defaultVal, ""};
    *ptr = defaultVal;
    _entries.push_back(entry);
}

void GS32Config::addUInt8(const char* key, uint8_t* ptr, uint8_t defaultVal) {
    ConfigEntry entry = {String(key), (void*)ptr, ConfigEntry::TYPE_UINT8, 0, defaultVal, ""};
    *ptr = defaultVal;
    _entries.push_back(entry);
}

void GS32Config::addText(const char* key, char* ptr, size_t maxLen, const char* defaultVal) {
    ConfigEntry entry = {String(key), (void*)ptr, ConfigEntry::TYPE_STRING, maxLen, 0, String(defaultVal)};
    memset(ptr, 0, maxLen);
    strncpy(ptr, defaultVal, maxLen - 1);
    _entries.push_back(entry);
}

void GS32Config::load() {
    for (const auto& entry : _entries) {
        switch (entry.type) {
            case ConfigEntry::TYPE_BOOL: {
                bool* p = (bool*)entry.ptr;
                if (_prefs.isKey(entry.key.c_str())) *p = _prefs.getBool(entry.key.c_str(), entry.defaultInt);
                else _prefs.putBool(entry.key.c_str(), *p);
                break;
            }
            case ConfigEntry::TYPE_INT: {
                int* p = (int*)entry.ptr;
                if (_prefs.isKey(entry.key.c_str())) *p = _prefs.getInt(entry.key.c_str(), entry.defaultInt);
                else _prefs.putInt(entry.key.c_str(), *p);
                break;
            }
            case ConfigEntry::TYPE_INT8: {
                int8_t* p = (int8_t*)entry.ptr;
                if (_prefs.isKey(entry.key.c_str())) *p = (int8_t)_prefs.getChar(entry.key.c_str(), entry.defaultInt);
                else _prefs.putChar(entry.key.c_str(), *p);
                break;
            }
            case ConfigEntry::TYPE_UINT8: {
                uint8_t* p = (uint8_t*)entry.ptr;
                if (_prefs.isKey(entry.key.c_str())) *p = (uint8_t)_prefs.getUChar(entry.key.c_str(), entry.defaultInt);
                else _prefs.putUChar(entry.key.c_str(), *p);
                break;
            }
            case ConfigEntry::TYPE_STRING: {
                char* p = (char*)entry.ptr;
                if (_prefs.isKey(entry.key.c_str())) {
                    String val = _prefs.getString(entry.key.c_str(), entry.defaultStr.c_str());
                    strncpy(p, val.c_str(), entry.maxLen - 1);
                } else {
                    _prefs.putString(entry.key.c_str(), p);
                }
                break;
            }
        }
    }
}

void GS32Config::save() {
    Serial.println("--- Saving Config ---");
    for (const auto& entry : _entries) {
        Serial.print("Saving key: "); Serial.print(entry.key);
        Serial.print(" | Value: "); 
        switch (entry.type) {
            case ConfigEntry::TYPE_BOOL:
                Serial.println(*((bool*)entry.ptr));
                _prefs.putBool(entry.key.c_str(), *((bool*)entry.ptr));
                break;
            case ConfigEntry::TYPE_INT:
                Serial.println(*((int*)entry.ptr));
                _prefs.putInt(entry.key.c_str(), *((int*)entry.ptr));
                break;
            case ConfigEntry::TYPE_INT8:
                Serial.println(*((int8_t*)entry.ptr));
                _prefs.putChar(entry.key.c_str(), *((int8_t*)entry.ptr));
                break;
            case ConfigEntry::TYPE_UINT8:
                Serial.println(*((uint8_t*)entry.ptr));
                _prefs.putUChar(entry.key.c_str(), *((uint8_t*)entry.ptr));
                break;
            case ConfigEntry::TYPE_STRING:
                Serial.println((char*)entry.ptr);
                _prefs.putString(entry.key.c_str(), (char*)entry.ptr);
                break;
        }
    }
}

void GS32Config::factoryReset() {
    for (const auto& entry : _entries) {
        switch (entry.type) {
            case ConfigEntry::TYPE_BOOL: {
                bool* p = (bool*)entry.ptr;
                *p = entry.defaultInt;
                _prefs.putBool(entry.key.c_str(), *p);
                break;
            }
            case ConfigEntry::TYPE_INT: {
                int* p = (int*)entry.ptr;
                *p = entry.defaultInt;
                _prefs.putInt(entry.key.c_str(), *p);
                break;
            }
            case ConfigEntry::TYPE_INT8: {
                int8_t* p = (int8_t*)entry.ptr;
                *p = (int8_t)entry.defaultInt;
                _prefs.putChar(entry.key.c_str(), *p);
                break;
            }
            case ConfigEntry::TYPE_UINT8: {
                uint8_t* p = (uint8_t*)entry.ptr;
                *p = (uint8_t)entry.defaultInt;
                _prefs.putUChar(entry.key.c_str(), *p);
                break;
            }
            case ConfigEntry::TYPE_STRING: {
                char* p = (char*)entry.ptr;
                memset(p, 0, entry.maxLen);
                strncpy(p, entry.defaultStr.c_str(), entry.maxLen - 1);
                _prefs.putString(entry.key.c_str(), p);
                break;
            }
        }
    }
}
