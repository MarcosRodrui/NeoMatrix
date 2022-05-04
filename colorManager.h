#ifndef _COLORMANAGER_H_
#define _COLORMANAGER_H_

#include "settingsFile.h"

#include <curses.h>
#include <string>
#include <algorithm>

#define COLOR_TRANSITION 3

typedef struct{
    int r;
    int g;
    int b;
}DefaultColor;


class ColorManager
{
private:
    SettingsFile *settingsFile;

public:
    ColorManager(SettingsFile *settingsFile);
    ~ColorManager();
    void UpdateColorSettings(bool first = false);
    int GetColorPair(string foreground);
};

#endif
