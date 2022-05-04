#include "asciiart.h"

//Modificar el códgio para hacer el título como me fuste
//Poner en el medio de la pantalla

WINDOW * title(string input, int screenWidth, int screenHeight,
    int & width, int & height)
{
    //distance between letters
    //Example: distance[1] is the distance between first Letter (N) and second Letter (o) 
    int distance[9] = {0, 10, 10, 10, 14, 10, 10, 10, 4}; 
    for(int i = 1; i < 9; i++)
        distance[i] += distance[i - 1];
    
    int totalDistance = distance[8] + 10; //10 is the width of the X
    int startDistance = (screenWidth - totalDistance) / 2;
    if(totalDistance > screenWidth || 10 > screenHeight)
        return smallTitle(input, screenWidth, screenHeight, width, height);

    WINDOW * win = newwin(10, screenWidth, 0, 0);
    refresh();
    wattron(win, COLOR_PAIR(3));
    width = screenWidth;
    height = 10;

    string firstLayer = "";
    for (int i=0; i < input.size(); i++)
    {
        if (input[i] == 'A' || input[i]== 'a')
            firstLayer ="";
        if (input[i] == 'E' || input[i] == 'e')
            firstLayer = "";
        if (input[i] == 'I' || input[i] == 'i')
            firstLayer = "$$\\ ";
        if (input[i] == 'M' || input[i] == 'm')
            firstLayer = "";
        if (input[i] == 'N' || input[i] == 'n')
            firstLayer = "$$\\   $$\\";
        if (input[i] == 'O' || input[i] == 'o')
            firstLayer = "";
        if (input[i] == 'R' || input[i] == 'r')
            firstLayer = "";
        if (input[i] == 'T' || input[i] == 't')
            firstLayer = "  $$\\     ";
        if (input[i] == 'X' || input[i] == 'x')
            firstLayer = "";
        mvwprintw(win, 0,startDistance + distance[i], firstLayer.c_str());
    }

    string secondLayer = "";
    for (int i=0; i < input.size(); i++)
    {
        if (input[i] == 'A' || input[i]== 'a')
            secondLayer ="";
        if (input[i] == 'E' || input[i] == 'e')
            secondLayer = "";
        if (input[i] == 'I' || input[i] == 'i')
            secondLayer = "\\__|";
        if (input[i] == 'M' || input[i] == 'm')
            secondLayer = "";
        if (input[i] == 'N' || input[i] == 'n')
            secondLayer = "$$$\\  $$ |";
        if (input[i] == 'O' || input[i] == 'o')
            secondLayer = "";
        if (input[i] == 'R' || input[i] == 'r')
            secondLayer = "";
        if (input[i] == 'T' || input[i] == 't')
            secondLayer = "  $$ |    ";
        if (input[i] == 'X' || input[i] == 'x')
            secondLayer = "";
        mvwprintw(win, 1,startDistance + distance[i], secondLayer.c_str());
    }

    string thirdLayer = "";
    for (int i=0; i < input.size(); i++)
    {
        if (input[i] == 'A' || input[i]== 'a')
            thirdLayer ="  $$$$$$\\  ";
        if (input[i] == 'E' || input[i] == 'e')
            thirdLayer = " $$$$$$\\  ";
        if (input[i] == 'I' || input[i] == 'i')
            thirdLayer = "$$\\ ";
        if (input[i] == 'M' || input[i] == 'm')
            thirdLayer = "$$$$$$\\$$$$\\  ";
        if (input[i] == 'N' || input[i] == 'n')
            thirdLayer = "$$$$\\ $$ |";
        if (input[i] == 'O' || input[i] == 'o')
            thirdLayer = " $$$$$$\\ ";
        if (input[i] == 'R' || input[i] == 'r')
            thirdLayer = " $$$$$$\\  ";
        if (input[i] == 'T' || input[i] == 't')
            thirdLayer = "$$$$$$\\   ";
        if (input[i] == 'X' || input[i] == 'x')
            thirdLayer = "$$\\   $$\\ ";
        mvwprintw(win, 2,startDistance + distance[i], thirdLayer.c_str());
    }

    string forthLayer = "";
    for (int i=0; i < input.size(); i++)
    {
        if (input[i] == 'A' || input[i]== 'a')
            forthLayer =" \\____$$\\ ";
        if (input[i] == 'E' || input[i] == 'e')
            forthLayer = "$$  __$$\\ ";
        if (input[i] == 'I' || input[i] == 'i')
            forthLayer = "$$ |";
        if (input[i] == 'M' || input[i] == 'm')
            forthLayer = "$$  _$$  _$$\\ ";
        if (input[i] == 'N' || input[i] == 'n')
            forthLayer = "$$ $$\\$$ |";
        if (input[i] == 'O' || input[i] == 'o')
            forthLayer = "$$  __$$\\ ";
        if (input[i] == 'R' || input[i] == 'r')
            forthLayer = "$$  __$$\\ ";
        if (input[i] == 'T' || input[i] == 't')
            forthLayer = "\\_$$  _|  ";
        if (input[i] == 'X' || input[i] == 'x')
            forthLayer = "\\$$\\ $$  |";
        mvwprintw(win, 3, startDistance + distance[i], forthLayer.c_str());
    }

    string fifthLayer = "";
    for (int i=0; i < input.size(); i++)
    {
        if (input[i] == 'A' || input[i]== 'a')
            fifthLayer =" $$$$$$$ |";
        if (input[i] == 'E' || input[i] == 'e')
            fifthLayer = "$$$$$$$$ |";
        if (input[i] == 'I' || input[i] == 'i')
            fifthLayer = "$$ |";
        if (input[i] == 'M' || input[i] == 'm')
            fifthLayer = "$$ / $$ / $$ |";
        if (input[i] == 'N' || input[i] == 'n')
            fifthLayer = "$$ \\$$$$ |";
        if (input[i] == 'O' || input[i] == 'o')
            fifthLayer = "$$ /  $$ |";
        if (input[i] == 'R' || input[i] == 'r')
            fifthLayer = "$$ |  \\__|";
        if (input[i] == 'T' || input[i] == 't')
            fifthLayer = "  $$ |    ";
        if (input[i] == 'X' || input[i] == 'x')
            fifthLayer = " \\$$$$  / ";
        mvwprintw(win, 4,startDistance + distance[i], fifthLayer.c_str());
    }

    string sixthLayer = "";
    for (int i=0; i < input.size(); i++)
    {
        if (input[i] == 'A' || input[i]== 'a')
            sixthLayer ="$$  __$$ |";
        if (input[i] == 'E' || input[i] == 'e')
            sixthLayer = "$$   ____|";
        if (input[i] == 'I' || input[i] == 'i')
            sixthLayer = "$$ |";
        if (input[i] == 'M' || input[i] == 'm')
            sixthLayer = "$$ | $$ | $$ |";
        if (input[i] == 'N' || input[i] == 'n')
            sixthLayer = "$$ |\\$$$ |";
        if (input[i] == 'O' || input[i] == 'o')
            sixthLayer = "$$ |  $$ |";
        if (input[i] == 'R' || input[i] == 'r')
            sixthLayer = "$$ |      ";
        if (input[i] == 'T' || input[i] == 't')
            sixthLayer = "  $$ |$$\\ ";
        if (input[i] == 'X' || input[i] == 'x')
            sixthLayer = " $$  $$<  ";
        mvwprintw(win, 5,startDistance + distance[i], sixthLayer.c_str());
    }

    string seventhLayer = "";
    for (int i=0; i < input.size(); i++)
    {
        if (input[i] == 'A' || input[i]== 'a')
            seventhLayer ="\\$$$$$$$ |";
        if (input[i] == 'E' || input[i] == 'e')
            seventhLayer = "\\$$$$$$$\\ ";
        if (input[i] == 'I' || input[i] == 'i')
            seventhLayer = "$$ |";
        if (input[i] == 'M' || input[i] == 'm')
            seventhLayer = "$$ | $$ | $$ |";
        if (input[i] == 'N' || input[i] == 'n')
            seventhLayer = "$$ | \\$$ |";
        if (input[i] == 'O' || input[i] == 'o')
            seventhLayer = "\\$$$$$$  |";
        if (input[i] == 'R' || input[i] == 'r')
            seventhLayer = "$$ |      ";
        if (input[i] == 'T' || input[i] == 't')
            seventhLayer = "  \\$$$$  |";
        if (input[i] == 'X' || input[i] == 'x')
            seventhLayer = "$$  /\\$$\\ ";
        mvwprintw(win, 6,startDistance + distance[i], seventhLayer.c_str());
    }

    string eighthLayer = "";
    for (int i=0; i < input.size(); i++)
    {
        if (input[i] == 'A' || input[i]== 'a')
            eighthLayer =" \\_______|";
        if (input[i] == 'E' || input[i] == 'e')
            eighthLayer = " \\_______|";
        if (input[i] == 'I' || input[i] == 'i')
            eighthLayer = "\\__|";
        if (input[i] == 'M' || input[i] == 'm')
            eighthLayer = "\\__| \\__| \\__|";
        if (input[i] == 'N' || input[i] == 'n')
            eighthLayer = "\\__|  \\__|";
        if (input[i] == 'O' || input[i] == 'o')
            eighthLayer = " \\______/ ";
        if (input[i] == 'R' || input[i] == 'r')
            eighthLayer = "\\__|      ";
        if (input[i] == 'T' || input[i] == 't')
            eighthLayer = "   \\____/ ";
        if (input[i] == 'X' || input[i] == 'x')
            eighthLayer = "\\__/  \\__|";
        mvwprintw(win, 7,startDistance + distance[i], eighthLayer.c_str());
    }

    wattroff(win, COLOR_PAIR(3));

    return win;
}                                   

