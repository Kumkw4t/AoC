#include <vector>
#include <array>
#include <string>
#include <fstream>
#include <iostream>
#include <chrono>

int solve (std::string fileName) {
    int score;
    std::ifstream file(fileName);
    int result;
    int count = 0;
    for (std::string line; std::getline(file,line);) {

        if (line.empty()) {
            break;
        }
        score += (line[2] - 88)*3;

        result = ((line[0] - 65) + (line[2] + 1) % 3) % 3;
        score += (result + 1);

        // std::cout << line << std::endl;
        std::cout << score << std::endl;
        count++;
    }

    return score;
}

int main () {

    auto start = std::chrono::high_resolution_clock::now();

    int totalScore = solve("day2.txt");

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Score total: " << totalScore << std::endl;
    std::cout << "Solving took " << duration.count()/1000 << "ms" << std::endl;
    return 0;
}
