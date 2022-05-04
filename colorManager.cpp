#include "colorManager.h"
#include <curses.h>

// COLOR_BLACK   0
// COLOR_RED     1
// COLOR_GREEN   2
// COLOR_YELLOW  3
// COLOR_BLUE    4
// COLOR_MAGENTA 5
// COLOR_CYAN    6
// COLOR_WHITE   7

ColorManager::ColorManager(SettingsFile *settingsFile)
{
    this->settingsFile = settingsFile;

    //COLOR SETTINGS
    if(has_colors() == TRUE)
	    start_color();	

    use_default_colors();
    //Create pairs, with all possible combinations
    for(int k = 0; k <= COLOR_TRANSITION*8; k++)
    {
        for(int i = 0; i <= 8; i++)
        {
            for(int j = 0; j <= 7; j++)
                init_extended_pair(72 * k + j + 8 * i + 1, j + k * 8, i - 1);
        }
    }
    
    UpdateColorSettings();      
}

void ColorManager::UpdateColorSettings(bool first)
{
    string terminalColors = settingsFile->GetSettingsData("terminal-colors");
    if(terminalColors == "1")
    {
        if(first)
        {
            endwin();
            system("./neomatrix");
            exit(1);
        }
    }
    else if(can_change_color() == TRUE)
    {
        int blackR = stoi(settingsFile->GetSettingsData("black-color-r")) * (999 / 255.0);
        int blackG = stoi(settingsFile->GetSettingsData("black-color-g")) * (999 / 255.0);
        int blackB = stoi(settingsFile->GetSettingsData("black-color-b")) * (999 / 255.0);
        init_color(COLOR_BLACK, blackR, blackG, blackB);

        int redR = stoi(settingsFile->GetSettingsData("red-color-r")) * (999 / 255.0);
        int redG = stoi(settingsFile->GetSettingsData("red-color-g")) * (999 / 255.0);
        int redB = stoi(settingsFile->GetSettingsData("red-color-b")) * (999 / 255.0);
        init_color(COLOR_RED, redR, redG, redB);

        int greenR = stoi(settingsFile->GetSettingsData("green-color-r")) * (999 / 255.0);
        int greenG = stoi(settingsFile->GetSettingsData("green-color-g")) * (999 / 255.0);
        int greenB = stoi(settingsFile->GetSettingsData("green-color-b")) * (999 / 255.0);
        init_color(COLOR_GREEN, greenR, greenG, greenB);

        int yellowR = stoi(settingsFile->GetSettingsData("yellow-color-r")) * (999 / 255.0);
        int yellowG = stoi(settingsFile->GetSettingsData("yellow-color-g")) * (999 / 255.0);
        int yellowB = stoi(settingsFile->GetSettingsData("yellow-color-b")) * (999 / 255.0);
        init_color(COLOR_YELLOW, yellowR, yellowG, yellowB);

        int blueR = stoi(settingsFile->GetSettingsData("blue-color-r")) * (999 / 255.0);
        int blueG = stoi(settingsFile->GetSettingsData("blue-color-g")) * (999 / 255.0);
        int blueB = stoi(settingsFile->GetSettingsData("blue-color-b")) * (999 / 255.0);
        init_color(COLOR_BLUE, blueR, blueG, blueB);

        int magentaR = stoi(settingsFile->GetSettingsData("magenta-color-r")) * (999 / 255.0);
        int magentaG = stoi(settingsFile->GetSettingsData("magenta-color-g")) * (999 / 255.0);
        int magentaB = stoi(settingsFile->GetSettingsData("magenta-color-b")) * (999 / 255.0);
        init_color(COLOR_MAGENTA, magentaR, magentaG, magentaB);

        int cyanR = stoi(settingsFile->GetSettingsData("cyan-color-r")) * (999 / 255.0);
        int cyanG = stoi(settingsFile->GetSettingsData("cyan-color-g")) * (999 / 255.0);
        int cyanB = stoi(settingsFile->GetSettingsData("cyan-color-b")) * (999 / 255.0);
        init_color(COLOR_CYAN, cyanR, cyanG, cyanB);

        int whiteR = stoi(settingsFile->GetSettingsData("white-color-r")) * (999 / 255.0);
        int whiteG = stoi(settingsFile->GetSettingsData("white-color-g")) * (999 / 255.0);
        int whiteB = stoi(settingsFile->GetSettingsData("white-color-b")) * (999 / 255.0);
        init_color(COLOR_WHITE, whiteR, whiteG, whiteB);

        //Creates the degradation colors
        for(int i = 0; i <= 7; i++) 
        {
            for(int j = 0; j < COLOR_TRANSITION; j++)
            {
                for(int k = 0; k <= 7; k++)
                {
                    int r, g, b, oriR, oriG, oriB, mixR, mixG, mixB;
                    switch (k) {
                    case 0:
                        oriR = blackR;
                        oriG = blackG;
                        oriB = blackB;
                        break;
                    case 1:
                        oriR = redR;
                        oriG = redG;
                        oriB = redB;
                        break;
                    case 2:
                        oriR = greenR;
                        oriG = greenG;
                        oriB = greenB;
                        break;
                    case 3:
                        oriR = yellowR;
                        oriG = yellowG;
                        oriB = yellowB;
                        break;
                    case 4:
                        oriR = blueR;
                        oriG = blueG;
                        oriB = blueB;
                        break;
                    case 5:
                        oriR = magentaR;
                        oriG = magentaG;
                        oriB = magentaB;
                        break;
                    case 6:
                        oriR = cyanR;
                        oriG = cyanG;
                        oriB = cyanB;
                        break;
                    case 7:
                        oriR = whiteR;
                        oriG = whiteG;
                        oriB = whiteB;
                        break;
                    } 

                    switch (i) {
                    case 0:
                        mixR = blackR;
                        mixG = blackG;
                        mixB = blackB;
                        break;
                    case 1:
                        mixR = redR;
                        mixG = redG;
                        mixB = redB;
                        break;
                    case 2:
                        mixR = greenR;
                        mixG = greenG;
                        mixB = greenB;
                        break;
                    case 3:
                        mixR = yellowR;
                        mixG = yellowG;
                        mixB = yellowB;
                        break;
                    case 4:
                        mixR = blueR;
                        mixG = blueG;
                        mixB = blueB;
                        break;
                    case 5:
                        mixR = magentaR;
                        mixG = magentaG;
                        mixB = magentaB;
                        break;
                    case 6:
                        mixR = cyanR;
                        mixG = cyanG;
                        mixB = cyanB;
                        break;
                    case 7:
                        mixR = whiteR;
                        mixG = whiteG;
                        mixB = whiteB;
                        break;
                    }

                    r = oriR - mixR;    
                    g = oriG - mixG;    
                    b = oriB - mixB;    
                    r = (r * (COLOR_TRANSITION - j))/(COLOR_TRANSITION + 1) + mixR;
                    g = (g * (COLOR_TRANSITION - j))/(COLOR_TRANSITION + 1) + mixG;
                    b = (b * (COLOR_TRANSITION - j))/(COLOR_TRANSITION + 1) + mixB;

                    init_extended_color(8 + i * (8 * COLOR_TRANSITION) + j * 8 + k, r, g, b);
                }
            }
        }
    }   
}

ColorManager::~ColorManager()
{

}

int ColorManager::GetColorPair(string foreground)
{
    std::transform(foreground.begin(), foreground.end(), foreground.begin(),
        [](unsigned char c){ return std::tolower(c); });

    if(foreground == "black")
        return 1;
    else if(foreground == "red")
        return 2;
    else if(foreground == "green")
        return 3;
    else if(foreground == "yellow")
        return 4;
    else if(foreground == "blue")
        return 5;
    else if(foreground == "magenta")
        return 6;
    else if(foreground == "cyan")
        return 7;
    else if(foreground == "white")
        return 8;

    return -1; //If not found   
}