WINDOW * smallTitle(string input, int screenWidth, int screenHeight,
    int & width, int & height)
{
    //distance between letters
    //Example: distance[1] is the distance between first Letter (N) and second Letter (o) 
    int distance[9] = {0, 7, 4, 5, 6, 5, 6, 5, 4}; 
    for(int i = 1; i < 9; i++)
        distance[i] += distance[i - 1];
    
    int totalDistance = distance[8] + 8; //8 is the width of the X
    int startDistance = (screenWidth - totalDistance) / 2;

    if(totalDistance > screenWidth || 5 > screenHeight)
        return minimalText(input, screenWidth, screenHeight, width, height);

    WINDOW * win = newwin(5, screenWidth, 0, 0);
    refresh();
    wattron(win, COLOR_PAIR(3));
    width = screenWidth;
    height = 5;

    string firstLayer = "";
    for (int i=0; i < input.size(); i++)
    {
        if (input[i] == 'A' || input[i]== 'a')
            firstLayer ="____";
        if (input[i] == 'E' || input[i] == 'e')
            firstLayer = "___";
        if (input[i] == 'I' || input[i] == 'i')
            firstLayer = "___";
        if (input[i] == 'M' || input[i] == 'm')
            firstLayer = "_____";
        if (input[i] == 'N' || input[i] == 'n')
            firstLayer = "__   _";
        if (input[i] == 'O' || input[i] == 'o')
            firstLayer = " __ ";
        if (input[i] == 'R' || input[i] == 'r')
            firstLayer = " ___";
        if (input[i] == 'T' || input[i] == 't')
            firstLayer = "_____";
        if (input[i] == 'X' || input[i] == 'x')
            firstLayer = "_    _";
        mvwprintw(win, 0,startDistance + distance[i], firstLayer.c_str());
    }

    string secondLayer = "";
    for (int i=0; i < input.size(); i++)
    {
        if (input[i] == 'A' || input[i]== 'a')
            secondLayer ="|__|";
        if (input[i] == 'E' || input[i] == 'e')
            secondLayer = "|__";
        if (input[i] == 'I' || input[i] == 'i')
            secondLayer = " | ";
        if (input[i] == 'M' || input[i] == 'm')
            secondLayer = "| | |";
        if (input[i] == 'N' || input[i] == 'n')
            secondLayer = "| \\  |";
        if (input[i] == 'O' || input[i] == 'o')
            secondLayer = "|  |";
        if (input[i] == 'R' || input[i] == 'r')
            secondLayer = "|__/";
        if (input[i] == 'T' || input[i] == 't')
            secondLayer = "  |  ";
        if (input[i] == 'X' || input[i] == 'x')
            secondLayer = " \\__/ ";
        mvwprintw(win, 1,startDistance + distance[i], secondLayer.c_str());
    }

    string thirdLayer = "";
    for (int i=0; i < input.size(); i++)
    {
        if (input[i] == 'A' || input[i]== 'a')
            thirdLayer ="|  |";
        if (input[i] == 'E' || input[i] == 'e')
            thirdLayer = "|__";
        if (input[i] == 'I' || input[i] == 'i')
            thirdLayer = "_|_";
        if (input[i] == 'M' || input[i] == 'm')
            thirdLayer = "| | |";
        if (input[i] == 'N' || input[i] == 'n')
            thirdLayer = "|  \\_|";
        if (input[i] == 'O' || input[i] == 'o')
            thirdLayer = "|__|";
        if (input[i] == 'R' || input[i] == 'r')
            thirdLayer = "| \\_";
        if (input[i] == 'T' || input[i] == 't')
            thirdLayer = "  |  ";
        if (input[i] == 'X' || input[i] == 'x')
            thirdLayer = "_/  \\_";
        mvwprintw(win, 2,startDistance + distance[i], thirdLayer.c_str());
    }

    wattroff(win, COLOR_PAIR(3));

    return win;
}

WINDOW * minimalText(string input, int screenWidth, int screenHeight,
    int & width, int & height)
{
    int totalDistance = 9;
    int startDistance = (screenWidth - totalDistance) / 2;

    if(totalDistance > screenWidth || 4 > screenHeight)
        return nullptr; //No title
    else
    {
        WINDOW * win = newwin(4, screenWidth, 0, 0);
        refresh();
        wattron(win, COLOR_PAIR(3));
        width = screenWidth;
        height = 4;

        mvwprintw(win, 1, startDistance, input.c_str());
        wattroff(win, COLOR_PAIR(3));
        return win;
    }
}