#include "effects.h"
#include <curses.h>
#include <string>

EffectController::EffectController(SettingsFile *settingsFile)
{
   this->settingsFile = settingsFile;
   spawnTime = elapseTime = width = height = 0;
   win = nullptr;
}

EffectController::~EffectController()
{
   ResetController();
}

void EffectController::StartController(int height, int width, WINDOW * win)
{
   this->height = height;
   this->width = width;
   this->win = win;
   timeBefore = std::chrono::steady_clock::now();

   for(int i = 0; i < width; i++)
      columnData.push_back(0);

   spawnTimeBase = spawnTimeBaseMax * 
      1 / (stoi(settingsFile->GetSettingsData("letter-density")) / 100.0);
   spawnTimeBase /= (width / 100.0);
   spawnTimeBase *= (height / 50.0);

   string background = settingsFile->GetSettingsData("background-color");
   if(background == "Default")
      backgroundColor = 0;
   else if(background == "Black")
      backgroundColor = 1;
   else if(background == "Red")
      backgroundColor = 2;
   else if(background == "Green")
      backgroundColor = 3;
   else if(background == "Yellow")
      backgroundColor = 4;
   else if(background == "Blue")
      backgroundColor = 5;
   else if(background == "Magenta")
      backgroundColor = 6;
   else if(background == "Cyan")
      backgroundColor = 7;
   else 
      backgroundColor = 8;

   wbkgd(win, COLOR_PAIR((backgroundColor + 1) * 8));
   wclear(win);
   refresh();
   wrefresh(win);

   for(int x = 0; x < width; x++)
      erasePos.push_back(vector<int> (height, 0));
}

void EffectController::ResetController()
{
   width = height = 0;
   win = nullptr;
   for(int i = 0; i < groups.size(); i++)
      delete groups[i];
   groups.erase(groups.begin(), groups.end());
   columnData.erase(columnData.begin(), columnData.end());
   erasePos.clear();
}

void EffectController::Update()
{
   if(!win)
      return;

   std::chrono::steady_clock::time_point timeNow = std::chrono::steady_clock::now();

   long double difference = std::chrono::duration_cast<std::chrono::microseconds>(timeNow - timeBefore).count();
   timeBefore = timeNow;
   difference /= 1e6;

   elapseTime += difference;

   if(elapseTime >= objetive)
   {
      UpdateSpawn(elapseTime);
      for(int i = 0; i < groups.size(); i++)
      {
         groups[i]->UpdateLetters(elapseTime, erasePos);

         //Removes the group when is not visible
         if(groups[i]->GetLastLetterPosition() > height)
         {
            delete groups[i];
            groups.erase(groups.begin() + i, groups.begin() + i + 1);
            i--;
         }
      }

      for(int i = groups.size() - 1; i >= 0; i--)
         groups[i]->ShowLetters(win, height, erasePos);

      wattron(win, COLOR_PAIR((backgroundColor + 1) * 8));
      for(int x = 0; x < width; x++) 
      {
         for(int y = 0; y < height; y++)
         {
            if(erasePos[x][y] == 1)
            {
               mvwprintw(win, y, x, " ");
            }
            erasePos[x][y] = 0;
         }
      }
      wattroff(win, COLOR_PAIR((backgroundColor + 1) * 8));

      wrefresh(win);
      elapseTime = 0;
   }
}

//Private Functions
void EffectController::UpdateSpawn(long double difference)
{
   spawnTime += difference; 
   while(spawnTime >= spawnTimeBase)
   {
      spawnTime -= spawnTimeBase;

      vector<int> availableColumns;
      int objetive; //It first checks for colums with 0 groups, then 1, then 2...
      for(objetive = 0; ;objetive++)
      {
         for(int i = 0; i < width; i++)
         {
            if(columnData[i] == objetive)
               availableColumns.push_back(i);
         }
         if(availableColumns.size() != 0)
            break;
      }
      int selectedIndex = (rand()%availableColumns.size());
      int selectedColumn = availableColumns[selectedIndex];
      
      columnData[selectedColumn]++;
      CretateGroup(selectedColumn);
   }
}

