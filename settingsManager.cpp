#include "settingsManager.h"
#include <curses.h>
#include <vector>

SettingsManager::SettingsManager(SettingsFile * settingsFile)
{
    win = nullptr;
    height = width = startShowing = changingNum = 0;
    selectedSetting = 1;
    changingSetting = selected = false;

    //General Settings
    info.push_back(SettingsInfo{"General Settings", nullptr, nullptr, nullptr, nullptr});

    vector<SettingsBar> densitySettings;
    densitySettings.push_back(SettingsBar{"", 1, 100, "letter-density"});
    info.push_back(SettingsInfo{"", nullptr,
     new MultipleSettingsBar{"Letter Density", densitySettings}, nullptr, nullptr});

    vector<SettingsBar> trailSizeSettings;
    trailSizeSettings.push_back(SettingsBar{"Min", 1, 100, "min-trail-size"});
    trailSizeSettings.push_back(SettingsBar{"Max", 1, 100, "max-trail-size"});
    info.push_back(SettingsInfo{"", nullptr,
     new MultipleSettingsBar{"Trail Size", trailSizeSettings}, nullptr, nullptr});

    vector<SettingsBar> fallingSpeedSettings;
    fallingSpeedSettings.push_back(SettingsBar{"Min", 1, 100, "min-falling-speed"});
    fallingSpeedSettings.push_back(SettingsBar{"Max", 1, 100, "max-falling-speed"});
    info.push_back(SettingsInfo{"", nullptr,
     new MultipleSettingsBar{"Falling Speed", fallingSpeedSettings}, nullptr, nullptr});

    vector<SettingsBar> changeLetterSettings;
    changeLetterSettings.push_back(SettingsBar{"Min", 0, 100, "min-change-letter"});
    changeLetterSettings.push_back(SettingsBar{"Max", 0, 100, "max-change-letter"});
    info.push_back(SettingsInfo{"", nullptr,
     new MultipleSettingsBar{"Change Letter Speed", changeLetterSettings}, nullptr, nullptr});

    transitionCondition = new vector<SettingsCondition>;
    transitionCondition->push_back({"terminal-colors", "0"});

    firstLetterTransitionCondition = new vector<SettingsCondition>;
    firstLetterTransitionCondition->push_back({"terminal-colors", "0"});
    firstLetterTransitionCondition->push_back({"first-letter", "1"});

    info.push_back(SettingsInfo{"", new SingleCheck{"First Letters Transition",
     "first-letter-transition"}, nullptr, nullptr, nullptr, firstLetterTransitionCondition});
    info.push_back(SettingsInfo{"", new SingleCheck{"Last Letters Transition",
     "last-letter-transition"}, nullptr, nullptr, nullptr, transitionCondition});


    //Color Settings:
    info.push_back(SettingsInfo{"Color Settings", nullptr, nullptr, nullptr, nullptr});
    
    if(can_change_color() == TRUE)
    {
        info.push_back(SettingsInfo{"", new SingleCheck{"Use Terminal Colors",
            "terminal-colors"}, nullptr, nullptr, nullptr, nullptr});
    }
    else
        settingsFile->ChangeSettingsValue("terminal-colors", "1"); //Because it's not supported

    colorsCondition = new vector<SettingsCondition>; 
    colorsCondition->push_back({"terminal-colors", "0"});

    vector<SettingsBar> blackSettings;
    blackSettings.push_back(SettingsBar{"Red", 0, 255, "black-color-r"});
    blackSettings.push_back(SettingsBar{"Green", 0, 255, "black-color-g"});
    blackSettings.push_back(SettingsBar{"Blue", 0, 255, "black-color-b"});
    info.push_back(SettingsInfo{"", nullptr,
     new MultipleSettingsBar{"Black", blackSettings}, nullptr, nullptr, colorsCondition});

    vector<SettingsBar> redSettings;
    redSettings.push_back(SettingsBar{"Red", 0, 255, "red-color-r"});
    redSettings.push_back(SettingsBar{"Green", 0, 255, "red-color-g"});
    redSettings.push_back(SettingsBar{"Blue", 0, 255, "red-color-b"});
    info.push_back(SettingsInfo{"", nullptr,
     new MultipleSettingsBar{"Red", redSettings}, nullptr, nullptr, colorsCondition});

    vector<SettingsBar> greenSettings;
    greenSettings.push_back(SettingsBar{"Red", 0, 255, "green-color-r"});
    greenSettings.push_back(SettingsBar{"Green", 0, 255, "green-color-g"});
    greenSettings.push_back(SettingsBar{"Blue", 0, 255, "green-color-b"});
    info.push_back(SettingsInfo{"", nullptr,
     new MultipleSettingsBar{"Green", greenSettings}, nullptr, nullptr, colorsCondition});

    vector<SettingsBar> yellowSettings;
    yellowSettings.push_back(SettingsBar{"Red", 0, 255, "yellow-color-r"});
    yellowSettings.push_back(SettingsBar{"Green", 0, 255, "yellow-color-g"});
    yellowSettings.push_back(SettingsBar{"Blue", 0, 255, "yellow-color-b"});
    info.push_back(SettingsInfo{"", nullptr,
     new MultipleSettingsBar{"Yellow", yellowSettings}, nullptr, nullptr, colorsCondition});

    vector<SettingsBar> blueSettings;
    blueSettings.push_back(SettingsBar{"Red", 0, 255, "blue-color-r"});
    blueSettings.push_back(SettingsBar{"Green", 0, 255, "blue-color-g"});
    blueSettings.push_back(SettingsBar{"Blue", 0, 255, "blue-color-b"});
    info.push_back(SettingsInfo{"", nullptr,
     new MultipleSettingsBar{"Blue", blueSettings}, nullptr, nullptr, colorsCondition});

    vector<SettingsBar> magentaSettings;
    magentaSettings.push_back(SettingsBar{"Red", 0, 255, "magenta-color-r"});
    magentaSettings.push_back(SettingsBar{"Green", 0, 255, "magenta-color-g"});
    magentaSettings.push_back(SettingsBar{"Blue", 0, 255, "magenta-color-b"});
    info.push_back(SettingsInfo{"", nullptr,
     new MultipleSettingsBar{"Magenta", magentaSettings}, nullptr, nullptr, colorsCondition});

    vector<SettingsBar> cyanSettings;
    cyanSettings.push_back(SettingsBar{"Red", 0, 255, "cyan-color-r"});
    cyanSettings.push_back(SettingsBar{"Green", 0, 255, "cyan-color-g"});
    cyanSettings.push_back(SettingsBar{"Blue", 0, 255, "cyan-color-b"});
    info.push_back(SettingsInfo{"", nullptr,
     new MultipleSettingsBar{"Cyan", cyanSettings}, nullptr, nullptr, colorsCondition});

    vector<SettingsBar> whiteSettings;
    whiteSettings.push_back(SettingsBar{"Red", 0, 255, "white-color-r"});
    whiteSettings.push_back(SettingsBar{"Green", 0, 255, "white-color-g"});
    whiteSettings.push_back(SettingsBar{"Blue", 0, 255, "white-color-b"});
    info.push_back(SettingsInfo{"", nullptr,
     new MultipleSettingsBar{"White", whiteSettings}, nullptr, nullptr, colorsCondition});

    info.push_back(SettingsInfo{"", nullptr, nullptr, nullptr, 
            new ProportionIndicator{"Colors Proportion", vector<string> {"black-proportion", "red-proportion",
            "green-proportion", "yellow-proportion", "blue-proportion", "magenta-proportion", "cyan-proportion",
            "white-proportion"}}, nullptr});

    vector<SettingsBar> blackProportion;
    blackProportion.push_back(SettingsBar{"", 0, 100, "black-proportion"});
    info.push_back(SettingsInfo{"", nullptr,
     new MultipleSettingsBar{"Black Proportion", blackProportion}, nullptr, nullptr, nullptr});
 
    vector<SettingsBar> redProportion;
    redProportion.push_back(SettingsBar{"", 0, 100, "red-proportion"});
    info.push_back(SettingsInfo{"", nullptr,
     new MultipleSettingsBar{"Red Proportion", redProportion}, nullptr, nullptr, nullptr});
  
    vector<SettingsBar> greenProportion;
    greenProportion.push_back(SettingsBar{"", 0, 100, "green-proportion"});
    info.push_back(SettingsInfo{"", nullptr,
     new MultipleSettingsBar{"Green Proportion", greenProportion}, nullptr, nullptr, nullptr});
  
    vector<SettingsBar> yellowProportion;
    yellowProportion.push_back(SettingsBar{"", 0, 100, "yellow-proportion"});
    info.push_back(SettingsInfo{"", nullptr,
     new MultipleSettingsBar{"Yellow Proportion", yellowProportion}, nullptr, nullptr, nullptr});
  
    vector<SettingsBar> blueProportion;
    blueProportion.push_back(SettingsBar{"", 0, 100, "blue-proportion"});
    info.push_back(SettingsInfo{"", nullptr,
     new MultipleSettingsBar{"Blue Proportion", blueProportion}, nullptr, nullptr, nullptr});
  
    vector<SettingsBar> magentaProportion;
    magentaProportion.push_back(SettingsBar{"", 0, 100, "magenta-proportion"});
    info.push_back(SettingsInfo{"", nullptr,
     new MultipleSettingsBar{"Magenta Proportion", magentaProportion}, nullptr, nullptr, nullptr});
  
    vector<SettingsBar> cyanProportion;
    cyanProportion.push_back(SettingsBar{"", 0, 100, "cyan-proportion"});
    info.push_back(SettingsInfo{"", nullptr,
     new MultipleSettingsBar{"Cyan Proportion", cyanProportion}, nullptr, nullptr, nullptr});
  
    vector<SettingsBar> whiteProportion;
    whiteProportion.push_back(SettingsBar{"", 0, 100, "white-proportion"});
    info.push_back(SettingsInfo{"", nullptr,
     new MultipleSettingsBar{"White Proportion", whiteProportion}, nullptr, nullptr, nullptr});

    info.push_back(SettingsInfo{"", new SingleCheck{"Unique Color per Group",
     "unique-color-group"}, nullptr, nullptr, nullptr, nullptr});

    info.push_back(SettingsInfo{"", nullptr, nullptr, new MultipleOptions{"background-color", "Background Color",
        vector<string> {"Default", "Black", "Red", "Green", "Yellow", "Blue", "Magenta", "Cyan", "White"}}, nullptr, nullptr});
 
    info.push_back(SettingsInfo{"", new SingleCheck{"First Letter Unique",
     "first-letter"}, nullptr, nullptr, nullptr, nullptr});

    firstLetterCondition = new vector<SettingsCondition>;
    firstLetterCondition->push_back({"first-letter", "1"});

    info.push_back(SettingsInfo{"", nullptr, nullptr, nullptr, 
            new ProportionIndicator{"First Letter Proportion", vector<string> {"first-letter-black-proportion", "first-letter-red-proportion",
            "first-letter-green-proportion", "first-letter-yellow-proportion", "first-letter-blue-proportion", "first-letter-magenta-proportion",
            "first-letter-cyan-proportion", "first-letter-white-proportion"}}, firstLetterCondition});

    vector<SettingsBar> firstLetterBlackProportion;
    firstLetterBlackProportion.push_back(SettingsBar{"", 0, 100, "first-letter-black-proportion"});
    info.push_back(SettingsInfo{"", nullptr,
     new MultipleSettingsBar{"Black Proportion", firstLetterBlackProportion}, nullptr, nullptr, firstLetterCondition});
 
    vector<SettingsBar> firstLetterRedProportion;
    firstLetterRedProportion.push_back(SettingsBar{"", 0, 100, "first-letter-red-proportion"});
    info.push_back(SettingsInfo{"", nullptr,
     new MultipleSettingsBar{"Red Proportion", firstLetterRedProportion}, nullptr, nullptr, firstLetterCondition});
  
    vector<SettingsBar> firstLetterGreenProportion;
    firstLetterGreenProportion.push_back(SettingsBar{"", 0, 100, "first-letter-green-proportion"});
    info.push_back(SettingsInfo{"", nullptr,
     new MultipleSettingsBar{"Green Proportion", firstLetterGreenProportion}, nullptr, nullptr, firstLetterCondition});
  
    vector<SettingsBar> firstLetterYellowProportion;
    firstLetterYellowProportion.push_back(SettingsBar{"", 0, 100, "first-letter-yellow-proportion"});
    info.push_back(SettingsInfo{"", nullptr,
     new MultipleSettingsBar{"Yellow Proportion", firstLetterYellowProportion}, nullptr, nullptr, firstLetterCondition});
  
    vector<SettingsBar> firstLetterBlueProportion;
    firstLetterBlueProportion.push_back(SettingsBar{"", 0, 100, "first-letter-blue-proportion"});
    info.push_back(SettingsInfo{"", nullptr,
     new MultipleSettingsBar{"Blue Proportion", firstLetterBlueProportion}, nullptr, nullptr, firstLetterCondition});
  
    vector<SettingsBar> firstLetterMagentaProportion;
    firstLetterMagentaProportion.push_back(SettingsBar{"", 0, 100, "first-letter-magenta-proportion"});
    info.push_back(SettingsInfo{"", nullptr,
     new MultipleSettingsBar{"Magenta Proportion", firstLetterMagentaProportion}, nullptr, nullptr, firstLetterCondition});
  
    vector<SettingsBar> firstLetterCyanProportion;
    firstLetterCyanProportion.push_back(SettingsBar{"", 0, 100, "first-letter-cyan-proportion"});
    info.push_back(SettingsInfo{"", nullptr,
     new MultipleSettingsBar{"Cyan Proportion", firstLetterCyanProportion}, nullptr, nullptr, firstLetterCondition});
  
    vector<SettingsBar> firstLetterWhiteProportion;
    firstLetterWhiteProportion.push_back(SettingsBar{"", 0, 100, "first-letter-white-proportion"});
    info.push_back(SettingsInfo{"", nullptr,
     new MultipleSettingsBar{"White Proportion", firstLetterWhiteProportion}, nullptr, nullptr, firstLetterCondition});


    //Character Settings
    info.push_back(SettingsInfo{"Character Settings", nullptr, nullptr, nullptr, nullptr});

    info.push_back(SettingsInfo{"", new SingleCheck{"Basic Latin",
     "basic-latin"}, nullptr, nullptr, nullptr, nullptr});
    info.push_back(SettingsInfo{"", new SingleCheck{"Latin-1 Latin",
     "latin-1-supplement"}, nullptr, nullptr, nullptr, nullptr});
    info.push_back(SettingsInfo{"", new SingleCheck{"Armenian",
     "armenian"}, nullptr, nullptr, nullptr, nullptr});
    info.push_back(SettingsInfo{"", new SingleCheck{"Hebrew",
     "hebrew"}, nullptr, nullptr, nullptr, nullptr});
    info.push_back(SettingsInfo{"", new SingleCheck{"Nko",
     "nko"}, nullptr, nullptr, nullptr, nullptr});
    info.push_back(SettingsInfo{"", new SingleCheck{"Mandaic",
     "mandaic"}, nullptr, nullptr, nullptr, nullptr});
    info.push_back(SettingsInfo{"", new SingleCheck{"Devanagari",
     "devanagari"}, nullptr, nullptr, nullptr, nullptr});
    info.push_back(SettingsInfo{"", new SingleCheck{"Thai",
     "thai"}, nullptr, nullptr, nullptr, nullptr});
    info.push_back(SettingsInfo{"", new SingleCheck{"Runic",
     "runic"}, nullptr, nullptr, nullptr, nullptr});
    info.push_back(SettingsInfo{"", new SingleCheck{"Hanunoo",
     "hanunoo"}, nullptr, nullptr, nullptr, nullptr});
    info.push_back(SettingsInfo{"", new SingleCheck{"Buhind",
     "buhind"}, nullptr, nullptr, nullptr, nullptr});
    info.push_back(SettingsInfo{"", new SingleCheck{"Limbu",
     "limbu"}, nullptr, nullptr, nullptr, nullptr});
    info.push_back(SettingsInfo{"", new SingleCheck{"Khmer",
     "khmer"}, nullptr, nullptr, nullptr, nullptr});
    info.push_back(SettingsInfo{"", new SingleCheck{"Ol Chiki",
     "ol_chiki"}, nullptr, nullptr, nullptr, nullptr});
    info.push_back(SettingsInfo{"", new SingleCheck{"Tifinagh",
     "tifinagh"}, nullptr, nullptr, nullptr, nullptr});
    info.push_back(SettingsInfo{"", new SingleCheck{"Myanmar",
     "myanmar"}, nullptr, nullptr, nullptr, nullptr});
    info.push_back(SettingsInfo{"", new SingleCheck{"Katakana",
     "katakana"}, nullptr, nullptr, nullptr, nullptr});

    this->settingsFile = settingsFile;

    colorManager = new ColorManager(settingsFile);
}

