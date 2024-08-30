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

int  solve(std::string filename, int part) {

    std::fstream file(filename);
    std::vector<std::vector<std::pair<int,int>>> biggestTree(0);
    std::vector<std::vector<bool>> isVisible;
    std::vector<std::string> lineBuffer;

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
            std::cout << line[i] << std::endl;
            if ( (line[i] - 48) > biggestTree[countLine][i>0 ? i-1 : i].first) {
                if (isVisible[countLine][i]) continue;
                isVisible[countLine][i] = true;
                result += 1;
                biggestTree[countLine][i].first = line[i];
                if (!line[i]) std::cout << "coucou" << std::endl;
                std::cout << static_cast<int>(line[i]) << " visible at [" << countLine << "," << i << "]" << std::endl;
            } else {
                biggestTree[countLine][i].first = biggestTree[countLine][i-1].first;
            }

            // from top
            if ( ((line[i] - 48) > biggestTree[countLine>0 ? countLine-1 : countLine][i].second) ){
                if (isVisible[countLine][i]) continue;
                isVisible[countLine][i] = true;
                result += 1;
                biggestTree[countLine][i].second = line[i];
                std::cout << "visible at [" << countLine << "," << i << "]" << std::endl;
            } else {
                biggestTree[countLine][i].second = biggestTree[countLine-1][i].second;
            }
        }

        countLine++;

        // save line to buffer for bottom/right
        lineBuffer.push_back(line);
    }

    return result;
}

int main () {

    auto start = std::chrono::high_resolution_clock::now();

    int part = 2;
    int result = solve("day_test.txt",part);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Message p" << part << ": " << result << std::endl;
    std::cout << "Solving took " << duration.count() << "us" << std::endl;
    return 0;
}
