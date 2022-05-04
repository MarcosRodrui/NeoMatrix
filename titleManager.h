#ifndef _TITLEMANAGER_H_
#define _TITLEMANAGER_H_

#include <curses.h>
#include "asciiart.h"

class TitleManager
{
private:
    WINDOW *win;
    int height;
    int width;
    bool active;
public:
    TitleManager();
    ~TitleManager();
    void CreateTitle(int, int);
    void DestroyTitle();
    bool isActive();
    void GetDimensions(int &, int &);
};

#endif
