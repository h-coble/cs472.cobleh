#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

/*
    I was very confused by the wording of the problem, so I asked chatGPT to give a possible solution.
    It was not immediately clear that the 10 sublists and "piles" referred to the same structure, and I
    believe that to have been the root of my confusion. I've tested the code and read through it to
    make sure it is doing what's been asked. Comments made by me to explain the process are initialed.
    I'm disappointed because I definitely could've written this by myself if I was clear on the purpose of
    each part of the algorithm, but I spoiled it for myself, so any rewritten solution would be based on this
    anyways. -HC
*/

// Function to perform sorting using the described algorithm
void customSort(vector<int>& arr) {
    // Define ten sublists
    vector<vector<int>> piles(10);

    //Each index represents the digit in the place for the pass.
    //For example, [0] on the first pass contains all numbers whose right-most digit is 0.
    //On the second, it contains all numbers with a 0 in the tens place. -HC

    // Find the maximum number of digits in the array
    int maxDigits = 0;
    for (int num : arr) {
        maxDigits = max(maxDigits, (int)to_string(num).length());
        //By converting num to a string, we can use the length() method to get the number of digits.
        //length() returns size_t, so it's casted to an int to use with the max() method. -HC
    }

    // Iterate through each digit position from right to left
    for (int digitPos = 0; digitPos < maxDigits; ++digitPos) {
        // Place numbers into piles based on the current digit
        for (int num : arr) {
            
            //Dividing num by 10^digitPos inspects digits right to left
            //This portion of the code finds the digit in the position for the pass, 
            //then places the number to the correct pile for the pass. -HC
            
            int digit = (num / static_cast<int>(pow(10, digitPos))) % 10;
            piles[digit].push_back(num);
        }

        // Clear the original array for reordering
        arr.clear();

        // Traverse the piles in sequential order, appending to the original array
        for (int i = 0; i < 10; ++i) {
            for (int num : piles[i]) {
                arr.push_back(num);         //Iterating left to right and using push_back ensures that entries from left-most pile stay on the left.
            }                               //arr has leftmost pile first, right-most last as a result, repeats until all digits are inspected. -HC
            piles[i].clear();
        }
    }
}

int main() {
    vector<int> arr = {170, 45, 75, 90, 802, 24, 2, 66};
    
    cout << "Original array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    customSort(arr);

    cout << "Sorted array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
