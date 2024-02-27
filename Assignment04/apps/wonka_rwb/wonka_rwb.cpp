#include <iostream>
#include <string>

using std::string;


bool rwb_cmp(const char lhs, const char rhs)
{
   if (lhs == 'r')      //rr, rb, rw -> true
      return true;
   else if (rhs == 'b') // rb covered already, wb, bb -> true
      return true;
   else if (rhs == lhs) // ww -> T
      return true;
   else                 //wr, br, bw -> false
      return false;               
}

void rwb_swap(char& a, char& b)
{
   char tmp = a;
   a = b;
   b = tmp;
}

string rwbSort(string str)
{
   unsigned int w_index = 0, b_index=0;

   for (int i =0; i+1 < str.size(); i++)
   {
      //Set index of starting point of w and b candies when found
      if(w_index == 0 && str[i] == 'w' && i!=0)
         w_index = i;
      else if(b_index == 0 && str[i] == 'b' && i!=0)
         b_index = i;  

      if(!rwb_cmp(str[i], str[i+1]))
      {
         switch(str[i])
            {
               case 'w':
                  if (str[i+1] == 'r' && w_index == 0) //first w found, log index for swap point
                     w_index = i+1;

                  rwb_swap(str[i+1], str[w_index]);
                  w_index++;
                  b_index++;
                  i--;
                  break;
               case 'b':
                  if ((str[i+1] == 'r' || str[i+1] == 'w') && b_index == 0) //first b found, log index for swap point
                     b_index = i+1;
                  
                  if(str[i+1] == 'w')
                  {
                     rwb_swap(str[i+1], str[b_index]);
                     b_index++;
                  }
                  else if (str[i+1] == 'r')
                  {
                     rwb_swap(str[i+1], str[w_index]);
                     w_index++;
                     //b_index++;
                  }
                  i--;
                  break;
            }
      }
   }

   return str;
}


int main()
{
   string a = "rwbbwr";
   std::cout << a << " ";
   a = rwbSort(a);
   std::cout << a << std::endl;

   a = "bbbrwrwrrbrbrwbrwbrwbwww";
   std::cout << a << " ";
   a = rwbSort(a);
   std::cout << a << std::endl;

   return 0;
}