void EffectController::CretateGroup(int column)
{
   int minSpeed = stoi(settingsFile->GetSettingsData("min-falling-speed")); 
   int maxSpeed = stoi(settingsFile->GetSettingsData("max-falling-speed"));
   double speed = (maxSpeed - minSpeed) * (rand()%10000/10000.0) + minSpeed;
   speed = speedMult * (1/speed);

   int minSize = stoi(settingsFile->GetSettingsData("min-trail-size"));
   int maxSize = stoi(settingsFile->GetSettingsData("max-trail-size"));
   int size = (maxSize - minSize) * (rand()%10000)/10000.0 + minSize;
   size = height * (size / 30.0);

   int firstLetterColor = -1;
   int colorGroup = -1;
   if(settingsFile->GetSettingsData("first-letter") == "1")
      firstLetterColor = GetRandomFirstLetterColor(settingsFile);
   if(settingsFile->GetSettingsData("unique-color-group") == "1")
      colorGroup = GetRandomColor(settingsFile);

   EffectGroup *newGroup = new EffectGroup(settingsFile, column, speed, size, firstLetterColor, backgroundColor, colorGroup);
   groups.push_back(newGroup);
}

//EffectGroup PUBLIC
EffectGroup::EffectGroup(SettingsFile * settingsFile, int column, double fallingSpeedBase, int maxSize, 
      int firstLetterColor, int backgroundColor, int colorGroup)
{
   this->settingsFile = settingsFile;
   this->column = column;
   this->fallingSpeedBase = fallingSpeedBase;
   this->maxSize = maxSize;
   this->firstLetterColor = firstLetterColor;
   this->backgroundColor = backgroundColor;
   this->colorGroup = colorGroup;
   fallingSpeedTime = 0;
   firstLetterPosition = -1;
   eraseLetters = 0;
}

EffectGroup::~EffectGroup()
{
   for(int i = 0; i < letters.size(); i++)
      delete letters[i];
}

void EffectGroup::UpdateLetters(double difference, vector<vector<int>> & erasePos)
{
   eraseLetters = 0;
   fallingSpeedTime += difference;
   while(fallingSpeedTime > fallingSpeedBase)
   {
      fallingSpeedTime -= fallingSpeedBase;

      if(firstLetterColor != -1)
      {
         if(letters.size() > 0)
            letters[letters.size() - 1]->UpdateLetter();
         if(settingsFile->GetSettingsData("first-letter-transition") == "1")
         {
            for(int i = 1; i <= COLOR_TRANSITION && i < letters.size(); i++)
               letters[letters.size() - 1 - i]->UpdateLetter();
         }
      }
      CreateLetter();
      firstLetterPosition++;
      if(letters.size() > maxSize)
      {
         delete letters[0];
         letters.erase(letters.begin(), letters.begin() + 1);
         if(firstLetterPosition - maxSize < erasePos[column].size())
            erasePos[column][firstLetterPosition - maxSize] = 1;
         eraseLetters++;
      }
      if(settingsFile->GetSettingsData("last-letter-transition") == "1")
      {
         for(int i = 0; i < COLOR_TRANSITION && i < letters.size() 
               && maxSize - (int)letters.size() - COLOR_TRANSITION + i <= 0; i++)
            letters[i]->UpdateLetter();
      }
   }
   if(settingsFile->GetSettingsData("min-change-letter") != "0" ||
         settingsFile->GetSettingsData("max-change-letter") != "0")
   {
      for(int i = 0; i < letters.size(); i++)
      {
         if(letters[i]->UpdateLetter(difference))
            letters[i]->SetLetter(GetRandomCharacter());
      }
   }
}

int EffectGroup::GetLastLetterPosition()
{
   return firstLetterPosition - letters.size() + 1;
}