SettingsManager::~SettingsManager()
{
    delete settingsFile; 
    delete colorManager;

    //Free all the dynamic memory inside info
    for(int i = 0; i < info.size(); i++)
    {
        if(info[i].singleCheck != nullptr)
            delete info[i].singleCheck;
        else if(info[i].mulSettingsBar != nullptr)
            delete info[i].mulSettingsBar;
        else if(info[i].mulOptions != nullptr)
            delete info[i].mulOptions;
        else if(info[i].proportionIndicator != nullptr)
            delete info[i].proportionIndicator;
    }
    delete transitionCondition;
    delete colorsCondition;
    delete firstLetterCondition;
    delete firstLetterTransitionCondition;
}

void SettingsManager::CreateSettigns(WINDOW *win, int height, int width)
{
    this->win = win;
    this->width = width;
    columnWidth = width * 0.25;
    if(columnWidth < 20)
        columnWidth = 20;
    this->height = height;
}
    
void SettingsManager::DestroySettings()
{
    win = nullptr;
    height = width = changingNum = 0;
    changingSetting = selected = false;
}

void SettingsManager::ShowSettings()
{
    if(win != nullptr)
    {
        int totalHeight = 0;

        if(info.size() > 0 && info[startShowing].title == "")
            totalHeight = 1;

        for(int i = startShowing; i < info.size(); i++)
        {
            if(info[i].settingsCondition != nullptr)
            {
                bool valid = CheckCondition(i);

                if(!valid)
                    continue;
            }
            if(info[i].title != "")
            {
                if(totalHeight + 3 <= height)
                {
                    mvwprintw(win, totalHeight + 1, (width - info[i].title.length()) / 2,
                     info[i].title.c_str());
                     for(int j = 0; j < width; j++)
                        mvwprintw(win, totalHeight + 2, j, "═");
                    totalHeight += 3;
                }
                else
                    break;
            }
            else if(info[i].singleCheck != nullptr)
            {
                if(totalHeight + 2 <= height)
                {
                    if(selected && i == selectedSetting)
                        wattron(win, A_STANDOUT);
                    mvwprintw(win, totalHeight, 
                    (columnWidth - info[i].singleCheck->description.length()) / 2,
                     info[i].singleCheck->description.c_str());
                    wattroff(win, A_STANDOUT);
                    
                    mvwprintw(win, totalHeight, columnWidth, "│");
                    if(i > 0 && info[i - 1].title != "")
                        mvwprintw(win, totalHeight - 1, columnWidth, "╤");
                    else if (i > 0)
                        mvwprintw(win, totalHeight - 1, columnWidth, "┼");

                    if(selected && i == selectedSetting && changingSetting)
                        wattron(win, A_STANDOUT);
                    if(settingsFile->GetSettingsData(info[i].singleCheck->code) == "0")
                        mvwprintw(win, totalHeight, columnWidth + (width - columnWidth) / 2, ".");
                    else
                        mvwprintw(win, totalHeight, columnWidth + (width - columnWidth) / 2, "+");
                    wattroff(win, A_STANDOUT);

                    for(int j = 0; j < width; j++)
                       mvwprintw(win, totalHeight + 1, j, "─");
                    mvwprintw(win, totalHeight + 1, columnWidth, "┴");


                    totalHeight += 2;
                }
                else
                    break;
            }
            else if(info[i].mulSettingsBar != nullptr)
            {
                int num = info[i].mulSettingsBar->settingsBar.size();
                if(totalHeight + num + 1 <= height)
                {
                    for(int j = 0; j < num; j++)
                    {
                        if(j == num / 2)
                        {   
                            if(selected && i == selectedSetting)
                                wattron(win, A_STANDOUT);
                            mvwprintw(win, totalHeight + j, 2,
                                "%s", info[i].mulSettingsBar->description.c_str());
                            wattroff(win, A_STANDOUT);

                            //Special Setting for Color:
                            string description = info[i].mulSettingsBar->description;
                            description = description.substr(0, description.find(" "));
                            int color = colorManager->GetColorPair(description);
                            if(color != -1)
                            {
                                wattron(win, COLOR_PAIR(color));
                                mvwprintw(win, totalHeight + j, 2 + info[i].mulSettingsBar->description.length(),
                                    " ██");
                                wattrset(win, COLOR_PAIR(3));
                            }
                        }
                        
                        mvwprintw(win, totalHeight + j, 
                            columnWidth - info[i].mulSettingsBar->settingsBar[j].description.length() - 2,
                            "%s  ", info[i].mulSettingsBar->settingsBar[j].description.c_str());
                        
                        if(j == 0)
                        {
                            if(i > 0 && info[i - 1].title != "")
                                mvwprintw(win, totalHeight - 1, columnWidth, "╤");
                            else if(i > 0)
                                mvwprintw(win, totalHeight - 1, columnWidth, "┼");
                        }
                        mvwprintw(win, totalHeight + j, columnWidth, "│");

                        int value = stoi(settingsFile->GetSettingsData(
                            info[i].mulSettingsBar->settingsBar[j].code));

                        if(selected && i == selectedSetting && changingSetting && 
                            j == changingNum)
                            wattron(win, A_STANDOUT);
                        if(info[i].mulSettingsBar->settingsBar[j].max >= 100)
                            mvwprintw(win, totalHeight + j, columnWidth + 1, "%3d", value);
                        else if(info[i].mulSettingsBar->settingsBar[j].max >= 10)
                            mvwprintw(win, totalHeight + j, columnWidth + 1, "%2d", value);
                        else
                            mvwprintw(win, totalHeight + j, columnWidth + 1, "%1d", value);
                        wattroff(win, A_STANDOUT);

                        mvwprintw(win, totalHeight + j, columnWidth + 4, "[");

                        int max = (width - columnWidth - 5);
                        for(int k = 1; k <= max; k++)
                        {
                            if(k / (float)max > 
                                value / (float)info[i].mulSettingsBar->settingsBar[j].max)
                                mvwprintw(win, totalHeight + j, columnWidth + 4 + k, "·");
                            else
                                mvwprintw(win, totalHeight + j, columnWidth + 4 + k, "#");
                        }
                        mvwprintw(win, totalHeight + j, width - 1, "]");
                    }

                    for(int j = 0; j < width; j++)
                       mvwprintw(win, totalHeight + num, j, "─");
                    mvwprintw(win, totalHeight + num, columnWidth, "┴");

                    totalHeight += num + 1;
                }
                else
                    break;
            }
            else if(info[i].mulOptions != nullptr)
            {
                int num = info[i].mulOptions->options.size();
                if(totalHeight + num + 1 <= height)
                {
                    for(int j = 0; j < num; j++)
                    {
                        if(j == num / 2)
                        {   
                            if(selected && i == selectedSetting)
                                wattron(win, A_STANDOUT);
                            mvwprintw(win, totalHeight + j, 2,
                                "%s", info[i].mulOptions->description.c_str());
                            wattroff(win, A_STANDOUT);
                        }

                        if(selected && i == selectedSetting && changingSetting && 
                            j == changingNum)
                            wattron(win, A_STANDOUT);
                        
                        string value = settingsFile->GetSettingsData(
                            info[i].mulOptions->code); 
                        if(value == info[i].mulOptions->options[j])
                            mvwprintw(win, totalHeight + j, columnWidth + 2, "%s", "+");
                        else
                            mvwprintw(win, totalHeight + j, columnWidth + 2, "%s", "·");

                        mvwprintw(win, totalHeight + j, 
                            columnWidth + 4,
                            "%s  ", info[i].mulOptions->options[j].c_str());
                        wattroff(win, A_STANDOUT);
                        
                        if(j == 0)
                        {
                            if(i > 0 && info[i - 1].title != "")
                                mvwprintw(win, totalHeight - 1, columnWidth, "╤");
                            else if(i > 0)
                                mvwprintw(win, totalHeight - 1, columnWidth, "┼");
                        }
                        mvwprintw(win, totalHeight + j, columnWidth, "│");

                   }

                    for(int j = 0; j < width; j++)
                       mvwprintw(win, totalHeight + num, j, "─");
                    mvwprintw(win, totalHeight + num, columnWidth, "┴");

                    totalHeight += num + 1;
                }
                else
                    break;
            }
            else if(info[i].proportionIndicator != nullptr)
            {
                int num = 1;
                if(totalHeight + num + 1 <= height)
                {
                    if(i > 0 && info[i - 1].title != "")
                        mvwprintw(win, totalHeight - 1, columnWidth, "╤");
                    else if(i > 0)
                        mvwprintw(win, totalHeight - 1, columnWidth, "┼");

                    //It represents the different proportions with colors  
                    vector<int> proportions;
                    int total = 0;
                    for(int j = 0; j < info[i].proportionIndicator->proportionCodes.size(); j++)
                    {
                        int num =  stoi(settingsFile->GetSettingsData(info[i].proportionIndicator->proportionCodes[j]));
                        total += num;
                        proportions.push_back(num);
                    }

                    if(total == 0)
                    {
                        total = info[i].proportionIndicator->proportionCodes.size();
                        for(int j = 0; j < total; j++)
                            proportions[j] = 1;
                    }

                    mvwprintw(win, totalHeight, 2, "%s", info[i].proportionIndicator->description.c_str());

                    int totalWidth = width - columnWidth;
                    int token = 0;

                    vector<int> addProportion;
                    int countFloor = 0;
                    for(int j = 0; j < proportions.size(); j++)
                    {
                        addProportion.push_back(totalWidth * (proportions[j] / (double)total));
                        countFloor += addProportion[j];
                    }

                    int fixLost = totalWidth - countFloor;
                    for(int j = 0; j < fixLost; j++)
                    {
                        int index = proportions.size() - j - 1;
                        if(proportions[index] > 0 && addProportion[index] == 0)
                        {
                            addProportion[index]++;
                            countFloor++;
                        }
                    }
                    fixLost = totalWidth - countFloor;
                    while(fixLost > 0) 
                    {
                        fixLost = totalWidth - countFloor;
                        vector<std::pair<int, int>> data;
                        for(int j = 0; j < proportions.size(); j++) 
                            data.push_back(std::pair<int, int> (proportions[j], j));
                        std::sort(data.begin(), data.end());

                        for(int j = 0; j < proportions.size() && fixLost > 0; j++)
                        {
                            if(proportions[data[j].second])
                            {
                                addProportion[data[j].second]++;
                                countFloor++;
                            }
                            fixLost = totalWidth - countFloor;
                        }
                    }

                    for(int j = 0; j < proportions.size(); j++)
                    {
                        for(int k = 0; k < addProportion[j]; k++) 
                        {
                            wattron(win, COLOR_PAIR(j + 1));
                            mvwprintw(win, totalHeight, columnWidth + token + k, "█");
                            wattroff(win, COLOR_PAIR(j + 1));
                        }
                        token += addProportion[j];
                    }
                    wattron(win, COLOR_PAIR(3));

                    mvwprintw(win, totalHeight, columnWidth, "│");
                    for(int j = 0; j < width; j++)
                       mvwprintw(win, totalHeight + num, j, "─");
                    mvwprintw(win, totalHeight + num, columnWidth, "┴");

                    totalHeight += num + 1;
                }
                else
                    break;
            }
        }
        if(info.size() > 0 && info[startShowing].title == "")
            mvwprintw(win, 0, columnWidth, "│");

    }
    wrefresh(win);
}

