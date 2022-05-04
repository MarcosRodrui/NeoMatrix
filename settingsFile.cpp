#include "settingsFile.h"

//Temp
#include <curses.h>

const vector<string> settings {
    "letter-density",
    "min-trail-size",
    "max-trail-size",
    "min-falling-speed",
    "max-falling-speed",
    "min-change-letter",
    "max-change-letter",
    "first-letter-transition",
    "last-letter-transition",
    "terminal-colors",
    "black-color-r",
    "black-color-g",
    "black-color-b",
    "red-color-r",
    "red-color-g",
    "red-color-b",
    "green-color-r",
    "green-color-g",
    "green-color-b",
    "yellow-color-r",
    "yellow-color-g",
    "yellow-color-b",
    "blue-color-r",
    "blue-color-g",
    "blue-color-b",
    "magenta-color-r",
    "magenta-color-g",
    "magenta-color-b",
    "cyan-color-r",
    "cyan-color-g",
    "cyan-color-b",
    "white-color-r",
    "white-color-g",
    "white-color-b",
    "black-proportion",
    "red-proportion",
    "green-proportion",
    "yellow-proportion",
    "blue-proportion",
    "magenta-proportion",
    "cyan-proportion",
    "white-proportion",
    "unique-color-group",
    "background-color",
    "first-letter",
    "first-letter-black-proportion",
    "first-letter-red-proportion",
    "first-letter-green-proportion",
    "first-letter-yellow-proportion",
    "first-letter-blue-proportion",
    "first-letter-magenta-proportion",
    "first-letter-cyan-proportion",
    "first-letter-white-proportion",
    "basic-latin",
    "latin-1-supplement",
    "armenian",
    "hebrew",
    "nko",
    "mandaic",
    "devanagari",
    "thai",
    "runic",
    "hanunoo",
    "buhind",
    "limbu",
    "khmer",
    "ol_chiki",
    "tifinagh",
    "myanmar",
    "thai",
    "thai",
    "thai",
    "thai",
    "katakana"
};

const vector<string> defaultSettings{
    "23",       //letter-density
    "20",       //min-trail-size
    "55",       //max-trail-size
    "15",       //min-falling-speed
    "30",       //max-falling-speed
    "10",       //min-change-letter
    "35",       //max-change-letter
    "1",        //first-letter-transition
    "1",        //last-letter-transition
    "0",        //terminal-colors
    "0",        //black-color-r
    "0",        //black-color-g
    "0",        //black-color-b
    "255",      //red-color-r
    "0",        //red-color-g
    "0",        //red-color-b
    "0",        //green-color-r
    "210",      //green-color-g
    "0",        //green-color-b
    "255",      //yellow-color-r
    "255",      //yellow-color-g
    "0",        //yellow-color-b
    "0",        //blue-color-r
    "0",        //blue-color-g
    "255",      //blue-color-b
    "255",      //magenta-color-r
    "0",        //magenta-color-g
    "255",      //magenta-color-b
    "0",        //cyan-color-g
    "255",      //cyan-color-r
    "255",      //cyan-color-b
    "255",      //white-color-g
    "255",      //white-color-g
    "255",      //white-color-b
    "0",        //black-proportion
    "0",        //red-proportion
    "5",        //green-proportion
    "0",        //yellow-proportion
    "0",        //blue-proportion
    "0",        //magenta-proportion
    "0",        //cyan-proportion
    "0",        //white-proportion
    "1",        //unique-color-group
    "Default",  //background-color
    "1",        //first-letter
    "0",        //first-letter-black-proportion
    "0",        //first-letter-red-proportion
    "0",        //first-letter-green-proportion
    "0",        //first-letter-yellow-proportion
    "0",        //first-letter-blue-proportion
    "0",        //first-letter-magenta-proportion
    "0",        //first-letter-cyan-proportion
    "5",        //first-letter-white-proportion
    "0",        //basic-latin
    "0",         
    "0",         
    "0",         
    "0",         
    "0",         
    "0",
    "0",         
    "0",         
    "0",
    "0",
    "0",
    "0",
    "0",
    "0",
    "0",
    "0",
    "0",
    "0",
    "0",
    "0",
    "0",         
    "0",         
    "0",
    "0"
};

SettingsFile::SettingsFile(){;}

SettingsFile::~SettingsFile(){;}

bool SettingsFile::CreateSettingsFile(bool restart)
{   
    //Check if the file exits --- System dependable

    string getPath;
    uid_t uid = geteuid();
    struct passwd *pw = getpwuid(uid);    
    getPath = "/home/";
    getPath += pw->pw_name;
    getPath += "/.config";
    dirPath = getPath;

    bool exits = std::filesystem::exists(dirPath);
    if(!exits)
        create_directory(dirPath);

    getPath = dirPath += "/neomatrix";
    exits = std::filesystem::exists(dirPath);
    if(!exits)
        create_directory(dirPath);

    getPath += "/neomatrix.conf"; 

    filePath = getPath;
    exits = std::filesystem::exists(filePath);
    if(!exits || restart)
        ResetSettingsFile();
    else
    {
        if(!CheckSettingsFile())  
        {
            std::cout << "Would you like to restart the settings to the defaullt file? (Y/N)\n";
            string resetAnswer = "";
            while(resetAnswer != "Y" && resetAnswer != "N" && resetAnswer != "Yes" && resetAnswer != "No")
            {
                if(resetAnswer != "")
                    std::cout << "Invalid answer. Would you like to restart the settings to the defaullt file? (Y/N)\n";
                std::cin >> resetAnswer;
            }
            if(resetAnswer == "Y" || resetAnswer == "Yes")
                ResetSettingsFile();
            else
                return false;
        }
    }

    //If the format is OK or if it has just been created, it will take the data
    std::ifstream ifs(filePath);
    string input = "";
    while(std::getline(ifs, input))
    {
        string code = input.substr(0, input.find("="));
        string data = input.substr(input.find("=") + 1, input.length() - input.find("="));
        SettingsData newData{code, data};
        settingsData.push_back(newData);
    }
    ifs.close();

    return true;
}

string SettingsFile::GetSettingsData(string code)
{
    string found = "";
    for (int i = 0; i < settingsData.size(); i++)
    {
        if(settingsData[i].code == code)
        {
            found = settingsData[i].data;
            break;
        }
    }
    return found;
}

void SettingsFile::ChangeSettingsValue(string code, string newValue)
{
    int found = -1;
    for (int i = 0; i < settingsData.size(); i++)
    {
        if(settingsData[i].code == code)
        {
            found = i;
            break;
        }
    }
    if(found == -1)
        return;

    settingsData[found].data = newValue;
    std::ofstream ofs(filePath);
    for(int i = 0; i < settingsData.size(); i++)
        ofs << settingsData[i].code << "=" << settingsData[i].data << "\n"; 
    ofs.close();
}


void SettingsFile::ResetSettingsFile()
{
    std::ofstream ofs(filePath);
    for(int i = 0; i < settings.size(); i++)
        ofs << settings[i] << "=" << defaultSettings[i] << "\n"; 
    ofs.close();
}

/* PRIVATE FUNCTIONS */
bool SettingsFile::CheckSettingsFile()
{
    std::ifstream ifs(filePath);
    string checkData;
    bool correctFormat = true;
    for(int i = 0; i < settings.size() && correctFormat; i++)
    {
        ifs >> checkData; 
        checkData = checkData.substr(0, checkData.find("="));
        if(settings[i] != checkData)
        {
            std::cout << "Invalid input in line " << i + 1 << "\n";
            correctFormat = false;
        }
    }
    ifs.close();    
    return correctFormat;
}


