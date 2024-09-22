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

struct Point {

    Point(int mx, int my):
        x(mx),
        y(my)
    {};

    int x;
    int y;
};

bool fill (std::deque<std::deque<bool>> &map,int startY, int part, int& grewLeft) {

    Point res(0,startY);
    grewLeft = 0;

    while (true) {
        while ((res.x < (map.size()-1)) && !map[res.x+1][res.y]) {
            // chute libre
            res.x++; 
        }
       
        if ((part == 1) && (res.x == (map.size()-1))) {
            if (part == 1) return false;
        }
        
        if (res.y > 0) {
            if (!map[res.x+1][res.y-1]) {
                // diagonale left
                res.x++;
                res.y--;
                continue;
            }

            if (res.y < (map[0].size()-1)) {
                if (!map[res.x+1][res.y+1]) {
                    // diagonale right
                    res.x++;
                    res.y++;
                    continue;
                } else {
                    // no more moves available
                    map[res.x][res.y] = true;

                    if ((res.x == 0) && (res.y == startY) && (part == 2)) return false;
                    
                    return true;
                }
            } else {
                // oob = into the void
                if (part == 1) return false;

                // part 2 grow map
                for (std::deque<bool> &mapLine : map) {
                    mapLine.push_back(false);
                }
                map[map.size()-1][map[0].size()-1] = true;
            }
        } else {
            // oob = into the void
            if (part == 1) return false;

            // part 2, grow map
            for (std::deque<bool> &mapLine : map) {
                mapLine.push_front(false);
            }
            grewLeft++;
            map[map.size()-1][0] = true;
            res.y++;
        }
    }

    return true;
}

int solve (std::string filename, int part) {

    int result = 0;
    std::fstream file(filename);
    int minX = 0;
    int minY = 500;
    int minPX,minPY,maxPX,maxPY;
    std::deque<std::deque<bool>> map(1,std::deque<bool>(1,false));
    std::size_t index, tmpIndex;
    Point p1(0,0),p2(0,0);

    for (std::string line; getline(file,line);) {

        index = 0; // state in line
        p1.y = std::stoi(line.substr(index),&index);
        p1.x = std::stoi(line.substr(index+1));

        minY = std::min(minY, p1.y);

        while (index < line.length()) {

            index = line.find('-',index) + 3;
            p2.y = p1.y;
            p2.x = p1.x;
            p1.y = std::stoi(line.substr(index),&tmpIndex);
            index += tmpIndex;
            p1.x = std::stoi(line.substr(++index),&tmpIndex);
            index += tmpIndex;

            minPY = std::min(p1.y,p2.y);
            minPX = std::min(p1.x,p2.x);
            maxPY = std::max(p1.y,p2.y);
            maxPX = std::max(p1.x,p2.x);

            // column index is lower than previous ones, growing map
            while (minY > minPY) {
                minY--;
                for (std::deque<bool> &mapLine : map) {
                    mapLine.push_front(false);
                }
            }

            while ((maxPY - minY) >= map[0].size()) {
                for (std::deque<bool> &mapLine : map) {
                    mapLine.push_back(false);
                }
            }

            while ((maxPX - minX) >= map.size()) {
                map.push_back(std::deque<bool>(map[0].size(),false));
            }

            if (p1.x == p2.x) {
                for (int i = (minPY-minY); i <= (maxPY-minY); i++) {
                    map[p1.x-minX][i] = true;
                }
            } else {
                for (int i = (minPX-minX); i <= (maxPX-minX); i++) {
                    map[i][p1.y-minY] = true;
                }
            }
        }
    }

    // floor
    if (part == 2) {
        map.push_back(std::deque<bool>(map[0].size(),false));
        map.push_back(std::deque<bool>(map[0].size(),true));
    }

    for (std::deque<bool> mapLine : map) {
        for (bool chr : mapLine) {
            if (chr) std::cout << "#";
            else std::cout << ".";
        }
        std::cout << std::endl;
    }

    int grew = 0;
    bool out = fill(map,500-minY,part,grew);
    while (out) {
        out = fill(map,500-minY,part,grew);
        while (grew > 0) {
            minY--;
            grew--;
        }
        result++;
    }    

    if (part == 2) result++;
    return result;
}

int main () {

    auto start = std::chrono::high_resolution_clock::now();

    int part = 2;
    int result = solve("day14.txt",part);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Message p" << part << ": " << result << std::endl;
    std::cout << "Solving took " << duration.count() << "us" << std::endl;
    return 0;
}