void SettingsManager::SetSelected(bool selected)
{
    this->selected = selected;
} 


bool SettingsManager::GetSelected()
{
    return selected;
}

void SettingsManager::ChangeSelected(bool increase)
{
    bool update = false;
    int selectedBefore = selectedSetting, showingBefore = startShowing;

    do
    {
        if(increase)
            selectedSetting--;
        else
            selectedSetting++;
        if(selectedSetting < 0)
        {
            selectedSetting = 0;
            if(!CheckCondition(selectedSetting))
                selectedSetting = selectedBefore;
            break;
        }
        if(selectedSetting >= info.size())
        {
            selectedSetting = info.size() - 1;
            if(!CheckCondition(selectedSetting))
                selectedSetting = selectedBefore;
            break;
        }
        if(info[selectedSetting].title != "" || 
            info[selectedSetting].proportionIndicator != nullptr)
        {
            if(increase)
            {
                if(selectedSetting != 0)
                    selectedSetting--;
                else
                {
                    startShowing = 0;
                    selectedSetting = selectedBefore;
                    update = true;
                }
            }
            else
            {
                if(selectedSetting != info.size() - 1)
                    selectedSetting++;
                else
                    selectedSetting = selectedBefore;
            }
        }
    }
    while(!CheckCondition(selectedSetting));

    if(selectedSetting != selectedBefore || update)
    {
        if(selectedSetting < startShowing)
        {
            startShowing = selectedSetting;
            if(startShowing > 0 && info[startShowing - 1].title != "")
                startShowing--;
        }
        else if(selectedSetting != selectedBefore)
        {
            int checkHeight = GetHeight(selectedSetting);
            while (checkHeight > height)
            {
                startShowing++;
                checkHeight = GetHeight(selectedSetting);  
            }
        }
	if(startShowing != showingBefore)
		wclear(win);
        ShowSettings();
    }
}

