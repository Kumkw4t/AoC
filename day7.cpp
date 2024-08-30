#include <vector>
#include <array>
#include <queue>
#include <tuple>
#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>
#include <chrono>

unsigned long long solve(std::string filename, int part) {

    unsigned long long result = 0;
    std::unordered_map<std::string,unsigned long long> folderSize;

    struct foldersState {
        std::string currentFolder;
        std::vector<std::string> prevFolders;
    };

    struct foldersState state;
    std::fstream file(filename);
    long size = 0;
    char i = 65;

    for (std::string line; std::getline(file,line); ) {

        if (line[0] == '$') {
            // new command
            if (line.substr(2,2).compare("cd") == 0 ) {
                // moving folders
                if (line.substr(5.2).compare("..") == 0) {
                    // moving up
                    state.currentFolder = state.prevFolders.back();
                    state.prevFolders.pop_back();
                } else {
                    //moving down
                    state.prevFolders.push_back(state.currentFolder);
                    state.currentFolder = line.substr(5);
                    i=65;
                    while (folderSize.count(state.currentFolder) > 0) {
                        i++;
                        state.currentFolder.push_back(i);
                    }
                }
            }         
            
        } else if (line[0] == 'd') {
            // directory name
            folderSize.emplace(line.substr(4),0);
        } else {
            // file size
            size = std::stol(line);
            for (auto folder : state.prevFolders) {
                if (folder.empty()) continue;
                folderSize[folder] += size;
            }
            folderSize[state.currentFolder] += size;
        }
    }

    if (part == 1) {
        for (auto folder : folderSize) {
            if (folder.second <= 100000) {
                result += folder.second;
            }
        }
    } else {

        int neededSpace = folderSize["/"] - 40000000;
        int current = folderSize["/"];
        for (auto folder : folderSize) {
            if (folder.second < neededSpace || folder.second > current) continue;
            current = folder.second;
        }
        result = current;
    }

    return result;
}

int main () {

    auto start = std::chrono::high_resolution_clock::now();

    int part = 2;
    unsigned long long result = solve("day7.txt",part);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Message p" << part << ": " << result << std::endl;
    std::cout << "Solving took " << duration.count() << "us" << std::endl;
    return 0;
}
