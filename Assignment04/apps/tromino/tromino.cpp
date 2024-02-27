#include <iostream>
#include <random>
#include <stdexcept>
#include <cmath>

void printArr(char** arr, unsigned int size)
{
   std::cout << "\n";
   for(int i = 0; i < size; i++)
   {  
      for(int j = 0; j < size; j++)
      {
         std::cout << arr[i][j] << " ";
      }
      std::cout <<std::endl;
   }
}

void deleteArr(char** arr, unsigned int size)
{
   for(int i = 0; i < size; i++)
   {  
      delete[] arr[i];
   }
   delete[] arr;

   for(int i = 0; i < size; i++)
   {  
      arr[i] = nullptr;
   }
   arr = nullptr;
}

std::pair<int,int> findForbid(char** arr, std::pair<int, int> startXY, unsigned int size)
{
   for(int i = startXY.first; i < startXY.first + size; i++)
   { 
      for(int j = startXY.second; j < startXY.second + size; j++)
      {
         if (arr[i][j] == 'x' || arr[i][j] == 'T')
            return std::pair<int,int>(i,j);
      }
   }
   std::cerr << "\nForbidden tile not found! Game is now invalid.\n";
   return std::pair<int,int>(-1,-1);
}

void placeTromino(char** arr, unsigned int size, std::pair<int,int> start, const unsigned int origSize)
{
   //Base Case
   if (size <= 1)
      return;

   //Find forbidden in this grid/subgrid
   std::pair<int,int> forbidden = findForbid(arr, start, size);
   bool Q1 = false, Q2 = false, Q3 = false, Q4 = false;

   //Identify the quadrant and set the flag
   if(forbidden.first - start.first < size/2)
   {
      if(forbidden.second - start.second < size/2)
         Q1 = true;
      else 
         Q2 = true;
   }
   else
   {
      if(forbidden.second - start.second < size/2)
         Q3 = true;
      else 
         Q4 = true;
   }

   //Quadrant tracker
   int quad = 1;

   //Tromino is ALWAYS place in the center of the grid/subgrid
   for(int i = start.first + size/2 -1; i <= start.first + size/2; i++)
   {  
      for(int j = start.second + size/2 -1 ; j <= start.second + size/2; j++)
      {
         switch (quad++)
         {
            case 1:           //if in QX
               if (Q1)        //and QX contains the forbidden tile
                  continue;   //then don't change/place tile
               break;
            case 2:
               if (Q2)
                  continue;
               break;
            case 3:
               if (Q3)
                  continue;
               break;
            case 4:
               if (Q4)
                  continue;
               break;
            default:          //Only 4 quadrants, should be impossible
               std::cerr<< "Invalid Quad Number!\n";
               break;
         }

         //Set tile to occupied/'T'
         if(arr[i][j] != 'x' && arr[i][j] != 'T')
            arr[i][j] = 'T';

         //Print coordinates of tile
         std::cout<<i<<","<<j<<"\n";
      }
   }

   printArr(arr, origSize);

   //Recur for each quadrant
   placeTromino(arr, size/2, start,origSize);
   placeTromino(arr, size/2, std::pair<int,int>(start.first, start.second + size/2),origSize);
   placeTromino(arr, size/2, std::pair<int,int>(start.first + size/2, start.second),origSize);
   placeTromino(arr, size/2, std::pair<int,int>(start.first + size/2, start.second + size/2),origSize);
}


int main()
{  
   float powCheck = 0;
   int size = 4;

   while (true)
   {
      do
      {
         std::cout << "Enter a negative number to exit\n";
         std::cout << "Enter size of 2D Array >= 4 and a power of 2: ";
         std:: cin >> size;
         
         if (size < 0)
            return 0;

         //Check for power of 2: https://www.educative.io/answers/how-to-check-if-a-number-is-a-power-of-2-in-cpp
         powCheck = log2(size);
      }while (ceil(powCheck) != floor(powCheck) || size < 4);

      //Random Engine, thank you Dr. Lewis from a CS 415 sample
      std::random_device rd{};
      std::mt19937 gen{rd()};
      std::uniform_int_distribution<int> forbiddenGen(0, size-1);

      //Create Grid
      char** tileset = new char*[size];
      std::cout<<"Creating Board:\n";

      for(int i = 0; i < size; i++)
      {  
         tileset[i] = new char[size];
         for(int j = 0; j <size; j++)
         {
            tileset[i][j] = '.';
            std::cout << tileset[i][j] << " ";
         }
         std::cout <<std::endl;
      }

      std::cout << "Set Forbidden Space:\n";
      tileset[forbiddenGen(gen)][forbiddenGen(gen)] = 'x';

      std::pair<int,int> forbid = findForbid(tileset, std::pair<int,int>(0,0), size);

      //If not found, kill the program
      if (forbid.first == -1)
         return -1;

      printArr(tileset, size);
      std::cout << "Forbidden Tile: (" << forbid.first <<", " << forbid.second << ")\n";

      //Start the game
      placeTromino(tileset, size, std::pair<int,int> (0,0), size);

      //Print results
      for (int i = 0; i < size; i++)
         std::cout << "==";
      std::cout <<"\nFinal Board:\n";
      printArr(tileset,size);

      //Clean up
      deleteArr(tileset, size);
   }
}