void SettingsManager::SetChangingNum(bool increase)
{   
    int max = 1;
    if(info[selectedSetting].mulSettingsBar != nullptr)
        max = info[selectedSetting].mulSettingsBar->settingsBar.size();
    if(info[selectedSetting].mulOptions != nullptr)
        max = info[selectedSetting].mulOptions->options.size();
    
    int changingBefore = changingNum;
    if(increase)
        changingNum--;
    else
        changingNum++;
    if(changingNum < 0)
        changingNum = 0;
    if(changingNum >= max)
        changingNum = max - 1;

    if(changingNum != changingBefore)
    {
        //wclear(win);
        ShowSettings();
    }
}

void SettingsManager::EnterInput()
{
    if(!selected)
    {
        selected = true;
        //wclear(win);
        ShowSettings();
    }
    else if(!changingSetting)
    {
        changingSetting = true;
        changingNum = 0;
        //wclear(win);
        ShowSettings();
    }
    else
        ChangeSettingEnter();
}

void SettingsManager::GetInput(int input)
{
    switch (input)
    {
    case KEY_UP:
        if(!changingSetting)
            ChangeSelected(true);
        else
            SetChangingNum(true);
        break;
    case KEY_DOWN:
        if(!changingSetting)
            ChangeSelected(false);
        else
            SetChangingNum(false);
        break;
    case KEY_LEFT:
    case KEY_RIGHT:
    case 562: //Ctrl + Right Arrow
    case 547: //Ctrl + Left Arrow
        ChangeSettingArrow(input);
        break;
    case KEY_BACKSPACE: //ESCAPE
    case 127:
    case '\b':
    case '\t':
        if(!changingSetting)
        {
            selected = false;
            //wclear(win);
            ShowSettings();
        }
        else
        {
            changingSetting = false;
            changingNum = 0;
            //wclear(win);
            ShowSettings();
        }
        break;
    }
}