void EffectGroup::ShowLetters(WINDOW *win, int height, vector<vector<int>> & erasePos)
{
   int letterSize = letters.size();

   for(int i = 0; i < letters.size(); i++)
   {
      int letterHeight = firstLetterPosition - letters.size() + 1 + i;
      if(letterHeight >= height)
         break;

      if(erasePos[column][letterHeight] == 2)
         continue;
      erasePos[column][letterHeight] = 2;

      if(!letters[i]->CheckUpdate())
         continue;

      bool firstLetter = settingsFile->GetSettingsData("terminal-colors") == "0";
      bool onlyFirstLetter = firstLetter && settingsFile->GetSettingsData("first-letter") == "1" 
         && settingsFile->GetSettingsData("first-letter-transition") == "0";
      bool lastLetter = firstLetter;
      firstLetter &= settingsFile->GetSettingsData("first-letter-transition") == "1";
      lastLetter &= settingsFile->GetSettingsData("last-letter-transition") == "1";

      int difference = maxSize - letterSize;

      if(onlyFirstLetter && i == (int)letters.size() - 1)
         mvwadd_wch(win, letterHeight, column, 
               letters[i]->GetFirstLetter(0));
      else if(firstLetter && i >=  ((int)letters.size() - (1 + COLOR_TRANSITION)) && firstLetterColor != -1)
         mvwadd_wch(win, letterHeight, column, 
               letters[i]->GetFirstLetter((int)letters.size() - 1 - i));
      else if(lastLetter && difference < COLOR_TRANSITION && i < COLOR_TRANSITION - difference)
         mvwadd_wch(win, letterHeight, column, 
            letters[i]->GetBackLetter(COLOR_TRANSITION - 1 - i - difference));
      else
         mvwadd_wch(win, letterHeight, column, letters[i]->GetLetter());
   }
}

//EffectGroup PRIVATE
void EffectGroup::CreateLetter()
{
   int color = colorGroup;
   if(colorGroup == -1)
      color = GetRandomColor(settingsFile);
   EffectLetter * effectLetter = new EffectLetter(settingsFile, GetRandomCharacter(), 
         color, backgroundColor, firstLetterColor);
   letters.push_back(effectLetter);
}

