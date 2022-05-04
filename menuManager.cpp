#include "menuManager.h"

MenuManager::MenuManager(InfoManager * infoManager)
{
    win = nullptr;
    height = selectedWindow = 0;
    width = fixedWidth;
    active = selected = false;
    this->infoManager = infoManager;
}

MenuManager::~MenuManager()
{
    DestroyMenu();
}

void MenuManager::GetMinimumDimensions(int & width, int & height)
{
    width = this->width; // Enough to write every configuration
    height = 18; //3 menu options * 6
}

int MenuManager::GetSelectedWindow() {return selectedWindow; };

void MenuManager::CreateMenu(int height, int startHeight)
{
    win = newwin(height, fixedWidth, startHeight, 0);
    refresh();

    if(win != nullptr)
    {        
        active = true;  
        this->height = height;

        wattron(win, COLOR_PAIR(3));
        for(int i = 0; i < height; i++)
            mvwprintw(win, i, fixedWidth - 1, "█");
        wattroff(win, COLOR_PAIR(3));
        wrefresh(win);

        vector<bool> update = {true, true, true, true};
        SetMenuOptions(update);
    }
}

void MenuManager::DestroyMenu()
{
    if(win != nullptr)
    {
        delwin(win);
        height = 0;
        active = selected = false;
    }
}

void MenuManager::UpdateMenu(bool increase)
{
    int windowBefore = selectedWindow;

    if(increase)
        selectedWindow++;
    else
        selectedWindow--;
    if(selectedWindow < 0)
        selectedWindow = 0;
    else if(selectedWindow > maxWindow)
        selectedWindow = maxWindow;

    if(selectedWindow != windowBefore)
    {
        vector<bool> update(4, 0);
        update[windowBefore] = update[selectedWindow] = true;
        SetMenuOptions(update);

        infoManager->EraseInfo();
        infoManager->ShowSelected(selectedWindow);

        wrefresh(win);
    }
}

// Private Functions
void MenuManager::SetMenuOptions(vector<bool> update)
{
    int textHeight = (height - 18) / 2;
    wattron(win, COLOR_PAIR(3));

    vector<string> options = {"START", "SETTINGS", "CREDITS"};
    for(int i = 0; i < options.size(); i++)
    {
        if(!update[i])
            continue;

        if(i == selectedWindow)
            wattron(win, A_STANDOUT);
            
        for(int j = 3; j < fixedWidth - 4; j++)
            mvwprintw(win, textHeight + i * 6, j, "━");           
        mvwprintw(win, textHeight + i * 6, 2, "┏");
        mvwprintw(win, textHeight + i * 6, fixedWidth - 4, "┓");

        mvwprintw(win, textHeight + i * 6 + 1, 2, "┃");
        mvwprintw(win, textHeight + i * 6 + 1, fixedWidth - 4, "┃");

        mvwprintw(win, textHeight + i * 6 + 2, 2, "┃");
        wattroff(win, A_STANDOUT);

        mvwprintw(win, textHeight + i * 6 + 2, 3 + (18 - options[i].length()) / 2, options[i].c_str());
        
        if(i == selectedWindow)
            wattron(win, A_STANDOUT);
        mvwprintw(win, textHeight + i * 6 + 2, fixedWidth - 4, "┃");

        mvwprintw(win, textHeight + i * 6 + 3, 2, "┃");
        mvwprintw(win, textHeight + i * 6 + 3, fixedWidth - 4, "┃");

        for(int j = 3; j < fixedWidth - 4; j++)
            mvwprintw(win, textHeight + i * 6 + 4, j, "━");           
        mvwprintw(win, textHeight + i * 6 + 4, 2, "┗");
        mvwprintw(win, textHeight + i * 6 + 4, fixedWidth - 4, "┛");
        wattroff(win, A_STANDOUT);
    }
    
    wattroff(win, COLOR_PAIR(3));

    wrefresh(win); 

}

bool MenuManager::PressingEnter()
{
    switch (selectedWindow)
    {
    case 0:
        //Starts the Effect
        return true;
    case 1:
        //Or if it is already in the right does something different (Like selecting a setting)
        if(!selected)
            selected = true;
        infoManager->SettingsInput(KEY_ENTER);
        return false;    
    case 2:
        //Opens Github page of the Project
        system("xdg-open https://github.com/MarcosRodrui/Neomatrix > /dev/null 2> /dev/null &");
        system("disown> /dev/null 2> /dev/null");

        return false;
    }
    return false;
}

void MenuManager::SpecialInput(int key)
{
    if(!selected)
    {
        if(key == KEY_UP)
            UpdateMenu(false);
        else if(key == KEY_DOWN)
            UpdateMenu(true);
    }
    else
    {
        switch (selectedWindow)
        {
        case 0:
            
            break;
        case 1:
            infoManager->SettingsInput(key);
            if(key == '\t' || key == '\b' || key == 127 || key == KEY_BACKSPACE) //ESCAPE
            {
                SettingsManager *settingsManager = infoManager->GetSettingsManager();
                selected = settingsManager->GetSelected();
            }
            break;    
        case 2:
            //Starts the Lock Mode
            break;
        case 3:
            //Maybe goes to the Github or to some social Media
            break;
        }
    }
}
