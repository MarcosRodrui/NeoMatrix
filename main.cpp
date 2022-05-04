#include "screenManager.h"
#include "commandManager.h"

#include <curses.h>
#include <locale.h>
#include <cstdlib>

const string version = "1.0.0";

//Nota para Windows -> Poner en Full Screen

int main(int argc, char *argv[])
{
    cmd_res commandRes;

    CommandManager commandManager(version); 
    commandRes = commandManager.CheckParameters(argc, argv);
    if(commandRes == CMD_HELP)
        return 0;

    SettingsFile *settingsFile = new SettingsFile; //SettigsManager is responsible of freeing it
    bool fileState = settingsFile->CreateSettingsFile(commandRes == CMD_RESTART);
    if(!fileState)
        return 1;
    if(commandRes == CMD_RESTART)
        return 0;

    srand((unsigned)time(0));
    //Set local settings (For special characters)
    setlocale(LC_ALL, "");

    //Initialize ncurses
    initscr();

    //Basic settigs
    raw();
    noecho(); //Doesn't show the characters that are obtain from the user
    curs_set(0); //Hides the cursor
    keypad(stdscr, TRUE);
    /* nodelay(stdscr, true); */
    timeout(10);

    ScreenManager screenManager(commandRes == CMD_EFFECT, settingsFile);

    //Main loop
    int ch;
    while(1)
    {
        ch = getch();
        if(ch == KEY_RESIZE)
            screenManager.UpdateScreen();
        else
        {
            if(screenManager.CheckInput(ch))
                break;
        }
    }

    endwin();

    return 0;
}
