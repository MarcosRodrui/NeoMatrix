#include "commandManager.h"

CommandManager::CommandManager(string version)
{
   this->version = version; 
}

cmd_res CommandManager::CheckParameters(int argc, char *argv[])
{
    if(argc == 1)
        return DisplayOutput(CMD_DEFAULT);
    if(argc > 2)
        return DisplayOutput(CMD_HELP);

    if(argv[1][0] != '-')
        return DisplayOutput(CMD_HELP);

    argv[1] = argv[1] + 1;
    if(!strcmp(argv[1], "h") || !strcmp(argv[1], "-help"))
        return DisplayOutput(CMD_HELP);
    else if(!strcmp(argv[1], "e") || !strcmp(argv[1], "-effect"))
        return DisplayOutput(CMD_EFFECT);
    else if(!strcmp(argv[1], "r") || !strcmp(argv[1], "-restart"))
        return DisplayOutput(CMD_RESTART);
    else
        return DisplayOutput(CMD_HELP);
}

cmd_res CommandManager::DisplayOutput(cmd_res result)
{
    switch(result)
    {
        case CMD_HELP:
            HelpOutput();
            return CMD_HELP;
        case CMD_RESTART:
            RestartOutput();
            return CMD_RESTART;
        default:
            return result;
    }
}


//PRIVATE FUNCTIONS
void CommandManager::HelpOutput()
{
    int minKeyDist = 20;

    cout << "Neomatrix " << version << "\n";
    cout << "MarcosRodrui 2021\n\n";

    vector<string> keys;
    string helpKey = "-h --help";
    string effectKey = "-e --effect"; 
    string restartKey = "-r --restart";
    keys.push_back(helpKey);
    keys.push_back(effectKey);
    keys.push_back(restartKey);

    vector<string> desc;
    string helpDesc = "Print the help screen";
    string effectDesc = "Starts the effect omitting the menu";
    string restartDesc = "Restart the settings to the default values";
    desc.push_back(helpDesc);
    desc.push_back(effectDesc);
    desc.push_back(restartDesc);

    for(int i = 0; i < keys.size(); i++)
    {
        cout << keys[i];
        for(int j = 0; j < minKeyDist - int(keys[i].size()); j++)
            cout << " ";
        cout << desc[i];
        cout << "\n";
    }
}

void CommandManager::RestartOutput()
{
    cout << "All settings have been restarted to their default value.\n";
}
