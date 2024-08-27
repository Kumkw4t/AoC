#include <vector>
#include <array>
#include <string>
#include <fstream>
#include <iostream>
#include <chrono>

std::pair<int,int> solve(std::string filename) {

    std::fstream file(filename);
    std::pair<int,int> pair1(0,0);
    std::pair<int,int> pair2(0,0);
    int index,indexMid = 0;
    int count = 0;
    std::pair<int,int> result(0,0);

    for (std::string line; std::getline(file,line);) {

        if (line.empty()) {
            break;
        }

        std::cout << line << std::endl;

        indexMid = line.find(",");
        index = line.find("-");

        pair1.first = std::stoi(line.substr(0,index));
        pair1.second = std::stoi(line.substr(index+1,indexMid-index));

        index = line.rfind("-");
        pair2.first = std::stoi(line.substr(indexMid+1, index-indexMid));
        pair2.second = std::stoi(line.substr(index+1,line.length()-index-1));


        if ( ((pair2.second - pair1.second)^(pair2.first - pair1.first)) < 0) {
            result.first += 1;
        } else if ( ((pair2.second - pair1.second) == 0) || ((pair2.first - pair1.first) == 0) ) {
            result.first += 1;
        }

        if ( (pair1.second < pair2.first) || (pair1.first > pair2.second) ) {
            continue;
        } else {
            result.second++;
        }

        std::cout << result.second << std::endl;
        count++;
    }

    return result;
}

int main () {

    auto start = std::chrono::high_resolution_clock::now();

    std::pair<int,int> totalScore = solve("day4.txt");

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Score total p1: " << totalScore.first << std::endl;
    std::cout << "Score total p2: " << totalScore.second << std::endl;
    std::cout << "Solving took " << duration.count() << "us" << std::endl;
    return 0;
}