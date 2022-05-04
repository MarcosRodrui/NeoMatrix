#ifndef _ASCIIART_H_
#define _ASCIIART_H_

/*
Original creator:
Author: Lord Hypersonic
Email: lordhypersonic.522@gmail.com
Website: www.lordhypersonic.blogspot.com

The original code was modified in orther to be used with ncurses
Change font to Big Money-NW by Nathan Bloomfield
*/

#include <iostream>
#include <string>
#include <curses.h>

using std::string;
using std::cout;
using std::endl;

WINDOW * title(string, int, int, int &, int &);
WINDOW * smallTitle(string, int, int, int &, int &);
WINDOW * minimalText(string, int, int, int &, int &);

#endif