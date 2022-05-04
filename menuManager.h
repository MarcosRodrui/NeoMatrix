#ifndef _MENUMANAGER_H_
#define _MENUMANAGER_H_

#include "infoManager.h"

#include <cstdlib>
#include <curses.h>
#include <string>
#include <vector>

using std::vector;
using std::string;

const int maxWindow = 2;
const int fixedWidth = 24; //Menu has fixed width

class MenuManager
{
private:
    InfoManager *infoManager;

    WINDOW *win;
    int height;
    int width;
    bool active;

    int selectedWindow;
    bool selected; //if TRUE the User is in the right side

    void SetMenuOptions(vector<bool> update);

public:
    MenuManager(InfoManager * infoManager);
    ~MenuManager();
    void GetMinimumDimensions(int &, int &);
    int GetSelectedWindow();
    void CreateMenu(int height, int startHeight);
    void DestroyMenu();
    void UpdateMenu(bool increase);
    bool PressingEnter(); //returns true when matrix/locked has been activated
    void SpecialInput(int key);
};

#endif
