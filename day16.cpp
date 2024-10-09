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
#include <list>
#include <algorithm>

struct Valve {
    int rate;
    std::list<std::string> leadsTo;
};

// struct Valve2 {
//     std::string name;
//     int rate;
//     std::list<std::string> leadsTo;
// };

int solve (std::string filename, int part) {
 
    std::fstream file(filename);
    std::unordered_map<std::string,Valve> valves;
    // std::vector<Valve2> valves_test = {};

    for (std::string line; getline(file,line);) {
        std::string name = line.substr(6,2);
        size_t size = 0;
        int flow = std::stoi(line.substr(23),&size);
        std::list<std::string> leadTo = {};
        // std::cout << "size " << size << " | flow " << flow << std::endl;
        int index = line.find(',');
        leadTo.push_back(line.substr(index == std::string::npos ? line.length()-2 : index - 2,2));
        while (index != std::string::npos) {
            // std::cout << "index " << index << std::endl;
            index += 2;
            // std::cout << "index " << index << " - " << line.substr(index,2) << std::endl;
            leadTo.push_back(line.substr(index,2));
            index = line.find(',',index);
        }
        valves.emplace(name,Valve{flow,leadTo});
        // valves_test.push_back({name,flow,leadTo});
    }

    // for (auto valve : valves_test) {
    //     std::cout << "Valve: " << valve.name << " - flow " << valve.rate << std::endl;
    //     std::cout << "Next: ";
    //     for (auto next : valve.leadsTo) {
    //         std::cout << next << " - ";
    //     }
    //     std::cout << std::endl;
    // }

    return 0;
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
