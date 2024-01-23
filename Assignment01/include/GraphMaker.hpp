#pragma once
#include<cstdlib>
#include "AdjMatrixGraph.hpp"
#include "AdjListGraph.hpp"
#include <time.h> 
#include <vector>
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
        srand(time(0));
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
            a->addNode(numberOfNodes);
            
            for(int j =0; j <i;j++)
            {
                if(((double)rand()/0.99) > edgeProbability)
                {
                    a->addEdge(i,j);
                }  
            }      
        }
        m.push_back(a);
        return *a;
    }

    AdjListGraph<int> & makeAdjListGraph(int numberOfNodes, double edgeProbability)
    {
        AdjListGraph<int>* a = new AdjListGraph<int>;
        for (int i =0;i<numberOfNodes;i++)
        {
            a->addNode(numberOfNodes);
            
            for(int j =0; j < i;j++)
            {
                if(((double)rand()/0.99) > edgeProbability)
                {
                    a->addEdge(i,j);
                }  
            }      
        }

        l.push_back(a);
        return *a;
    }
    
};
