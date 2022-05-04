#ifndef _SCREENMANAGER_H_
#define _SCREENMANAGER_H_

#include <curses.h>
#include <string>

#include "titleManager.h"
#include "menuManager.h"
#include "infoManager.h"
#include "effects.h"
#include "settingsFile.h"

#include <sys/ioctl.h>
#include <unistd.h>

using std::string;

//MENU: Main menu shown by default
//MAIN: Main effect state
//LOCKED: Locked Screen
enum ScreenState{MENU, MAIN, LOCKED};

class ScreenManager
{
private:
    ScreenState state;
    TitleManager *titleManager;
    MenuManager *menuManager;
    InfoManager *infoManager;
    EffectController *effectController;

    bool effectVar; //when it's executed with -e

    void CreateMenu(int, int); //Creates the whole menu (Initialize and after resize)
    void DestroyMenu();
    void CreateStart();

public:
    ScreenManager(bool effectVar, SettingsFile *settingsFile);
    ~ScreenManager();
    void UpdateScreen(); //Use when initialize program and after resize

    bool CheckInput(int); //Checks Input, if the result is TRUE it will exit the program
};

#endif
