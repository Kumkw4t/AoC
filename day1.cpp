#include <vector>
#include <array>
#include <string>
#include <fstream>
#include <iostream>

std::vector<std::string> loadData (std::string fileName) {
    std::vector<std::string> data;
    std::ifstream file(fileName);
    for (std::string line; std::getline(file,line);) {
        data.push_back(line);
    }
    return data;
}

int main () {
    std::vector<std::string> input = loadData("day1.txt");
    std::array<int,3> maxCalories = {0,0,0};
    std::vector<int> elvesCalories =  {0};
    int index;


    for (std::string line : input) {
        if (line.empty()) {
            index = -1;
            while ( (elvesCalories.back() > maxCalories[index+1]) && (index < 2) ) {
                index++;
                if (index > 0) {
                    maxCalories[index-1] = maxCalories[index];
                }
                maxCalories[index] = elvesCalories.back();
            }

            // std::cout << elvesCalories.back() << " vs " << maxCalories << std::endl;
            elvesCalories.push_back(0);
            continue;
        }

        elvesCalories.back() += std::stoi(line);
    }

    int maxCal = maxCalories[0] + maxCalories[1] + maxCalories[2];
    std::cout << maxCal << std::endl;
}