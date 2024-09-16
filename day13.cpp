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

int sort (std::string line, std::string prevLine) {
    int index = 0;  
    int prevIndex = 0;      
    while ((line[index] != '\0') && (prevLine[prevIndex] != '\0')) {

        if ((line[index] == '[' && prevLine[prevIndex] == '[') 
        || (line[index] == ']' && prevLine[prevIndex] == ']')) {
            // not a number yet or list ended at the same time
            index++;
            prevIndex++;
            continue;
        }

        if ((line[index] == ']') && (prevLine[prevIndex] != ']')) {
            // right pair finished before left, wrong order
            return 0;
        }

        if (prevLine[prevIndex] == ']' && line[index] != ']') {
            // left pair run out before right, good order
            return 1;
        }

        if (line[index] == ',') index++;
        if (prevLine[prevIndex] == ',') prevIndex++;

        if (prevLine[prevIndex] != '[' && prevLine[prevIndex] != ',') {
            // left is number, getting next number or ] in right pair
            while (line[index] == '[') index++;
            if (line[index] != ']') {
                if (std::stoi(line.substr(index)) == std::stoi(prevLine.substr(prevIndex))) {
                    index++;
                    prevIndex++;
                    if (line[index] == '0') index++;
                    if (prevLine[prevIndex] == '0') prevIndex++;
                    continue;
                }
                
                if (std::stoi(line.substr(index)) > std::stoi(prevLine.substr(prevIndex))) {
                    // right order
                    return 1;
                } else {
                    // wrong order
                    return 0;
                }
            }

            continue;
        }

        if (line[index] != '[' && line[index] != ',') {
            // right is number, getting next number or ] in left pair

            while (prevLine[prevIndex] == '[') prevIndex++;
            if (prevLine[prevIndex] != ']') {
                if (std::stoi(line.substr(index)) == std::stoi(prevLine.substr(prevIndex))) {
                    index++;
                    prevIndex++;
                    if (line[index] == '0') index++;
                    if (prevLine[prevIndex] == '0') prevIndex++;
                    continue;
                }
                
                if (std::stoi(line.substr(index)) > std::stoi(prevLine.substr(prevIndex))) {
                    // right order
                    return 1;
                } else {
                    // wrong order
                    return 0;
                }
            }

            continue;
        }
    }

    if (prevIndex == prevLine.length()) return 1;
    return 0;
}

int solve (std::string filename, int part) {

    std::fstream file(filename);
    std::string prevLine;
    int count = -1;
    int index,prevIndex;
    int result = 0;
    std::vector<std::string> sorted;

    for (std::string line; getline(file,line);) {

        count++;
        if (count%3 == 2 || count%3 == 0) {
            prevLine = line;
            continue;
        }

        if (line.empty()) break;

        if (part == 2) {
            sorted.push_back(prevLine);
            sorted.push_back(line);
        }
        
        // compare pair with index (int) count/3 + 1
        if (part == 1) result += sort(line,prevLine)*(((int) count/3)+1);
    }

    if (part == 1) return result;

    sorted.push_back("[[2]]");
    sorted.push_back("[[6]]");

    // simple bubble sort
    std::string tmp;
    for (int i=0; i<sorted.size()-1;i++) {
        for (int j=0; j<sorted.size()-i-1;j++) {
            if (sort(sorted[j],sorted[j+1])) {
                tmp = sorted[j];
                sorted[j] = sorted[j+1];
                sorted[j+1] = tmp;
            }
        }
    }

    count = 1;
    result = 1;
    for (std::string line : sorted) {
        if ( (line.find("[[2]]") == 0) || (line.find("[[6]]") == 0)) {
            result *= count;
        }
        count++;
    }

    return result;
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
