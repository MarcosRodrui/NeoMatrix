#ifndef _INFOMANAGER_H_
#define _INFOMANAGER_H_

#include <curses.h>
#include <string>

#include "settingsManager.h"
#include "effects.h"



using std::string;

class InfoManager
{
private:
    WINDOW *win, *startWin;
    int height;
    int width;
    int startWidth;
    int startHeight;
    int startPWidth;
    int startPHeight;

    SettingsManager *settingsManager;
    EffectController *effectController;

    void ShowStart();
    void ShowSettings();
    void ShowCredits();

public:
    InfoManager(SettingsFile * settingsFile, EffectController * effectController);
    ~InfoManager();
    void ShowSelected(int selectedWindow);
    void EraseInfo(); //When a new Option is selected everything is erased
    void DestroyInfo();
    void CreateInfo(int selectedWindow, int width, int height, int startWidth, int startHeight);

    void SettingsInput(int input);
    SettingsManager * GetSettingsManager();
};

#endif
