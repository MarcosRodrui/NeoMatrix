#ifndef _EFFECTS_H_
#define _EFFECTS_H_

#include <vector>
#include <curses.h>
#include <chrono>
#include <cstdlib> 
#include <ctime> 
#include <chrono>

#include "settingsFile.h"

#define COLOR_TRANSITION 3

using std::vector;

const double spawnTimeBaseMax = 0.02;
const double speedMult = 1;
const double changeLetterMultBase = 30;

//Private Functions
int GetRandomFirstLetterColor(SettingsFile * settingsFile);
int GetRandomColor(SettingsFile * settingsFile);

class EffectLetter
{
private:
   SettingsFile *settingsFile;

   wchar_t letter;
   cchar_t letterData;
   vector<cchar_t> firstLettersData;
   vector<cchar_t> backLettersData;
   int color; //From 0 to 7, according to ncurses colors
   int backgroundColor;
   int firstLetterColor;
   double changeLetterTime;

   bool update;

public:
   EffectLetter(SettingsFile * settingsFile, wchar_t letter, 
         int color, int backgroundColor, int firstLetterColor);
   ~EffectLetter();
   void UpdateChangeLetterTime();
   bool UpdateLetter(double difference);
   void SetLetter(wchar_t letter);
   cchar_t * GetLetter();
   cchar_t * GetFirstLetter(int index);
   cchar_t * GetBackLetter(int index);
   int GetColor();
   bool CheckUpdate();
   void UpdateLetter(); //sets update to true
};

class EffectGroup //Group of letter falling together
{
private:
   SettingsFile *settingsFile;

   vector<EffectLetter *> letters;

   double fallingSpeedBase; //When will the group fall one letter
   double fallingSpeedTime; 

   int firstLetterColor; //-1 when there is no first Letter Color
   int colorGroup; //-1 when each letter has different color
   int backgroundColor;

   int column;

   int firstLetterPosition;
   int maxSize; //Max number of letters


   int eraseLetters; //How much spaces should be added to erase the letters

   void CreateLetter();

   wchar_t GetRandomCharacter();

public:
   EffectGroup(SettingsFile * settingsFile, int column, double fallingSpeedBase, int maxSize, 
         int firstLetterColor, int backgroundColor, int colorGroup);
   ~EffectGroup();
   void UpdateLetters(double difference, vector<vector<int>> & erasePos);
   int GetLastLetterPosition();
   void ShowLetters(WINDOW * win, int height, vector<vector<int>> & erasePos);
};

class EffectController
{
private:
   SettingsFile *settingsFile;

   vector<EffectGroup *> groups; 
   vector<int> columnData; //Counts how many groups are there in a column
   vector<vector<int>> erasePos; //Where the screen will be clean, 0 std, 1 clean, 2 letter
   int height;
   int width;

   std::chrono::steady_clock::time_point timeBefore;
   long double elapseTime;
   long double objetive = 1.0 / 60; //Temporal, Refresh Rate will be an option
   
   double spawnTimeBase;
   double spawnTime; //Provisional, how much time it takes to spawn 

   int backgroundColor;
 
   WINDOW * win; //Where the effect will be display, its size has to match width height and width

   void UpdateSpawn(long double difference);
   void CretateGroup(int column);

public:
   EffectController(SettingsFile * settingsFile);
   ~EffectController();
   void StartController(int height, int width, WINDOW * win = stdscr);
   void ResetController();
   void Update(); //Effect Loop where everything happens, it has to be called every second
};

#endif
