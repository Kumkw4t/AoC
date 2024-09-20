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

bool fill (std::deque<std::deque<bool>> &map,int startY) {

    Point res(0,startY);
    // std::cout << "start Y: " << startY << std::endl;

    while (true) {
        while ((res.x < (map.size()-1)) && !map[res.x+1][res.y]) {
            // chute libre
            std::cout << "[" << res.x << "," << res.y << "]: " << map[res.x][res.y] << std::endl;
            res.x++; 
        }
       
        if (res.x == (map.size()-1)) {
            std::cout << "bottom reached" << std::endl;
            return false;
        }
        
        if (res.y > 0) {
            if (!map[res.x+1][res.y-1]) {
                // diagonale left
                res.x++;
                res.y--;
                continue;
            }

            if (res.y < map[0].size()) {
                if (!map[res.x+1][res.y+1]) {
                    // diagonale right
                    res.x++;
                    res.y++;
                    continue;
                } else {
                    // no more moves available
                    std::cout << "filling [" << res.x << "," << res.y << "]" << std::endl;
                    map[res.x][res.y] = true;
                    return true;
                }
            } else {
                // oob = into the void
                return false;
            }
        } else {
            // oob = into the void
            return false;
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
        // minX = std::min(minX, p1.x);

        while (index < line.length()) {

            // std::cout << " === " << index << " | " << line.length() << " === " << std::endl;
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

            // std::cout << "P1 [" << p1.x << "," << p1.y << "] | P2 [" << p2.x << "," << p2.y << "]" << std::endl;

            // column index is lower than previous ones, growing map
            while (minY > minPY) {
                // std::cout << "lower Y! " << p1.y << " vs " << minY << std::endl;
                minY--;
                for (std::deque<bool> &mapLine : map) {
                    mapLine.push_front(false);
                }
            }

            // std::cout << "MinX: " << minX << " | MinY: " << minY << std::endl;
            while ((maxPY - minY) >= map[0].size()) {
                // std::cout << "larger Y! " << maxPY-minY << " vs " << map[0].size();
                for (std::deque<bool> &mapLine : map) {
                    mapLine.push_back(false);
                }
                // std::cout << " -> new size: " << map[0].size() << std::endl;
            }

            while ((maxPX - minX) >= map.size()) {
                // std::cout << "larger X! " << p1.x-minX << " vs " << map.size() << std::endl;
                map.push_back(std::deque<bool>(map[0].size(),false));
            }

            // std::cout << "current size: " << map.size() << "," << map[0].size() << std::endl;
            if (p1.x == p2.x) {
                // std::cout << "X are equal" << std::endl;
                for (int i = (minPY-minY); i <= (maxPY-minY); i++) {
                    // std::cout << "adding [" << p1.x-minX << "," << i << "]" << std::endl;
                    map[p1.x-minX][i] = true;
                }
            } else {
                // std::cout << "Y are equal" << std::endl;
                for (int i = (minPX-minX); i <= (maxPX-minX); i++) {
                    // std::cout << "adding [" << i << "," << p1.y-minY << "]" << std::endl;
                    map[i][p1.y-minY] = true;
                }
            }
        }
    }

    for (std::deque<bool> mapLine : map) {
        for (bool chr : mapLine) {
            if (chr) std::cout << "#";
            else std::cout << ".";
        }
        std::cout << std::endl;
    }

    bool out = fill(map,500-minY);
    while (out) {
        out = fill(map,500-minY);
        result++;
    }    

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