//PRIVATE FUNCTIONS
int SettingsManager::GetHeight(int objective)
{
    int total = 0;
    if(info.size() > 0 && info[startShowing].title == "")
        total++;

    for(int i = startShowing; i < info.size() && i <= objective; i++)
    {
        if(!CheckCondition(i))
            continue;
        if(info[i].title != "")
            total += 3;
        else if(info[i].singleCheck != nullptr)
            total += 2;
        else if(info[i].mulSettingsBar != nullptr)
        {
            int num = info[i].mulSettingsBar->settingsBar.size();
            total += num + 1;
        }
        else if(info[i].mulOptions != nullptr)
        {
            int num = info[i].mulOptions->options.size();
            total += num + 1;
        }
        else if(info[i].proportionIndicator != nullptr)
        {
            total += 2;
        }

    }
    return total;
}

void SettingsManager::ChangeSettingEnter()
{
    if(info[selectedSetting].singleCheck != nullptr)
    {
        string code = info[selectedSetting].singleCheck->code;
        string value = settingsFile->GetSettingsData(code);
        string newValue = value == "0" ? "1" : "0";
        settingsFile->ChangeSettingsValue(code, newValue);
        if(code == "terminal-colors")
            colorManager->UpdateColorSettings(true);
        wclear(win);
        ShowSettings();
    }
    else if(info[selectedSetting].mulOptions != nullptr)
    {
        string code = info[selectedSetting].mulOptions->code;
        string value = settingsFile->GetSettingsData(code);
        string newValue; 
        if(code == "color-mode")
        {
            switch (changingNum) {
                case 0:
                    newValue = "Default";
                    break;
                case 1:
                    newValue = "Classic";
                    break;
            }
        }
        else if(code == "background-color")
        {
            switch (changingNum) {
                case 0:
                    newValue = "Default";
                    break;
                case 1:
                    newValue = "Black";
                    break;
                case 2:
                    newValue = "Red";
                    break;
                case 3:
                    newValue = "Green";
                    break;
                case 4:
                    newValue = "Yellow";
                    break;
                case 5:
                    newValue = "Blue";
                    break;
                case 6:
                    newValue = "Magenta";
                    break;
                case 7:
                    newValue = "Cyan";
                    break;
                case 8:
                    newValue = "White";
                    break;
            }
        }
        else if(code == "first-letter-color")
        {
            switch (changingNum) {
                case 0:
                    newValue = "Black";
                    break;
                case 1:
                    newValue = "Red";
                    break;
                case 2:
                    newValue = "Green";
                    break;
                case 3:
                    newValue = "Yellow";
                    break;
                case 4:
                    newValue = "Blue";
                    break;
                case 5:
                    newValue = "Magenta";
                    break;
                case 6:
                    newValue = "Cyan";
                    break;
                case 7:
                    newValue = "White";
                    break;
            }
        }

        if(value != newValue)
        {
            settingsFile->ChangeSettingsValue(code, newValue);
            //wclear(win);
            ShowSettings();
        }
    }
}

