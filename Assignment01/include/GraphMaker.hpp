#pragma once
#include<cstdlib>
#include "AdjMatrixGraph.hpp"
#include "AdjListGraph.hpp"
#include <vector>
#include<random>
using namespace std;

class GraphMaker
{
private:
    vector<AdjMatrixGraph<int>*> m;
    vector<AdjListGraph<int>*> l;
public:
    // Default constuctor, create empty
    GraphMaker()
    {
    }
    ~GraphMaker()
    {
        for (int i=0;i < m.size(); i++)
        {
            delete m[i];
        }
        for (int i = 0; i < l.size(); i++)
        {
            delete l[i];
        }
    }
    AdjMatrixGraph<int> & makeAdjMatrixGraph(int numberOfNodes, double edgeProbability)
    {
        AdjMatrixGraph<int>* a = new AdjMatrixGraph<int>;
        for (int i =0;i<numberOfNodes;i++)
        {
            //Needed some help with [0,1) random
            //https://www.geeksforgeeks.org/generate-random-double-numbers-in-cpp/

            double lower_bound = 0;
            double upper_bound = 1;
            uniform_real_distribution<double> unif(lower_bound, upper_bound);
            default_random_engine re;
            double random_double;
            
            a->addNode(i);
            
            for(int j =0; j <i;j++)
            {
                random_double = unif(re);
                if (random_double > edgeProbability)
                {
                    a->addEdge(i, j);
                }
            }      
        }
        m.push_back(a);
        return *a;
    }

    AdjListGraph<int> & makeAdjListGraph(int numberOfNodes, double edgeProbability)
    {
        double lower_bound = 0;
        double upper_bound = 1;
        uniform_real_distribution<double> unif(lower_bound, upper_bound);
        default_random_engine re;
        double random_double;

        AdjListGraph<int>* a = new AdjListGraph<int>;
        for (int i =0;i<numberOfNodes;i++)
        {
            a->addNode(i);
            
            for(int j =0; j < i;j++)
            {
                random_double = unif(re);
                if( random_double > edgeProbability)
                {
                    a->addEdge(i,j);
                }  
            }      
        }

        l.push_back(a);
        return *a;
    }
    
};
