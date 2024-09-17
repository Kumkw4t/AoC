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

int solve (std::string filename, int part) {

    int result = 0;
    std::fstream file(filename);
    int minX, minY;
    std::deque<std::deque<bool>> map;
    int index;

    for (std::string line; getline(file,line);) {

        index = 0;
        while (index < line.length()) {

        }
    }

    return 0;
}

int main () {

    auto start = std::chrono::high_resolution_clock::now();

    int part = 2;
    int result = solve("day13.txt",part);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Message p" << part << ": " << result << std::endl;
    std::cout << "Solving took " << duration.count() << "us" << std::endl;
    return 0;
}
