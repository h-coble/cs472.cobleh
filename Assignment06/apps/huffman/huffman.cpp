#include "HuffmanTree.hpp"


int main()
{
    //std::map <char , int> a = buildFreqTable("racecar.txt");

    auto ht = HuffmanTree("racecar.txt");
    ht.encodeFile();
    return  0;

}

