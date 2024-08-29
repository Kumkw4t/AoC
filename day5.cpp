#include <vector>
#include <array>
#include <deque>
#include <tuple>
#include <string>
#include <fstream>
#include <iostream>
#include <chrono>

std::string solvep1(std::string filename, int part) {

    std::string message("");
    std::fstream file(filename);
    bool flag = false;
    int curPos = 0;
    int crateIndex = 0;
    int count = 0;
    int countMoves = 0;
    std::vector<std::deque<char>> crates(9);

    std::pair<int,int> movingCrates(0,0);
    int moves = 0;

    for (std::string line; std::getline(file,line);) {

        if (line.empty()) {
            if (flag) break;
            flag = true;
            continue;
        }
            
        if ( !flag ) {
            curPos = line.find("[",0) + 1;
            while (curPos != 0) {
                crateIndex = ((curPos-1)/4);
                crates[crateIndex].push_back(line[curPos]);
                curPos = line.find("[",curPos) + 1;
            }
        }

        if (flag) {
            // process movements
            curPos = 5;
            moves = std::stoi(line.substr(curPos,line.length() - 5));
            curPos = 12;
            if ( moves > 9 ) curPos++; //if number takes two spaces instead of 1

            movingCrates.first = std::stoi(line.substr(curPos,1)); // starting crate
            movingCrates.second = std::stoi(line.substr(curPos+5,1)); // ending crate

            if (part == 1) {
                
                while (moves > 0) {
                    crates[movingCrates.second-1].push_front(crates[movingCrates.first-1].front());
                    crates[movingCrates.first-1].pop_front();
                    moves--;
                }

            } else if (part == 2) {
                crates[movingCrates.second-1].insert(crates[movingCrates.second-1].cbegin(),
                                                    crates[movingCrates.first-1].cbegin(),
                                                    crates[movingCrates.first-1].cbegin()+moves);
                while (moves > 0) {
                    crates[movingCrates.first-1].pop_front();
                    moves--;
                }
            }
            countMoves++;
        }
        count++;
    }

    for (int i = 0; i < crates.size(); i++) {
        message.push_back(crates[i].front());
    }

    return message;
}

int main () {

    auto start = std::chrono::high_resolution_clock::now();

    int part = 2;
    std::string result = solvep1("day5.txt",part);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Message p" << part << ": " << result << std::endl;
    std::cout << "Solving took " << duration.count() << "us" << std::endl;
    return 0;
}
