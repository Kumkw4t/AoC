#include <vector>
#include <array>
#include <queue>
#include <tuple>
#include <array>
#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>
#include <chrono>

int  solvep1(std::string filename, int part) {

    std::fstream file(filename);
    std::vector<std::vector<std::pair<int,int>>> biggestTree(0);
    std::vector<std::vector<bool>> isVisible;
    std::deque<std::string> lineBuffer;

    int countLine = 0;
    int index = 0;
    int result = 0;

    for (std::string line; std::getline(file,line);) {

        if (line.empty()) break;

        biggestTree.push_back(std::vector<std::pair<int, int>>());
        isVisible.push_back(std::vector<bool>());

        for (int i=0; i<line.length(); i++) {

            biggestTree[countLine].push_back({-1, -1});
            isVisible[countLine].push_back(false);

            // from left
            // std::cout << line[i] << " vs " << biggestTree[countLine][i>0 ? i-1 : i].first << std::endl;
            if ( line[i] > biggestTree[countLine][i>0 ? i-1 : i].first) {
                biggestTree[countLine][i].first = line[i];
                if (isVisible[countLine][i]) continue;
                isVisible[countLine][i] = true;
                result += 1;
                // std::cout << "left: " << line[i] << " visible at [" << countLine << "," << i << "]" << std::endl;
            } else {
                biggestTree[countLine][i].first = biggestTree[countLine][i-1].first;
            }

            // from top
            // std::cout << static_cast<char>(line[i]) << " vs " << static_cast<char>(biggestTree[countLine>0 ? countLine-1 : countLine][i].second) << std::endl;
            if ( (line[i] > biggestTree[countLine>0 ? countLine-1 : countLine][i].second) ){
                biggestTree[countLine][i].second = line[i];
                if (isVisible[countLine][i]) continue;
                isVisible[countLine][i] = true;
                result += 1;
                // std::cout << "top: " << line[i] << " visible at [" << countLine << "," << i << "]" << std::endl;
            } else {
                biggestTree[countLine][i].second = biggestTree[countLine-1][i].second;
            }
        }

        countLine++;

        // save line to buffer for bottom/right
        lineBuffer.push_front(line);
    }

    countLine = 0;
    biggestTree.clear();
    int nbLines = isVisible.size() - 1;
    int tmpTree = 0;
    int part2Index = 0;
    std::vector<int> viewScore(4);

    for (std::string line : lineBuffer) {

        // std::cout << line  << std::endl;
        biggestTree.push_back(std::vector<std::pair<int, int>>());

        for (int i = line.length(); i>0; i--) {
            
            biggestTree[countLine].push_back({-1, -1});
            index = line.length() - i;
            // from right
            // std::cout << "right: " << line[i-1] << " vs " << static_cast<char>(biggestTree[countLine][index>0 ? index-1 : index].first) << std::endl;
            if ( line[i-1] > biggestTree[countLine][index>0 ? index-1 : index].first) {
                biggestTree[countLine][index].first = line[i-1];
                if (!isVisible[nbLines-countLine][i-1]) {
                    isVisible[nbLines-countLine][i-1] = true;
                    result += 1;
                    // std::cout << "right: " << line[i-1] << " visible at [" << nbLines-countLine << "," << i-1 << "]" << std::endl;
                }
            } else {
                biggestTree[countLine][index].first = biggestTree[countLine][index-1].first;
            }

            // from bot
            // std::cout << "bot: " << line[i-1] << " vs " << static_cast<char>(biggestTree[countLine>0 ? countLine-1 : countLine][index].second) << std::endl;
            if ( (line[i-1] > biggestTree[countLine>0 ? countLine-1 : countLine][index].second) ){
                biggestTree[countLine][index].second = line[i-1];
                if (!isVisible[nbLines-countLine][i-1]) {
                    isVisible[nbLines-countLine][i-1] = true;
                    result += 1;
                    // std::cout << "bot: " << line[i-1] << " visible at [" << nbLines-countLine << "," << i-1 << "]" << std::endl;
                }
            } else {
                biggestTree[countLine][index].second = biggestTree[countLine-1][index].second;
            }

            if (part == 2) {

                tmpTree = line[i-1];
                part2Index = i;

                for (int j=1; j<line.length(); j++) {
                    if ((i-1+j) < line.length() && line[i-1+j] <) viewScore[0]++;
                }   
         
                if (viewScore[0]*viewScore[1]*viewScore[2]*viewScore[3] > result) {
                    result = viewScore[0]*viewScore[1]*viewScore[2]*viewScore[3];
                    std::cout << result << " at [" << nbLines-countLine << ',' << i-1 << "]" << std::endl;
                }
            }
        }
        
        countLine++;
    }

    if (part == 2) {

    }

    return result;
}


int main () {

    auto start = std::chrono::high_resolution_clock::now();

    int part = 2;
    int result = solvep1("day8.txt",part);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Message p" << part << ": " << result << std::endl;
    std::cout << "Solving took " << duration.count() << "us" << std::endl;
    return 0;
}