wchar_t EffectGroup::GetRandomCharacter()
{
   wchar_t selected;
   vector<std::pair<int, int>> characters;

   if(settingsFile->GetSettingsData("basic-latin") == "1")
      characters.push_back(std::pair<int, int> (33, 126));              //Basic Latin
   if(settingsFile->GetSettingsData("latin-1-supplement") == "1")
      characters.push_back(std::pair<int, int> (0x00a1, 0x00ff));       //Latin-1 Supplement
   if(settingsFile->GetSettingsData("armenian") == "1")
   {
      characters.push_back(std::pair<int, int> (0x0531, 0x0556));       //Armenian
      characters.push_back(std::pair<int, int> (0x0560, 0x0588));
      characters.push_back(std::pair<int, int> (0x058D, 0x058E));
   }
   if(settingsFile->GetSettingsData("hebrew") == "1")
      characters.push_back(std::pair<int, int> (0x05D0, 0x05EA));       //Hebrew
   if(settingsFile->GetSettingsData("nko") == "1")
   {
      characters.push_back(std::pair<int, int> (0x07C0, 0x07EA));       //Nko
      characters.push_back(std::pair<int, int> (0x07F6, 0x07FA));
   }
   if(settingsFile->GetSettingsData("mandaic") == "1")
      characters.push_back(std::pair<int, int> (0x0840, 0x0858));       //Mandaic
   if(settingsFile->GetSettingsData("devanagari") == "1")
   {
      characters.push_back(std::pair<int, int> (0x0904, 0x0939));       //Devanagari
      characters.push_back(std::pair<int, int> (0x0958, 0x0961));
      characters.push_back(std::pair<int, int> (0x0964, 0x097F));
   }
   if(settingsFile->GetSettingsData("thai") == "1")
   {
      characters.push_back(std::pair<int, int> (0x0E01, 0x0E30));       //Thai
      characters.push_back(std::pair<int, int> (0x0E3F, 0x0E46));
      characters.push_back(std::pair<int, int> (0x0E4F, 0x0E5A));
   }
   if(settingsFile->GetSettingsData("runic") == "1")
   {
      characters.push_back(std::pair<int, int> (0x16A0, 0x16EA));       //Runic
      characters.push_back(std::pair<int, int> (0x16EE, 0x16F8));       
   }
   if(settingsFile->GetSettingsData("hanunoo") == "1")
   {
      characters.push_back(std::pair<int, int> (0x1720, 0x1731));       //Thai
      characters.push_back(std::pair<int, int> (0x1735, 0x1736));       
   }
   if(settingsFile->GetSettingsData("buhind") == "1")
      characters.push_back(std::pair<int, int> (0x1740, 0x1751));       //Thai
   if(settingsFile->GetSettingsData("limbu") == "1")
   {
      characters.push_back(std::pair<int, int> (0x1900, 0x191E));       //Thai
      characters.push_back(std::pair<int, int> (0x1940, 0x1940));
      characters.push_back(std::pair<int, int> (0x1944, 0x194F));
   }
   if(settingsFile->GetSettingsData("khmer") == "1")
   {
      characters.push_back(std::pair<int, int> (0x19E0, 0x19E9));       //Thai
      characters.push_back(std::pair<int, int> (0x19F0, 0x19F9));       //Thai
   }
   if(settingsFile->GetSettingsData("ol_chiki") == "1")
   {
      characters.push_back(std::pair<int, int> (0x1C50, 0x1C77));       //Thai
   }
   if(settingsFile->GetSettingsData("tifinagh") == "1")
   {
      characters.push_back(std::pair<int, int> (0x2D30, 0x2D3D));       //Thai
      characters.push_back(std::pair<int, int> (0x2D3F, 0x2D41)); 
      characters.push_back(std::pair<int, int> (0x2D43, 0x2D45));       
      characters.push_back(std::pair<int, int> (0x2D47, 0x2D47));       
      characters.push_back(std::pair<int, int> (0x2D49, 0x2D56));       
      characters.push_back(std::pair<int, int> (0x2D59, 0x2D66));       
   }
   //MARCOS, ME TOCA COMPROBAR LISA A4D0
   if(settingsFile->GetSettingsData("myanmar") == "1")
   {
      characters.push_back(std::pair<int, int> (0x3131, 0x318F));       //Thai
   }
   if(settingsFile->GetSettingsData("katakana") == "1")
   {
      characters.push_back(std::pair<int, int> (0xff66, 0xff6f));       //Katakana
      characters.push_back(std::pair<int, int> (0xff71, 0xff9d));
   }
   if(characters.size() == 0)
      characters.push_back(std::pair<int, int> (33, 126));              //Basic Latin

   int total = 0;
   for(int i = 0; i < characters.size(); i++)
      total += characters[i].second - characters[i].first + 1;

   int chose = rand()%total;
   int count = 0;
   for(int i = 0; i < characters.size(); i++)
   {
      if(chose >= count && chose < characters[i].second - characters[i].first + 1 + count)
      {
         chose -= count;
         selected = characters[i].first + chose;
         break;
      }
      count += characters[i].second - characters[i].first + 1; 
   }
   return selected;
}

//EffectLetter PUBLIC
EffectLetter::EffectLetter(SettingsFile * settingsFile, wchar_t letter,
      int color, int backgroundColor, int firstLetterColor)
{
   this->settingsFile = settingsFile;
   this->color = color;
   this->backgroundColor = backgroundColor;
   this->firstLetterColor = firstLetterColor;
   SetLetter(letter);

   UpdateChangeLetterTime();
   update = true;
}

EffectLetter::~EffectLetter()
{

}

void EffectLetter::UpdateChangeLetterTime()
{
   int minChangeLetter = stoi(settingsFile->GetSettingsData("min-change-letter")); 
   int maxChangeLetter = stoi(settingsFile->GetSettingsData("max-change-letter"));
   changeLetterTime = (maxChangeLetter - minChangeLetter) * (rand()%10000/10000.0) + minChangeLetter;
   changeLetterTime = changeLetterMultBase * (1/changeLetterTime);
}

bool EffectLetter::UpdateLetter(double difference)
{
   changeLetterTime -= difference;
   if(changeLetterTime < 0)
   {
      UpdateChangeLetterTime();
      update = true;
      return true;
   }
   return false;
}

