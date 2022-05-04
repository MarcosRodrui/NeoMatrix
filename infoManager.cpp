#include "infoManager.h"

InfoManager::InfoManager(SettingsFile * settingsFile, EffectController * effectController)
{
    win = startWin = nullptr;
    width = height = startWidth = startHeight = startPWidth = startPHeight = 0;
    settingsManager = new SettingsManager(settingsFile);
    this->effectController = effectController;
}

InfoManager::~InfoManager()
{
    delete settingsManager;
    if(win != nullptr)
    {
        delwin(startWin);
        delwin(win);
    }
}

void InfoManager::ShowSelected(int selectedWindow)
{
    wattrset(win, COLOR_PAIR(3));
    switch (selectedWindow)
    {
    case 0:
        ShowStart();
        break;
    case 1:
        ShowSettings();
        break;
    case 2:
        ShowCredits();
        break;
    }
}

void InfoManager::EraseInfo()
{
    wclear(win);
    effectController->ResetController();
}

void InfoManager::DestroyInfo()
{
    if(win != nullptr)
    {
        width = height = startWidth = startHeight = startPWidth = startPHeight = 0;
        delwin(startWin);
        wclear(win);
        delwin(win);
        win = startWin = nullptr;
        settingsManager->DestroySettings();
        effectController->ResetController();
    }
}

void InfoManager::CreateInfo(int selectedWindow, int width, int height, 
int startWidth, int startHeight)
{
    win = newwin(height, width, startHeight, startWidth);
    int startH = startHeight + height * 0.15;
    int startW = startWidth + width * 0.15;
    startWin = newwin(height * 0.7, width * 0.7, startH, startW);
    refresh();

    if(win != nullptr && startWin != nullptr)
    {
        this->width = width;
        this->height = height;
        this->startHeight = height * 0.7;
        this->startWidth = width * 0.7;
        this->startPWidth = width * 0.15;
        this->startPHeight = height * 0.15;
        settingsManager->CreateSettigns(win, height, width);

        ShowSelected(selectedWindow);
    }
}

void InfoManager::ShowStart()
{
    //If the message is too big for the space, it won't be display
    string message = "Pulse ENTER to start the Matrix";
    mvwprintw(win, 2, (width - message.length()) / 2, message.c_str());

    for(int i = 0; i < startHeight; i++)
    {
        mvwprintw(win, startPHeight + i, startPWidth - 1, "│");
        mvwprintw(win, startPHeight + i, startPWidth + startWidth, "│");
    }
    for(int i = 0; i < startWidth; i++)
    {
        mvwprintw(win, startPHeight - 1, startPWidth + i, "─");
        mvwprintw(win, startPHeight + startHeight, startPWidth + i, "─");
    }
    mvwprintw(win, startPHeight - 1, startPWidth - 1, "┌");
    mvwprintw(win, startPHeight - 1, startPWidth + startWidth, "┐");
    mvwprintw(win, startPHeight + startHeight, startPWidth - 1, "└");
    mvwprintw(win, startPHeight + startHeight, startPWidth + startWidth, "┘");

    wrefresh(win);

    effectController->StartController(startHeight, startWidth, startWin);
}

void InfoManager::ShowSettings()
{
    settingsManager->ShowSettings();
}

