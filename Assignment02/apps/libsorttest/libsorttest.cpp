#include <iostream>
#include <chrono>
#include <iomanip>
#include <random>
#include <algorithm>
#include <vector>


void GenerateRandomDataSet(std::vector<int> dataset, unsigned int size)
{
   //Set up
   int lower_bound = 0;
   int upper_bound = 100000;
   std::uniform_int_distribution<int> unif(lower_bound, upper_bound);
   std::default_random_engine re;

   for(int i=0;i< size; i++)
       dataset.push_back(unif(re));

   auto start = std::chrono::steady_clock::now();
   std::sort(dataset.begin(), dataset.end());
   auto end = std::chrono::steady_clock::now();

   std::cout << "Time to sort an array of " << size << " elements: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds\n";

   dataset.clear();
}
int main()
{
   std::vector<int> dataset;

   GenerateRandomDataSet(dataset,5);
   GenerateRandomDataSet(dataset, 10);
   GenerateRandomDataSet(dataset,100);
   GenerateRandomDataSet(dataset, 500);
   GenerateRandomDataSet(dataset,1000);
   GenerateRandomDataSet(dataset, 5000);
   GenerateRandomDataSet(dataset,100000);

   system("pause");
   
}