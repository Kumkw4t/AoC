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
#include <algorithm>

using pii = std::pair<int,int>;

int getDist(pii a, pii b) {
    return (std::abs(a.first - b.first) + std::abs(a.second - b.second));
}

long long solve (std::string filename, int part) {

    long long result = 0;
    std::fstream file(filename);
    std::vector<pii> ranges({});
    pii currentRange;

    std::vector<pii> sensors;
    std::vector<pii> beacons;
    pii sensor;
    pii beacon;

    size_t size = 0;
    size_t tmpSize = 0;

    int dist = 0;
    int diff;
    bool flag;
    int index;

    // parsing file
    for (std::string line; getline(file,line);) {
        size = 12;
        sensor.first = std::stoi(line.substr(size),&tmpSize);
        size += (tmpSize+4);
        sensor.second = std::stoi(line.substr(size),&tmpSize);

        size += (tmpSize + 25);
        beacon.first = std::stoi(line.substr(size),&tmpSize);
        beacon.second = std::stoi(line.substr(size+tmpSize+4));

        sensors.push_back(sensor);
        beacons.push_back(beacon);
    }

    for (int goal = 0; goal <= 4000000; goal++) {

        if ((part == 1) && (goal < 2000000)) continue;
        ranges.clear();

        for (int i = 0; i < sensors.size(); i++) {

            dist = getDist(sensors[i],beacons[i]);
            diff = std::abs(goal - sensors[i].second);

            if ( diff > dist) {
                continue;
            }

            // in range
            currentRange = {sensors[i].first - (dist - diff), sensors[i].first + (dist - diff)};
            std::vector<int> elemsToRemove = {};
            index = -1;

            for (pii range : ranges) {
                // no overlap
                index++;
                if ((currentRange.first > range.second) || (currentRange.second < range.first)) continue;

                currentRange.first = std::min(currentRange.first,range.first);
                currentRange.second = std::max(currentRange.second,range.second);
                elemsToRemove.push_back(index);
            }
            
            ranges.push_back(currentRange);
            
            while (elemsToRemove.size() != 0) {
                ranges.erase(ranges.begin()+elemsToRemove.back());
                elemsToRemove.pop_back();
            }

        }

        if (part == 2) {
            flag = true;
            for (pii range : ranges) {
                if ((range.first <= 0) && (range.second >= 4000000)) {
                    flag = false;
                    break;
                }
            }

            if (flag) {
                long long x = ranges[1].first - 1;
                result = (x * 4000000) + goal;
            }
        }

        if (part == 1) {
            for (pii range : ranges) {
                result += std::abs(range.second - range.first);
            }
            break;
        }
    }

    return result;
}

int main () {

    auto start = std::chrono::high_resolution_clock::now();

    int part = 2;
    long long result = solve("day15.txt",part);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Message p" << part << ": " << result << std::endl;
    std::cout << "Solving took " << duration.count() << "us" << std::endl;
    return 0;
}