void InfoManager::ShowCredits()
{
    //If the message is too big for the space, it won't be display
    string message = "APP created by MarcosRodrui";
    mvwprintw(win, 2, (width - message.length()) / 2, message.c_str());
    
    if(height > 36 && width > 98)
    {
        int widthLimit = 98;
        int heightLimit = 34;
        int startWidth = (width - 98)/2;
        int startHeight = 2 + (height - 36)/2;
        vector<string> jake_rows = {".........//.......................................................................................",
                                    "........:/+..........................-:///:::::::::::::-..........................................",
                                    "...../+:o-+.....................-////:-----------------:/:///:-...................................",
                                    "..../:o:o-o//:...............://:-----------------------------////-...............................",
                                    ".....oo+:://::.............//:------------------------------------///-............................",
                                    ".....+---o.............../+------------------------------------------//:..........................",
                                    "....:/--/:.............-+:---------------------------------------------:+:........................",
                                    "....+---o.............:/--/oyhhhs+:--------------------::----------------:/.......................",
                                    "....+---+............//-/++:--:+hNNh:--------------/syyhdmmy+:-------------+-.....................",
                                    "....+---+...........:/-/.        -dMm/::/::/::---:::.````.+dMm+-------------+-....................",
                                    "....o---+..........-+-+`          .mho/::::::///+:         `sMN/-------------+....................",
                                    "....o---+..........+--+          -/:------------//.          mMy-------------:/...................",
                                    "....o---+.........:/--+`       `/:----ohmmmdy/----/:         mMy--------------o...................",
                                    "....o---+.........+----/.      /:----+MMMMMMMh-----+-       oMm:-----+-----/--o...................",
                                    "....o---/:--------+-----:::-.-/+-----:hdmmmdyo------+    `-yNh:------o-----o--+-..................",
                                    "::::/+:--:::::::/o:--------:/+s/-----/+:+:o::s------s/+osyhs/--------:/:::+:--+/::::::::::::::::::",
                                    ":::::/++/::::::--o-------------+:---/dyhdydyym/----:o------------------::/:---o:::::::::::::::::::",
                                    "::://///+ooo++o++s-------------://///+oyysoo++++//+/--------------------------o:::::::::::::::::::",
                                    "ooooooooo+++oooooo-------------------------------:--------------------------::yssoooo++++/+++oo+++",
                                    "ooooooooooooooooy:--------------------------------------------------------///:----------------so++",
                                    "++++++++++++++os/--------------------------------------------------------------://++++++++----yooo",
                                    "+++++++++++++so------------------:/+oooo+/--------------------------------///ysoo+++++++oo---oo+++",
                                    "+++++++++++os:-----------------//::----:://///:-----------------------------so+++++++++s+---oo++++",
                                    "++++++++++s+---------------------------------------------------------------/s+++++++++s+---oo+++++",
                                    "++++++++os:---------------------------------------------------------------:s+++++++++s+---oo++++++",
                                    "++++++++s:----------------------------------------------------------------so++++++++oo---oo+++++++",
                                    "+++++++s:----------------------------------------------------------------+o+++++++++s---+s++++++++",
                                    "++++++os----------------------------------------------------------------/s+++++++++o+---s+++++++++",
                                    "ooo+++++---------------------------------------------------------------/s++++++++++y:::+o++++++++o",
                                    "ossoo++++//::---------------------------------------------------------:s++ooooooo++ys+:ooooooossss",
                                    "+oosssso++++++//:::-----------------------------------------------:::/++++ssssssssssyssyssssssssss",
                                    "+++++osyo+++++++++++///::::----------------------------::::::://++++++ooosssssssssssssssssssssssss",
                                    "+oo+++oysssoo+++++++++++++++++++//////////////////++++++++++++++++osssssooosssssssssssssssssssssss",
                                    "ossoo++++ooooooooooo++o++++++++++++++++++++++++++++++++++++++ooossysooo++ossoossssssssssssssssssss",
        };

        for(int i = 0; i < jake_rows.size(); i++)
                mvwprintw(win, startHeight + i, startWidth, "%s", jake_rows[i].c_str());

        for(int i = 0; i < heightLimit; i++)
        {
            mvwprintw(win, startHeight + i, startWidth - 1, "│");
            mvwprintw(win, startHeight + i, startWidth + widthLimit, "│");
        }
        for(int i = 0; i < widthLimit; i++)
        {
            mvwprintw(win, startHeight - 1, startWidth + i, "─");
            mvwprintw(win, startHeight + heightLimit, startWidth + i, "─");
        }
        mvwprintw(win, startHeight - 1, startWidth - 1, "┌");
        mvwprintw(win, startHeight - 1, startWidth + widthLimit, "┐");
        mvwprintw(win, startHeight + heightLimit, startWidth - 1, "└");
        mvwprintw(win, startHeight + heightLimit, startWidth + widthLimit, "┘");

        wrefresh(win);
    }
    else if(height > 24 && width > 60)
    {
        int widthLimit = 60;
        int heightLimit = 21;
        int startWidth = (width - 60)/2;
        int startHeight = 2 + (height - 24)/2;
        vector<string> jake_rows = {".......-....................................................",
                                    ".....-//..............--:::::::::----.......................",
                                    "....////--........--::-:-----------:-:::--..................",
                                    "....+/:::-......-::---------------------:::-................",
                                    "..../-/........::-:::----------------------::-..............",
                                    "...-:-/.......::///oyho---------/+oss/-------::.............",
                                    "...:--:....../:-`    :Ns:::::::-.``./dh:------:/............",
                                    "...:--:.....::/      -/:::/:-:/.     -M+-------:-...........",
                                    "...:--:...../-:-    :--:mNMNs--:-    /N/--:---:-/...........",
                                    "---:/-::::://-----:o---:yhhs+---/..-oh/---::--/-/--------...",
                                    "::::////::-+-------::-:ysyyoy:--+://-------:::--+:::::::::::",
                                    "++++++++ooos--------:::-:/::::::---------------:s++++////+//",
                                    "oooooooooos/----------------------------------::----:::--/oo",
                                    "++++++++oo:---------::/+++/:-----------------::oooooo+s--o++",
                                    "+++++++o/------------------::-----------------/o+++++o:-o+++",
                                    "++++++o:-------------------------------------:o+++++o:-o++++",
                                    "+++++o:--------------------------------------o+++++o:-++++++",
                                    "++o+++--------------------------------------+o+++++o::o+++++",
                                    "+osooo+//::-------------------------------:/ooooooossoooosss",
                                    "++oooyoo+++++//:::::::--------:::::::://+++oosssssssssssssss",
                                    "+osoooooooooo+oo++++++++++++++++++++ooooosoooosossssssssssss"};


        for(int i = 0; i < jake_rows.size(); i++)
                mvwprintw(win, startHeight + i, startWidth, "%s", jake_rows[i].c_str());

        for(int i = 0; i < heightLimit; i++)
        {
            mvwprintw(win, startHeight + i, startWidth - 1, "│");
            mvwprintw(win, startHeight + i, startWidth + widthLimit, "│");
        }
        for(int i = 0; i < widthLimit; i++)
        {
            mvwprintw(win, startHeight - 1, startWidth + i, "─");
            mvwprintw(win, startHeight + heightLimit, startWidth + i, "─");
        }
        mvwprintw(win, startHeight - 1, startWidth - 1, "┌");
        mvwprintw(win, startHeight - 1, startWidth + widthLimit, "┐");
        mvwprintw(win, startHeight + heightLimit, startWidth - 1, "└");
        mvwprintw(win, startHeight + heightLimit, startWidth + widthLimit, "┘");

        wrefresh(win);
    }

    wrefresh(win);
}

void InfoManager::SettingsInput(int input)
{
    switch (input)
    {
        case KEY_ENTER:
            settingsManager->EnterInput();
        default:
            settingsManager->GetInput(input);
        break;
    }
}

SettingsManager * InfoManager::GetSettingsManager()
{
    return settingsManager;
}
