//
//  File:   AdjListGraph.hpp
//  Author: Your Glorious Instructor
//  Purpose:
//  Implementation of the adjacency list implementation of the graph ADT
//

#include "Graph.hpp"
#include <unordered_map>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <stack>
#include <queue>
#include <functional>

using namespace std;

template <class N>
class AdjListGraph: public Graph<N>  {
private:
    using Edges = list<pair<N, N>>;
    unordered_map<N, Edges > vertexMap;       //Already a map, not a vector?

    //NEW
    vector<N> nodeVec;
public:
    // Default constuctor, create empty
    AdjListGraph() : Graph<N>() { };
    
    // Get the vertex map from the Graph we're copying
    AdjListGraph(const AdjListGraph& other) : Graph<N>()
    {
        vertexMap = other->vertexMap;
    }
    
    // Don't forget to overload the assignment operator
    AdjListGraph& operator= (const AdjListGraph &source)
    {
        vertexMap = source->vertexMap;
        return *this;
    }
    
    // Add the nodes in the list to graph
    AdjListGraph(vector<N> newNodes, vector<pair<N,N>> newEdges) :
    Graph<N>(newNodes, newEdges)
    {
        for (auto it = newNodes.begin();
             it < newNodes.end();
             ++it)
        {
            N node = *it;
            vertexMap[node].push_back(newEdges);
        }
    }
    
    
    // Clean up behind ourselves
    ~AdjListGraph() { }
    
    virtual bool adjacent(N x, N y){
        Edges edges = vertexMap.at(x);
        pair<N,N> *searchEdge = new pair<N,N>(x,y);
        typename Edges::const_iterator begin = edges.begin();
        typename Edges::const_iterator end = edges.end();
        auto pos = std::find_if(begin,end,
                                [&](pair<N,N> const &b) {
            bool match =  (b.first == searchEdge->first
                           && b.second == searchEdge->second);
            return match;
        });
        bool match = false;
        if (pos != end) { match = true; }
        return (match);
    }
    
    virtual vector<N> neighbors(N x) {
        vector<N> *nodes = new vector<N>();
        Edges edges = vertexMap.at(x);
        for (typename Edges :: const_iterator it = edges.begin(); it != edges.end(); it++) {
            pair<N,N> e = *it;
            nodes->push_back(e.second);
        }
        return *nodes;
    }
    
    virtual void addNode(N node){
        Edges * newEdgeList = new Edges();
        vertexMap[node] = *newEdgeList;

        //NEW
        nodeVec.push_back(node);
    }
    
    virtual void addEdge(N x, N y){
        pair<N,N> forwardEdge = make_pair(x,y);
        pair<N,N> backwardEdge = make_pair(y,x);
        Edges edgeList = vertexMap[x];
        edgeList.push_back(forwardEdge);
        vertexMap[y].push_back(backwardEdge);
    }
    
    virtual void deleteEdge(N x, N y){
        pair<N,N> forwardEdge = make_pair(x,y);
        pair<N,N> backwardEdge = make_pair(y,x);
        vertexMap[x].remove(forwardEdge);
        vertexMap[y].remove(backwardEdge);
    }
    
    // Traversals
    void dfs(N startNode, std::function<void(N)> visit) {
        map<N, bool> visited;
        stack<N> s;
        for (auto v : vertexMap) {
            visited[v.first] = false;
        }
        s.push(startNode);
        while (!s.empty()) {
            N currentNode = s.top();
            s.pop();
            bool beenVisited = visited[currentNode];
            if (!beenVisited) {
                visit(currentNode);
                visited[currentNode] = true;
            }
            vector<N> neighVec = neighbors(currentNode);
            for (auto neighbor: neighVec ) {
                if (!visited[neighbor]) { s.push(neighbor); }
            }
        }
    }
    
    void bfs(N startNode, std::function<void(N)> visit) {
        map<N, bool> visited;
        for (auto v: vertexMap) {
            visited[v.first] = false;
        }
        queue<N> q;
        q.push(startNode);
        while (!q.empty()) {
            N currentNode = q.front();
            q.pop();
            bool beenVisited = visited[currentNode];
            if (!beenVisited) {
                visit(currentNode);
                visited[currentNode] = true;
            }
            vector<N> neighVec = neighbors(currentNode);
            for (auto neighbor: neighVec) {
                if (!visited[neighbor]) { q.push(neighbor); }
            }
        }
    }
};
