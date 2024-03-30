#include <string>   //stoi for 
#include <bitset>   //bitset/bitstring for encoding/decoding
#include <queue>    //Prioritty queue heap for tree building
#include <map>      //Frequency table?
#include <memory>   //Less pointer headaches
#include <fstream>
#include <iostream>

#include <stack>    //Used in encoding characters from node -> root. Encoding is read root -> node, L - > R.

int ID = 0;

class HuffmanTree
{
    public:
        struct node
        {
            int freq = 0;
            char character = '\0';    //Unsigned?
            int id = ID++;

            //weak_ptr?
            std::shared_ptr<node> left = nullptr;
            std::shared_ptr<node> right = nullptr;
            std::shared_ptr<node> parent = nullptr;

            //Overload for priority queue
            bool operator< (const node& rhs) const
            {
                return freq > rhs.freq;     //> to heapify
            }
            bool operator == (const node& rhs) const
            {
                return id == rhs.id;
            }
            bool isLeaf()
            {
                return left == nullptr && right == nullptr;
            }
        };

    private:
        node root;
        std::string filename;
        //Prevent public default constructor
        HuffmanTree();

        std::map<char,int> buildFreqTable(std::string filename)
        {
            char temp;
            std::ifstream fileIn;
            fileIn.open(filename);
            std::map<char, int> freqTable;
            while(fileIn >> temp)
            {
                auto charItr = freqTable.find(temp);
                if(charItr == freqTable.end())
                    freqTable.insert({temp, 1});
                else
                    freqTable.at(temp)++;
            }

            fileIn.close();
            return freqTable;
        }


        bool find(char target, node& targetNode)
        {
            bool found = false;
            if(root.left->character == target)
            {
                //Found
                targetNode = *root.left;
                return true;
            }
            else if (root.right->character == target)
            {
                //Found
                targetNode = *root.right;
                return true;
            }


            if (!root.right->isLeaf())
            {
                //findInner is recursive search
                if(findInner(target, root.right, targetNode))
                {
                    found = true;
                }
            }
            if(!root.left->isLeaf())
            {
                if(findInner(target, root.left, targetNode))
                    found = true;
            }


            if(!root.left->isLeaf() || !root.right->isLeaf())
                return found;
            else
                return false;
        }

        bool findInner(char target, std::shared_ptr<node> startingNode, node& targetNode)
        {
            if(!startingNode->isLeaf())
            {
                return findInner(target, startingNode->left, targetNode)
                    || findInner(target, startingNode->right, targetNode);
            }
            else if(startingNode->character == target)
            {
                targetNode = *startingNode;
                return true;
            }
            else
                return false;
        }


    public:
        HuffmanTree(std:: string file)
        {
            filename = file;

            std::priority_queue<node> pq;
            std::map<char,int> freqTable = buildFreqTable(filename);
            auto mapItr = freqTable.begin();
            while (mapItr != freqTable.end())
            {
                node tempNode;
                tempNode.character =  mapItr -> first;
                tempNode.freq = mapItr -> second;
                pq.push(tempNode);
                ++mapItr;
            }
            
            while (pq.size() > 1)
            {
                node n1 = pq.top();
                pq.pop();
                node n2 = pq.top();
                pq.pop();
                std::shared_ptr<node> p1;
                node newNode;

                newNode.freq = n1.freq + n2.freq;

                n1.parent = std::make_shared<node>(newNode);
                n2.parent = std::make_shared<node>(newNode);

                newNode.left = std::make_shared<node>(n1);
                newNode.right = std::make_shared<node>(n2);

                pq.push(newNode);
            }
            if(pq.size() != 1)
                std::cerr << "Error making tree\n";
            else
                root = pq.top();
        }


        void encodeFile()
        {
            std::ifstream fileIn(filename);
            std::ofstream fileOut("HuffmanCode.txt");
            char temp;
            while(fileIn >> temp)
            {   
                std::stack<int> charStack;
                node foundNode, prevNode;

                find(temp, foundNode);

                while(foundNode.parent != nullptr)
                {
                    prevNode = foundNode;
                    foundNode = *(foundNode.parent);    //set foundNode to be its parent
                    //all pointers in foundNode are null for some reason; couldn't find out how to prevent/fix this
                    //while still using shared_ptr. I'm assuming it has to do with how the = operator is written for them.
                    if(prevNode == *foundNode.left)     
                    {
                        charStack.push(0);
                    }
                    else
                        charStack.push(1);
                }

                while(!charStack.empty())
                {
                    fileOut << charStack.top();
                    charStack.pop();
                }
            }

            fileOut.close();
            fileIn.close();
        }

        void decodeFile()
        {
            //Read every character from file 
            //if character = 0, go to left child, else go to right
            //if that node is a leaf, record the character, go back to root
            //else repeat until it is a leaf
        }
};