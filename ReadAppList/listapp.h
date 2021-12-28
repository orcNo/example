#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <vector>

struct AppInfo {
    std::string name;
    std::string version;

    AppInfo() = default;
    AppInfo(const AppInfo& rhl);
};


std::vector<AppInfo> GetAppList();

#endif // LOGGER_H
