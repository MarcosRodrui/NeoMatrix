#ifndef _SETTINGSMANAGER_H_
#define _SETTINGSMANAGER_H_

#include "curses.h"
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>

#include "settingsFile.h"
#include "colorManager.h"

using std::string;
using std::vector;

typedef struct 
{
    string description;
    string code;
}SingleCheck;

typedef struct 
{
    string description;
    int min;
    int max;
    string code;
}SettingsBar;

typedef struct 
{
    string description;
    vector<SettingsBar> settingsBar;
}MultipleSettingsBar;

typedef struct 
{
    string code;
    string conditionValue;
}SettingsCondition;

typedef struct
{
    string code;
    string description;
    vector<string> options;
}MultipleOptions;

typedef struct
{
    string description;
    vector<string> proportionCodes;
}ProportionIndicator; //It will be mainly used to desplay colors

typedef struct
{
    string title; //null if it's not a title
    SingleCheck *singleCheck; //null if it's not a single check
    MultipleSettingsBar *mulSettingsBar; //null if it's not a bar
    MultipleOptions *mulOptions; //null if it hasn't multiple Options
    ProportionIndicator *proportionIndicator; //null is it's not an indicator

    vector<SettingsCondition> *settingsCondition; //null if there is no condition to be displayed
}SettingsInfo;

class SettingsManager
{
private:
    WINDOW *win;
    int height;
    int width;
    int columnWidth;

    bool selected; //When the User is selecting a setting in the right side
    int startShowing;
    int selectedSetting;
    bool changingSetting; //When the User is changing a setting
    int changingNum; //What option is being change

    SettingsFile *settingsFile;
    ColorManager *colorManager;
    vector<SettingsInfo> info;

    //Conditions (Needed to be free when the program ends)
    vector<SettingsCondition> * transitionCondition;
    vector<SettingsCondition> * colorsCondition;
    vector<SettingsCondition> * firstLetterCondition;
    vector<SettingsCondition> * firstLetterTransitionCondition;

    int GetHeight(int objective);
    void ChangeSettingEnter();
    void ChangeSettingArrow(int key);
    bool CheckCondition(int index);

public:
    SettingsManager(SettingsFile * settingsFile);
    ~SettingsManager();
    void CreateSettigns(WINDOW *win, int height, int width);
    void DestroySettings();
    void ShowSettings();
    void SetSelected(bool selected); 
    bool GetSelected(); 
    void ChangeSelected(bool increase);
    void SetChangingNum(bool increase);

    //INPUTS
    void EnterInput();
    void GetInput(int input);
};

#endif
