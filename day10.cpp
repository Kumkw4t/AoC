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

    std::fstream file(filename);
    int result = 0;
    int reg = 1;
    int cycles = 1;
    int step = 1;
    int index = 0;

    std::vector<std::vector<char>> screen;
    screen.push_back(std::vector<char>(40));
    
    for (std::string line; getline(file,line); ) {
        
        if (line.empty() || ( (part == 1) && (cycles > 220) ) ) return result;

        step = line[0] == 'n' ? 1 : 2;

        if ( (part == 1) && ( (cycles+step >= 20) && ( ((cycles-20+step-1) % 40) < step ) ) ) {

            for (int i=0; i<step; i++) {
                if ( (cycles+i == 20) || ( ( (cycles+i-20) % 40 ) == 0 ) ) result += (cycles+i)*reg;
            }

        } else if (part==2) {

            for (int i=0; i<step; i++) {

                if (index >= 40) {
                    index %= 40;
                    screen.push_back(std::vector<char>(40));
                }

                if ( ((index+1) >= reg) && ((index-reg+1) < 3) ) {
                    screen[(int) (cycles-1)/40][index] = '#';
                } else {
                    screen[(int) (cycles-1)/40][index] = '.';
                }

                index++;
            }
        }

        if (step == 2) {
            reg += std::stoi(line.substr(5));
        }

        cycles += step;
    }

    if (part == 2) {
        for (std::vector<char> line : screen) {
            for (char letter : line) {
                std::cout << static_cast<char>(letter);
            }

            std::cout << std::endl;
        }
    }

    return result;
}

int main () {

    auto start = std::chrono::high_resolution_clock::now();

    int part = 2;
    int result = solve("day10.txt",part);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Message p" << part << ": " << result << std::endl;
    std::cout << "Solving took " << duration.count() << "us" << std::endl;
    return 0;
}
