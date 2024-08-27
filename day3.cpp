#include <vector>
#include <array>
#include <string>
#include <fstream>
#include <iostream>
#include <chrono>

int findLetterPrio(std::string line) {
    int letterPrio = 0;
    int size = line.length();
    std::string firstCompartment = line.substr(0,size/2);
    std::string secondCompartment = line.substr(size/2, size/2);

    unsigned long long bufFirst = 0ULL;
    unsigned long long bufSecond = 0ULL;

    char curFirst, curSecond;

    for (int i = 0; i < size/2; i++) {
        curFirst = firstCompartment[i] > 90 ? firstCompartment[i] - 97 : firstCompartment[i] - 39;
        curSecond = secondCompartment[i] > 90 ? secondCompartment[i] - 97 : secondCompartment[i] - 39;


        if ( (((unsigned long long) 1 << curFirst)&bufSecond) != 0 ) {
            letterPrio = curFirst+1;
            break;
        } else if ((((unsigned long long) 1 << curSecond)&bufFirst) != 0 ) {
            letterPrio = curSecond+1;
            break;
        } else if ( curFirst == curSecond ) {
            letterPrio = curSecond+1;
            break;            
        }

        bufFirst |= ((unsigned long long) 1<<curFirst);
        bufSecond |= ((unsigned long long) 1<<curSecond);
    }
    return letterPrio;
}

int solvep1 (std::string fileName) {
    int score;
    std::ifstream file(fileName);
    int result;
    int count = 0;
    for (std::string line; std::getline(file,line);) {

        if (line.empty()) {
            break;
        }

        result = findLetterPrio(line);
        score += result;
        count++;
    }

    return score;
}

int findGroupPrio(std::vector<std::string> group) {

    int prio = 0;
    unsigned long long bufFirst = 0ULL;
    unsigned long long bufSecond = 0ULL;
    unsigned long long bufThird = 0ULL;

    char curFirst, curSecond, curThird;

    int size0 = group[0].length();
    int size1 = group[1].length();
    int size2 = group[2].length();

    int maxSize = std::max(std::max(size0,size1),size2);

    for (int i = 0; i < maxSize; i++) {

        if (i < size0) curFirst = group[0][i] > 90 ? group[0][i] - 97 : group[0][i] - 39;
        if (i < size1) curSecond = group[1][i] > 90 ? group[1][i] - 97 : group[1][i] - 39;
        if (i < size2) curThird = group[2][i] > 90 ? group[2][i] - 97 : group[2][i] - 39;

        if ( (((unsigned long long) 1 << curFirst)&bufSecond) != 0 && (((unsigned long long) 1 << curFirst)&bufThird) != 0) {
            prio = curFirst+1;
            break;
        } else if ((((unsigned long long) 1 << curSecond)&bufFirst) != 0 && (((unsigned long long) 1 << curSecond)&bufThird) != 0) {
            prio = curSecond+1;
            break;
        } else if ((((unsigned long long) 1 << curThird)&bufFirst) != 0 && (((unsigned long long) 1 << curThird)&bufSecond) != 0){
            prio = curThird+1;
            break;            
        } else if ( (curFirst == curSecond) && (curFirst == curThird) ) {
            prio = curSecond+1;
            break;            
        }

        bufFirst |= ((unsigned long long) 1<<curFirst);
        bufSecond |= ((unsigned long long) 1<<curSecond);
        bufThird |= ((unsigned long long) 1<<curThird);
    }
    return prio;
}

int solvep2 (std::string fileName) {
    int score;
    std::ifstream file(fileName);
    int result = 0;
    int count = 1;
    int countgrp = 0;
    std::vector<std::string> group = {};

    for (std::string line; std::getline(file,line);) {

        group.push_back(line);

        if (line.empty()) {
            break;
        }

        if (group.size() == 3) {
            result = findGroupPrio(group);
            group.clear();
            score += result;
        }
        
        count++;
    }

    return score;
}

int main () {

    auto start = std::chrono::high_resolution_clock::now();

    int totalScore = solvep1("day3.txt");
    int totalScore2 = solvep2("day3.txt");

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Score total p1: " << totalScore << std::endl;
    std::cout << "Score total p2: " << totalScore2 << std::endl;
    std::cout << "Solving took " << duration.count() << "us" << std::endl;
    return 0;
}
