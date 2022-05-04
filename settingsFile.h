#ifndef _SETTINGSFILE_H_
#define _SETTINGSFILE_H_

#include <filesystem>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <pwd.h>

#include <string>
#include <vector>

using std::vector;
using std::string;

typedef struct 
{
    string code;
    string data;
}SettingsData;

class SettingsFile
{
private:
    vector<SettingsData> settingsData;
    std::filesystem::path dirPath;
    std::filesystem::path filePath;
    bool CheckSettingsFile(); //Returns True if everything is OK
public:
    SettingsFile();
    ~SettingsFile();
    bool CreateSettingsFile(bool restart); //If there is something wrong with the files
    string GetSettingsData(string code);
    void ChangeSettingsValue(string code, string newValue);
    void ResetSettingsFile();
};

#endif