void EffectLetter::SetLetter(wchar_t letter) 
{
   wchar_t temp[2];
   temp[0] = letter;
   temp[1] = '\0';
   setcchar(&letterData, temp, WA_NORMAL, color + 1 + backgroundColor * 8, NULL);

   firstLettersData.clear();
   
   cchar_t firstLetterData;
   setcchar(&firstLetterData, temp, WA_NORMAL, firstLetterColor + 1 + backgroundColor * 8, NULL);
   firstLettersData.push_back(firstLetterData);

   for(int i = COLOR_TRANSITION - 1; i >= 0; i--)
   {
      cchar_t newData;
      setcchar(&newData, temp, WA_NORMAL, 
            color + 1 + backgroundColor * 8 + 72 * (firstLetterColor * COLOR_TRANSITION + i + 1), NULL);
      firstLettersData.push_back(newData);
   }

   for(int i = 0; i < COLOR_TRANSITION; i++) 
   {
      cchar_t newData;
      int lastLetterColor = backgroundColor - 1;
      if(lastLetterColor == -1)
         lastLetterColor = 0;
      setcchar(&newData, temp, WA_NORMAL, 
            color + 1 + backgroundColor * 8 + 72 * (lastLetterColor * COLOR_TRANSITION + i + 1), NULL);
      backLettersData.push_back(newData);
   }

   this->letter = letter;
}

cchar_t * EffectLetter::GetLetter()
{
   return &letterData;
}

cchar_t * EffectLetter::GetFirstLetter(int index)
{
   return &(firstLettersData[index]);
}

cchar_t * EffectLetter::GetBackLetter(int index)
{
   return &(backLettersData[index]);
}

int EffectLetter::GetColor()
{
   return color;
}

bool EffectLetter::CheckUpdate()
{
   if(update)
   {
      update = false;
      return true;
   }
   return false;
}

void EffectLetter::UpdateLetter()
{
   update = true;
}

//Private Functions

int GetRandomFirstLetterColor(SettingsFile * settingsFile)
{
   vector<int> colorProportions;
   vector<string> codes = {
    "first-letter-black-proportion",
    "first-letter-red-proportion",
    "first-letter-green-proportion",
    "first-letter-yellow-proportion",
    "first-letter-blue-proportion",
    "first-letter-magenta-proportion",
    "first-letter-cyan-proportion",
    "first-letter-white-proportion"};

   int totalProp = 0;
   for(int i = 0; i < codes.size(); i++)
   {
      int proportion = stoi(settingsFile->GetSettingsData(codes[i]));
      colorProportions.push_back(proportion);
      totalProp += proportion;
   }
   if(totalProp == 0)
   {
      totalProp = codes.size();
      for(int i = 0; i < totalProp; i++)
         colorProportions[i] = 1;
   }

   long double random = (rand()%(totalProp * 100))/(long double)100;  

   int colorSelected = 0;
   int checkForColor = 0;
   for(int i = 0; i < colorProportions.size(); i++)
   {
      checkForColor += colorProportions[i];
      if(random < checkForColor)
      {
         colorSelected = i;
         break;
      }
   }
   return colorSelected;
}

int GetRandomColor(SettingsFile * settingsFile)
{
   vector<int> colorProportions;
   vector<string> codes = {
    "black-proportion",
    "red-proportion",
    "green-proportion",
    "yellow-proportion",
    "blue-proportion",
    "magenta-proportion",
    "cyan-proportion",
    "white-proportion"};

   int totalProp = 0;
   for(int i = 0; i < codes.size(); i++)
   {
      int proportion = stoi(settingsFile->GetSettingsData(codes[i]));
      colorProportions.push_back(proportion);
      totalProp += proportion;
   }
   if(totalProp == 0)
   {
      totalProp = codes.size();
      for(int i = 0; i < totalProp; i++)
         colorProportions[i] = 1;
   }

   long double random = (rand()%(totalProp * 100))/(long double)100;  

   int colorSelected = 0;
   int checkForColor = 0;
   for(int i = 0; i < colorProportions.size(); i++)
   {
      checkForColor += colorProportions[i];
      if(random < checkForColor)
      {
         colorSelected = i;
         break;
      }
   }
   return colorSelected;
}
