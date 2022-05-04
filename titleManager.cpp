#include "titleManager.h"

TitleManager::TitleManager()
{
    win = nullptr;
    height = width = 0;
    active = false;
}

TitleManager::~TitleManager()
{
    DestroyTitle();
}

void TitleManager::CreateTitle(int width, int height)
{
    win = title("Neomatrix", width, height, this->width, this->height);
    if(win != nullptr)
    {
        active = true;
        wattron(win, COLOR_PAIR(3));
        for(int i = 0; i < width; i++)
            mvwprintw(win, this->height - 1, i, "▄");
        wattroff(win, COLOR_PAIR(3));
        wrefresh(win); 
    }
}

void TitleManager::DestroyTitle()
{
    if(win != nullptr)
    {
        delwin(win);
        height = width = 0;
        active = false;
    }
}

bool TitleManager::isActive()
{
    return active;
}

void TitleManager::GetDimensions(int & width, int & height)
{
    width = this->width;
    height = this->height;
}
