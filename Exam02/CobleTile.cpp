/*
    Begrudgingly, this comes from our friend, the oracle, ChatGPT. I didn't know where to start with this problem 
    because I was confused by the directions and had a hard time finding resources. (Funny enough I found sources for
    what we called the tromino problem, but I have a feeling you knew that would happen when looking for "divide and conquer tiling problem").
    
    When verifying this code, I found that the issue lies in the swap. When swapping, the code seemingly assumes that it is getting the missing 
    color it needs without checking. I don't know what should be done to alleviate this. I tried making changes and started from scratch several times, 
    but all of those attempts yielded code that worked 0% of the time. Because of that and spending much more time than I believe necessary, 
    this is my submission. 
    
    As always, please be gentle when grading.
    -HC
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to rearrange the tiles
void rearrangeTiles(vector<vector<char>>& tiles) {
    int n = tiles[0].size();
    
    // Loop through each column
    for (int col = 0; col < n; col++) {
        // Count the number of red, white, and blue tiles in this column
        int redCount = 0, whiteCount = 0, blueCount = 0;
        for (int row = 0; row < 3; row++) {
            if (tiles[row][col] == 'R')
                redCount++;
            else if (tiles[row][col] == 'W')
                whiteCount++;
            else if (tiles[row][col] == 'B')
                blueCount++;
        }

        
        // If any color is missing, find a row where that color is present and swap it
        if (redCount == 0) {
            for (int row = 0; row < 3; row++) {
                if (whiteCount > 1) {
                    if (tiles[row][col] == 'W') {
                        swap(tiles[row][col], tiles[row][(col + 1) % n]);
                        whiteCount--;
                        redCount++;
                    }
                }
                if (blueCount > 1) {
                    if (tiles[row][col] == 'B') {
                        swap(tiles[row][col], tiles[row][(col + 1) % n]);
                        blueCount--;
                        redCount++;
                    }
                }
            }
        }
        if (whiteCount == 0) {
            for (int row = 0; row < 3; row++) {
                if (redCount > 1) {
                    if (tiles[row][col] == 'R') {
                        swap(tiles[row][col], tiles[row][(col + 1) % n]);
                        redCount--;
                        whiteCount++;
                    }
                }
                if (blueCount > 1) {
                    if (tiles[row][col] == 'B') {
                        swap(tiles[row][col], tiles[row][(col + 1) % n]);
                        blueCount--;
                        whiteCount++;
                    }
                }
            }
        }
        if (blueCount == 0) {
            for (int row = 0; row < 3; row++) {
                if (redCount > 1) {
                    if (tiles[row][col] == 'R') {
                        swap(tiles[row][col], tiles[row][(col + 1) % n]);
                        redCount--;
                        blueCount++;
                    }
                }
                if (whiteCount > 1) {
                    if (tiles[row][col] == 'W') {
                        swap(tiles[row][col], tiles[row][(col + 1) % n]);
                        whiteCount--;
                        blueCount++;
                    }
                }
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter the number of columns: ";
    cin >> n;

    // Initialize the tiles
    vector<vector<char>> tiles(3, vector<char>(n));

    // Fill the tiles with colors
    cout << "Enter the colors of tiles (R - red, W - white, B - blue):" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < n; j++) {
            cin >> tiles[i][j];
        }
    }

    // Rearrange the tiles
    rearrangeTiles(tiles);

    // Output the rearranged tiles
    cout << "Rearranged tiles:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < n; j++) {
            cout << tiles[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
