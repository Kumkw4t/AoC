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

    int result = 1;

    struct pos {
        int x = 0;
        int y = 0;
    };

    std::vector<struct pos> tail(part == 1 ? 2 : 10,{0,0});
    std::vector<int> distance(part == 1 ? 1 : 9,0);

    std::fstream file(filename);
    std::pair<int,int> dir(0,0);
    std::deque<std::deque<bool>> isVisited(1,{true});
    int index;
    int move = 0;
    
    for (std::string line; getline(file,line); ) {

        if (line.empty()) break;

        switch (line[0]) {
            case 'R':
                dir = {1,0};
                break;
            case 'L':
                dir = {-1,0};
                break;
            case 'U':
                dir = {0,-1};
                break;
            case 'D':
                dir = {0,1};
                break;
            default : break;
        }

        move = std::stoi(line.substr(2));

        while (move > 0) {
            
            tail[0].x += dir.first;
            tail[0].y += dir.second;

            if ( tail[0].x < 0 ) {

                for (int i=0; i<tail.size(); i++) tail[i].x++;

                for (int i = 0; i < isVisited.size(); i++) {
                    isVisited[i].push_front(false);
                }

            } else if ( (tail[0].y >= 0) && (tail[0].x >= isVisited[tail[0].y].size()) ) {
                for (int i = 0; i < isVisited.size(); i++) {
                    isVisited[i].push_back(false);
                }
            }

            if ( tail[0].y < 0 ) {

                for (int i=0; i<tail.size(); i++) tail[i].y++;
                isVisited.push_front(std::deque<bool>(isVisited[0].size(),false));
            } else if ( tail[0].y >= isVisited.size() ) {
                isVisited.push_back(std::deque<bool>(isVisited.back().size(),false));
            }


            for (int i=0; i<distance.size(); i++) {

                distance[i] = (tail[i].y-tail[i+1].y)*(tail[i].y-tail[i+1].y) + (tail[i].x-tail[i+1].x)*(tail[i].x-tail[i+1].x);

                if (distance[i] < 4) break;

                if ( tail[i+1].x == tail[i].x || distance[i] > 4 ) tail[i+1].y += (tail[i+1].y > tail[i].y) ? -1 : 1;
                if ( tail[i+1].y == tail[i].y || distance[i] > 4 ) tail[i+1].x += (tail[i+1].x > tail[i].x) ? -1 : 1;
            }

            move--;

            index = tail.size()-1;
            if ( !isVisited[tail[index].y][tail[index].x] ) {
                isVisited[tail[index].y][tail[index].x] = true;
                result++;
            }
        }
    }

    return result;
}

int main () {

    auto start = std::chrono::high_resolution_clock::now();

    int part = 2;
    int result = solve("day9.txt",part);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Message p" << part << ": " << result << std::endl;
    std::cout << "Solving took " << duration.count() << "us" << std::endl;
    return 0;
}
