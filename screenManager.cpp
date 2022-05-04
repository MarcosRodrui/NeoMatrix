#include "screenManager.h"
#include <curses.h>

// Public functions
ScreenManager::ScreenManager(bool effectVar, SettingsFile *settingsFile)
{
    this->effectVar = effectVar;
    if(effectVar)
        state = MAIN;
    else
        state = MENU;

    effectController = new EffectController(settingsFile);
    infoManager = new InfoManager(settingsFile, effectController);
    titleManager = new TitleManager;
    menuManager = new MenuManager(infoManager);
    UpdateScreen();
}

ScreenManager::~ScreenManager()
{
    delete effectController;
    delete infoManager;
    delete titleManager;
    delete menuManager;
}

void ScreenManager::UpdateScreen()
{
    //Gets the terminal dimensiones and resizes if its possible
    int width, height;

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    width = w.ws_col; height = w.ws_row;
    resize_term(height, width);
    clear();

    switch(state)
    {
        case MENU:
            CreateMenu(width, height);
            break;
        case MAIN:
        {
            effectController->ResetController();
            CreateStart();
        }
    }
}

bool ScreenManager::CheckInput(int input)
{
    if(input == 3) //Ctrl + C
    {
        if(state == MENU || effectVar)
            return true;
        else if(state == MAIN)
        {
            state = MENU;
            effectController->ResetController();
            clear();
            refresh();
            UpdateScreen(); 
            return false;
        }
    }

    int selectedWindow = menuManager->GetSelectedWindow();
    if(state == MAIN)
        effectController->Update();
    else if(state == MENU && selectedWindow == 0)
        effectController->Update();

    if(input == ERR || state != MENU)
        return false;

    switch (input)
    {
    case KEY_DOWN:
    case KEY_UP:
    case KEY_RIGHT:
    case KEY_LEFT:
    case 562: //Ctrl + Right Arrow
    case 547: //Ctrl + Left Arrow
    case KEY_BACKSPACE:
    case 127:
    case '\b':
    case '\t':
        menuManager->SpecialInput(input);
        break;
    case 10: //ENTER
        {
            bool result = menuManager->PressingEnter();
            if(result)
            {
                DestroyMenu();
                if(menuManager->GetSelectedWindow() == 0)
                {
                    state = MAIN;
                    CreateStart();
                }
            }
            break;
        }
    }
    return false;
}

//Private Functions
void ScreenManager::CreateMenu(int width, int height)
{
    titleManager->DestroyTitle();
    menuManager->DestroyMenu();
    infoManager->DestroyInfo();


    int totalWidth = width;
    int totalHeight = height;

    //TITLE
    titleManager->CreateTitle(width, height);
    if(!titleManager->isActive()) //If there is no space
        return;

    int titleWidth, titleHeight;
    titleManager->GetDimensions(titleWidth, titleHeight);
    height -= titleHeight;

    //MENU
    int minMenuWidth, minMenuHeight;
    menuManager->GetMinimumDimensions(minMenuWidth, minMenuHeight);

    if(width < minMenuWidth || height < minMenuHeight) //No space left for the menu
        return;
    
    menuManager->CreateMenu(height, titleHeight);

    //INFO
    width -= minMenuWidth;

    //Kind of an arbitrary number
    //Height is not checked (If the menu can be printed, Info can be pritned as well)
    if(width < 30)
        return;

    int selectedWindow = menuManager->GetSelectedWindow();
    infoManager->CreateInfo(selectedWindow, width, height, minMenuWidth, titleHeight);
}

void ScreenManager::DestroyMenu()
{
    //TITLE
    titleManager->DestroyTitle();

    //MENU
    menuManager->DestroyMenu();

    //INFO
    infoManager->DestroyInfo();
    clear();
    refresh();
}

void ScreenManager::CreateStart()
{
    int height, width;
    getmaxyx(stdscr, height, width);
    effectController->StartController(height, width);
}
