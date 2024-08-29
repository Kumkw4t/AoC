#include <vector>
#include <array>
#include <queue>
#include <tuple>
#include <string>
#include <fstream>
#include <iostream>
#include <chrono>

int solve(std::string filename, int part) {
    int result = 0;
    int mod = part == 1 ? 4 : 14;
    std::vector<char> marker(mod,' ');

    std::string line;
    std::fstream file(filename);
    std::getline(file,line);

    int curPos = 0;
    std::vector<bool> blockingLetters(mod,false);
    bool correctMarker = true;

    for (char letter : line) {

        result++;
        blockingLetters[curPos] = false;
        correctMarker = true;

        for (int i=1; i<mod; i++) {
            if ((letter == marker[(curPos+i)%mod]) && (!blockingLetters[(curPos+i)%mod])) {
                blockingLetters[(curPos+i)%mod] = true;
                correctMarker = false;
            }
        }

        for (bool block : blockingLetters) {
            if (block) {
                correctMarker = false;
            }
        }

        if (marker.back() == ' ' ) {
            correctMarker = false;
        }

        marker[curPos] = letter;
        curPos = (curPos+1)%mod;

        if (correctMarker) {
            return result;
        }
    }

    return result;
}

int main () {

    auto start = std::chrono::high_resolution_clock::now();

    int part = 2;
    int result = solve("day6.txt",part);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Message p" << part << ": " << result << std::endl;
    std::cout << "Solving took " << duration.count() << "us" << std::endl;
    return 0;
}
