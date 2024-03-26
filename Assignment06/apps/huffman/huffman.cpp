#include <string>   //stoi for 
#include <bitset>   //bitset/bitstring for encoding/decoding
#include <queue>    //Prioritty queue heap for tree building
#include <map>      //Frequency table?
#include <memory>   //Less pointer headaches
class HuffmanTree
{
    private:
        node root;
    public:
        HuffmanTree(node r): root(r) {};
};

struct node
{
    int freq = 0;
    char chracter = ' ';    //Unsigned?

    //weak_ptr?
    std::shared_ptr<node> left = nullptr;
    std::shared_ptr<node> right = nullptr;
    std::shared_ptr<node> parent = nullptr;

    //Overload for priority queue
    bool operator< (node rhs)
    {
        return freq > rhs.freq;     //> to heapify
    }
};