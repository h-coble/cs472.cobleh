#include "GraphMaker.hpp"
#include "AdjMatrixGraph.hpp"
#include "AdjListGraph.hpp"

#include <chrono>
#include <iomanip>
#include<math.h>

auto visit = [&] (int n) { std::cout << n << " "; };

double timeSearchList(int numNodes, double prob, GraphMaker maker)
{
    AdjListGraph<int> a = maker.makeAdjListGraph(numNodes, prob);
    auto start = std::chrono::steady_clock::now();
    a.dfs(0, visit);
    auto end = std::chrono::steady_clock::now();

    return (end - start).count() / pow(10, 9);
}

double timeSearchMatrix(int numNodes, double prob, GraphMaker maker)
{
    AdjMatrixGraph<int> a = maker.makeAdjMatrixGraph(numNodes, prob);
    auto start = std::chrono::steady_clock::now();
    a.dfs(--numNodes, visit);
    auto end = std::chrono::steady_clock::now();

    return (end - start).count() / pow(10, 9);
}

int main()
{
    GraphMaker maker;
    const int numOfItems[5] = {2,8,64,256,1000};
    double m, l;
    for (int i = 0; i < 5; i++)
    {
        std::cout << setprecision(4) << fixed;
        
        m = timeSearchMatrix(numOfItems[i], 0.5, maker);
        std::cout << std::endl;
        //l = timeSearchList(numOfItems[i], 0.5, maker);
        std::cout << std::endl;
        std::cout << "\nTime of DFS for " << numOfItems[i] << " items in graph with probability of 0.5\n";
        std::cout << "AdjMatrix: " << setw(10) << std::right << m << "\n";
        //std::cout << "AdjList: " << setw(10) << std::right << l << "\n";
        std::cout << std::endl;
    }
	
    return 0;

}

