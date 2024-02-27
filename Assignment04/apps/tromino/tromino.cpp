#include <iostream>
#include <random>

int sizeG;


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
   //throw std::runtime_error("Forbidden tile not found.");
}

void placeTromino(char** arr, unsigned int size, std::pair<int,int> start)
{
   //Base Case
   if (size <= 1)
      return;
   std::pair<int,int> forbidden = findForbid(arr, start, size);
   bool Q1 = false, Q2 = false, Q3 = false, Q4 = false;

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

   int quad = 1;
   for(int i = start.first + size/2 - 1; i <= start.first + size/2; i++)
   {  
      for(int j = start.second + size/2 -1 ; j <= start.second + size/2; j++)
      {
         switch (quad++)
         {
            case 1:
               if (Q1)
                  continue;
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
            default:
               std::cerr<< "Invalid Quad Number!\n";
               break;
         }
         
         if(arr[i][j] != 'x')
            arr[i][j] = 'T';
         std::cout<<i<<","<<j<<"\n";
      }
   }

   std::cout << "Placed a Tromino.\n";

   printArr(arr, sizeG);
   //Recur for each quadrannt
   placeTromino(arr, size/2, start);
   placeTromino(arr, size/2, std::pair<int,int>(0, size/2));
   placeTromino(arr, size/2, std::pair<int,int>(size/2, 0));
   placeTromino(arr, size/2, std::pair<int,int>(size/2, size/2));

}

void placeTromino(char** arr, std::pair<int,int> start, std::pair<int,int> end)
{
   int size = end.first - start.first;

   if (size == 1)
      return;
   std::pair<int,int> forbidden = findForbid(arr, start, size);
   bool Q1 = false, Q2 = false, Q3 = false, Q4 = false;

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


}


int main()
{
   int size = 4;

   std::cout << "Enter size of 2D Array >= 4 and a power of 2: ";
   std:: cin >> sizeG;
   size = sizeG;

   std::random_device rd{};
   std::mt19937 gen{rd()};
   std::uniform_int_distribution<int> forbiddenGen(0, size-1);

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
   //tileset[forbiddenGen(gen)][forbiddenGen(gen)] = 'x';
   tileset[7][7]='x';
   std::pair<int,int> forbid = findForbid(tileset, std::pair<int,int>(0,0), size);
   printArr(tileset,size);
   std::cout << "Forbidden Tile: (" << forbid.first <<", " << forbid.second << ")\n";
   placeTromino(tileset, size, std::pair<int,int> (0,0));
   for (int i = 0; i < size; i++)
      std::cout << "==";
   printArr(tileset,size);
   deleteArr(tileset, size);
}