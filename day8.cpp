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
    int result2 = 0;

    for (std::string line; std::getline(file,line);) {

        if (line.empty()) break;

        biggestTree.push_back(std::vector<std::pair<int, int>>());
        isVisible.push_back(std::vector<bool>());

        for (int i=0; i<line.length(); i++) {

            biggestTree[countLine].push_back({-1, -1});
            isVisible[countLine].push_back(false);

            // from left
            if ( line[i] > biggestTree[countLine][i>0 ? i-1 : i].first) {
                biggestTree[countLine][i].first = line[i];
                if (isVisible[countLine][i]) continue;
                isVisible[countLine][i] = true;
                result += 1;
            } else {
                biggestTree[countLine][i].first = biggestTree[countLine][i-1].first;
            }

            // from top
            if ( (line[i] > biggestTree[countLine>0 ? countLine-1 : countLine][i].second) ){
                biggestTree[countLine][i].second = line[i];
                if (isVisible[countLine][i]) continue;
                isVisible[countLine][i] = true;
                result += 1;
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
    int lineIndex,colIndex = 0;
    bool stop = true;
    std::vector<int> viewScore(4,0);
    std::vector<bool> continueExploration(4,true);

    for (std::string line : lineBuffer) {

        biggestTree.push_back(std::vector<std::pair<int, int>>());

        for (int i = line.length(); i>0; i--) {
            
            biggestTree[countLine].push_back({-1, -1});
            index = line.length() - i;
            // from right
            if ( line[i-1] > biggestTree[countLine][index>0 ? index-1 : index].first) {
                biggestTree[countLine][index].first = line[i-1];
                if (!isVisible[nbLines-countLine][i-1]) {
                    isVisible[nbLines-countLine][i-1] = true;
                    result += 1;
                }
            } else {
                biggestTree[countLine][index].first = biggestTree[countLine][index-1].first;
            }

            // from bot
            if ( (line[i-1] > biggestTree[countLine>0 ? countLine-1 : countLine][index].second) ){
                biggestTree[countLine][index].second = line[i-1];
                if (!isVisible[nbLines-countLine][i-1]) {
                    isVisible[nbLines-countLine][i-1] = true;
                    result += 1;
                }
            } else {
                biggestTree[countLine][index].second = biggestTree[countLine-1][index].second;
            }

            if (part == 2) {

                tmpTree = line[i-1];
                lineIndex = i-1;
                colIndex = countLine;
                viewScore.clear();
                viewScore.resize(4,0);
                continueExploration.clear();
                continueExploration.resize(4,true);

                for (int j=1; j<line.length(); j++) {
                    stop = true;

                    //right
                    if ((lineIndex+j) < line.length() && continueExploration[0]) {
                        viewScore[0]++;
                        stop = false;
                        if (line[lineIndex+j] >= tmpTree) continueExploration[0] = false;
                    }

                    //left
                    if ( ((lineIndex-j) >= 0) && continueExploration[1]) {
                        viewScore[1]++;
                        stop = false;
                        if (line[lineIndex-j] >= tmpTree) continueExploration[1] = false;
                    }

                    //top
                    if ( ((colIndex+j) <= nbLines) && continueExploration[2]) {
                        viewScore[2]++;
                        stop = false;
                        if (lineBuffer[colIndex+j][i-1] >= tmpTree) continueExploration[2] = false;
                    }

                    //bot
                    if ( ((colIndex-j) >= 0) && continueExploration[3] ) {
                        viewScore[3]++;
                        stop = false;
                        if (lineBuffer[colIndex-j][i-1] >= tmpTree) continueExploration[3] = false;
                    }

                    if (stop) break;
                    
                }   
         
                if (viewScore[0]*viewScore[1]*viewScore[2]*viewScore[3] > result2) {
                    result2 = viewScore[0]*viewScore[1]*viewScore[2]*viewScore[3];
                }
            }
        }
        
        countLine++;
    }

    if (part == 1) return result;
    else return result2;
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
