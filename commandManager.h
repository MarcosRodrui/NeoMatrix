#ifndef _COMMANDMANGER_H_
#define _COMMANDMANGER_H_

#include <iostream>
#include <vector>
#include <cstring>

using std::vector;
using std::cout;
using std::string;

typedef enum _cmd_res{
    CMD_DEFAULT,
    CMD_HELP,
    CMD_EFFECT,
    CMD_RESTART
} cmd_res;

class CommandManager{
private:
    string version;

    cmd_res DisplayOutput(cmd_res result);
    void HelpOutput();
    void RestartOutput();

public:
    CommandManager(string version);
    cmd_res CheckParameters(int argc, char *argv[]);
};


#endif