void SettingsManager::ChangeSettingArrow(int key)
{
    if(!changingSetting)
        return;
    if(info[selectedSetting].mulSettingsBar != nullptr)
    {
        string code = info[selectedSetting].mulSettingsBar->settingsBar[changingNum].code;
        int value = stoi(settingsFile->GetSettingsData(code));
        if(key == KEY_RIGHT)
            value++;
        else if(key == KEY_LEFT)
            value--;
        else if(key == 562) //Ctrl + Right Key
            value += 5;
        else if(key == 547) //Ctrl + Left Key
            value -= 5; 

        if(value < info[selectedSetting].mulSettingsBar->settingsBar[changingNum].min)
            value = info[selectedSetting].mulSettingsBar->settingsBar[changingNum].min;
        if(value >  info[selectedSetting].mulSettingsBar->settingsBar[changingNum].max)
            value =  info[selectedSetting].mulSettingsBar->settingsBar[changingNum].max;

        settingsFile->ChangeSettingsValue(code, std::to_string(value));

        colorManager->UpdateColorSettings();
        //wclear(win);
        ShowSettings();
    }
}

bool SettingsManager::CheckCondition(int index)
{
    bool valid = true;
    if(info[index].settingsCondition == nullptr)
        return true;
    for(int j = 0; j < info[index].settingsCondition->size(); j++)
    {
        string value = settingsFile->GetSettingsData((*(info[index].settingsCondition))[j].code);
        if(value != (*(info[index].settingsCondition))[j].conditionValue)
        {
            valid = false;
            break;
        }
    }
    return valid;
}
