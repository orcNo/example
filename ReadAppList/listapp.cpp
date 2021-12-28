#include "listapp.h"

#include <stdarg.h>

#include <windows.h>
#include <windef.h>

#ifdef WIN32
#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383

#define printf

typedef bool (*ExpFunc)(const char*, bool bSub);
typedef void (*ActionFunc)(HKEY, const char*, const char*);
#undef tfunc
//typename tfunc findCb;

template <class Exp, class Action>
void ReadRegistryKey(HKEY hKey, const char *subKey, Exp *exp, Action *action);

std::vector<std::pair<HKEY, std::string>> keyList = { {HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall"},
                                     {HKEY_CURRENT_USER ,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall"},
                                     {HKEY_LOCAL_MACHINE, "SOFTWARE\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall"}};
#endif

AppInfo::AppInfo(const AppInfo& rhl)
    : name(rhl.name)
    , version(rhl.version) {

}

std::vector<AppInfo> GetAppList() {
    std::vector<AppInfo> v;
#ifdef WIN32
    for (auto ite : keyList) {
        auto action = [&v](HKEY hHey, const char* key, const char* value) {
            if (!key)
                return;

            AppInfo app;
            bool isApp = true;
            ExpFunc exp2 = [](const char *str, bool bSub) -> bool {
                return strcmp(str, "ParentKeyName") == 0
                        || strcmp(str, "ParentDisplayName") == 0
                        || strcmp(str, "SystemComponent") == 0
                        || strcmp(str, "DisplayName") == 0
                        || strcmp(str, "DisplayVersion") == 0;
            };
            auto action2 = [&app, &isApp](HKEY hkey, const char* key, const char* value) {
                if (strcmp(key, "ParentKeyName") == 0) {
                    isApp = false;
                } else if (strcmp(key, "ParentDisplayName") == 0) {
                    isApp = false;
                } else if (strcmp(key, "SystemComponent") == 0){
                    if (atoi(value) == 1) {
                        isApp = false;
                    }
                } else if (strcmp(key, "DisplayName") == 0){
                    app.name = value;
                } else if (strcmp(key, "DisplayVersion") == 0) {
                    app.version = value;
                }
            };
            ReadRegistryKey(hHey, key, &exp2, &action2);
            if (!app.name.empty() && isApp) {
                v.push_back(app);
            }
        };
        auto exp = [](const char *str, bool bSub) ->bool {
            return bSub && strlen(str) > 0;
        };
        ReadRegistryKey(ite.first, ite.second.c_str(), &exp, &action);
    }
#endif
    return v;
}

template <class Exp, class Action>
void ReadRegistryKey(HKEY hKey, const char *subKey, Exp* exp , Action* cb) {
    HKEY hTestKey;
    if(RegOpenKeyEx(hKey,
            subKey,
            0,
            KEY_READ,
            &hTestKey) != ERROR_SUCCESS) {
        return;
    }

    TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
    DWORD    cbName;                   // size of name string
    TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name
    DWORD    cchClassName = MAX_PATH;  // size of class string
    DWORD    cSubKeys=0;               // number of subkeys
    DWORD    cbMaxSubKey;              // longest subkey size
    DWORD    cchMaxClass;              // longest class string
    DWORD    cValues;              // number of values for key
    DWORD    cchMaxValue;          // longest value name
    DWORD    cbMaxValueData;       // longest value data
    DWORD    cbSecurityDescriptor; // size of security descriptor
    FILETIME ftLastWriteTime;      // last write time

    DWORD i, retCode;

    TCHAR  achValue[MAX_VALUE_NAME];
    DWORD cchValue = MAX_VALUE_NAME;

    // Get the class name and the value count.
    retCode = RegQueryInfoKey(
        hTestKey,                    // key handle
        achClass,                // buffer for class name
        &cchClassName,           // size of class string
        NULL,                    // reserved
        &cSubKeys,               // number of subkeys
        &cbMaxSubKey,            // longest subkey size
        &cchMaxClass,            // longest class string
        &cValues,                // number of values for this key
        &cchMaxValue,            // longest value name
        &cbMaxValueData,         // longest value data
        &cbSecurityDescriptor,   // security descriptor
        &ftLastWriteTime);       // last write time

    // Enumerate the subkeys, until RegEnumKeyEx fails.

    if (cSubKeys)
    {
        printf( "\nNumber of subkeys: %lu\n", cSubKeys);

        for (i=0; i<cSubKeys; i++)
        {
            cbName = MAX_KEY_LENGTH;
            retCode = RegEnumKeyEx(hTestKey, i,
                     achKey,
                     &cbName,
                     NULL,
                     NULL,
                     NULL,
                     &ftLastWriteTime);
            if (retCode == ERROR_SUCCESS)
            {
                printf(TEXT("(%lu) %s\n"), i+1, achKey);
                cchValue = MAX_VALUE_NAME;
                achValue[0] = '\0';

                retCode = RegEnumValue(hTestKey, i,
                    achValue,
                    &cchValue,
                    NULL,
                    NULL,
                    NULL,
                    NULL);

                if (retCode == ERROR_SUCCESS )
                {
                    printf(TEXT("(%lu) %s\n"), i+1, achValue);
                }
                if (exp && (*exp)(achKey, true) && cb) {
                    (*cb)(hTestKey, achKey, (char*)nullptr);
                }
            }
        }
    }

    // Enumerate the key values.
    if (cValues)
    {
        printf( "\nNumber of values: %lu\n", cValues);

        for (i=0, retCode=ERROR_SUCCESS; i<cValues; i++)
        {
            cchValue = MAX_VALUE_NAME;
            achValue[0] = '\0';
            DWORD type;
            DWORD dataLen = 1024;
            BYTE data[1024];
            retCode = RegEnumValue(hTestKey, i,
                achValue,
                &cchValue,
                NULL,
                &type,
                data,
                &dataLen);

            if (retCode == ERROR_SUCCESS )
            {
                printf(TEXT("(%lu) %s\n"), i+1, achValue);
            }
            if (exp && (*exp)(achValue, false) && cb) {
                (*cb)(hTestKey, achValue, (char*)data);
            }
        }
    }
    RegCloseKey(hTestKey);
}
