//Note to Dr. Lewis: 
//The best day of my life will be the one that Mr. Wonka retires.
#include <vector>
#include <algorithm>
#include <iostream>
#include <utility>
#include <stack>
using std::vector;
int robotCollection(vector<vector<bool>> tiles, vector<std::pair<int,int>>& pathVec)
{
    int maxCoins=-1;
    vector<vector<int>> F (tiles.size(), vector<int> (tiles[0].size(), 0));

    //Linear, x2 insignificant impact on O
    for(int i =0; i< tiles.size(); i++)
        F[0][i] = 0;
    for(int j = 0; j < tiles[0].size(); j++)
        F[j][0] = 0; 
    


    //Make table
    for(int i =0; i< tiles.size(); i++)
        for(int j = 1; j < tiles[0].size(); j++)
        {
            F[j][i] = std::max(F[j][i-1], F[j-1][i]) + tiles[j][i];
        }

    /*
        The nested for-loops above limit the performance of this algorithm. 
        O(n * m), not O(n), not O(n^2)

        n and m are both variables; the number of rows doesn't have to be the same
        as the number of columns. This prevents the case that O(n) since m isn't constant,
        and doesn't necessarily imply O(n^2) due to the nature of the variable m. Consider m = n^2:
        the implication then is O(n^3).

        TLDR: O(n*m)
    */


    //These print the 2D Vectors showing where the coins are and the table of #of coins
    //They aren't essential for the problem, so I didn't factor them into my analysis, but
    //the result would still reduce to O(n*m)
    for(int i =0; i< tiles.size(); i++)
    {   for(int j = 0; j < tiles[0].size(); j++)
        {
            std::cout << tiles[j][i] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

    for(int i =0; i< F.size(); i++)
    {   for(int j = 0; j < F[0].size(); j++)
        {
            std::cout << F[j][i] << " ";
        }
        std::cout << std::endl;
    }


    //Get the path
    std::stack<std::pair<int,int>> path;
    int j = tiles[0].size() -1, i = tiles.size()-1;
    maxCoins = F[j][i];
    //While subscripts-1 are valid aka >=0
    //Impact on O: repeats a max of n + m which is < n * m from before
    //Algorithm reduces to O(n*m) still
    while (j != 0 || i != 0)
    {
        path.push(std::pair<int,int>(j,i));
        //Go left if possible, else go right if possible
        if(F[j][i-1] > F[j-1][i])
            if(i != 0)
                i--;
            else
                j--;
        else
            if(j != 0)
                j--;
            else
                i--;
    }
    //push 0,0
    path.push(std::pair<int,int>(j,i));

    pathVec.clear();

    //Linear, no significant impact on O
    while(!path.empty())
    {
        pathVec.push_back(path.top());
        path.pop();
    }

    return maxCoins;
}

int main()
{
    vector<std::pair<int,int>> path;
    vector<vector<bool>> x = {
        {0,0,0,0,1,0}, 
        {0,0,1,0,0,0}, 
        {1,0,0,0,0,1},
        {0,1,0,1,0,0},
        {0,0,1,0,1,0},
        {1,0,0,0,0,1} };

    std::cout << "Max # of coins is " << robotCollection(x, path) << std::endl;
    for(int i = 0; i < path.size(); i++)
        std::cout << path[i].first << ", " << path[i].second << std::endl;
}