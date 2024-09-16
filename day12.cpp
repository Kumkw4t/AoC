#include <vector>
#include <array>
#include <queue>
#include <stack>
#include <tuple>
#include <array>
#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>
#include <chrono>

using pii = std::pair<int,int>;

struct Step {

    Step(int mx, int my, int mfrom, int msteps):
        x(mx),
        y(my),
        from(mfrom),
        steps(msteps)
    {};

    int x;
    int y;
    int from;
    int steps;
};

void explore (  std::stack<Step>& stack, std::vector<std::string>& map, 
                std::vector<std::vector<std::pair<bool,int>>>& isVisited, int part)
{
    Step step = stack.top();
    stack.pop();

    std::vector<pii> moves = { {0,1}, {1,0}, {-1,0}, {0,-1} };

    if (step.from == -1) {
        // first move
        if (part == 2) step.steps = 0;

        for (int i=0; i<moves.size();i++) {
            stack.push(Step(step.x+moves[i].first,step.y+moves[i].second,i,step.steps+1));
        }
        return;
    }

    //check out of bound
    if ( (step.x < 0) || (step.x >= map.size()) || (step.y < 0) || (step.y >= map[0].size()) ) {
        return;
    }
        
    if ( (part == 2) && (map[step.x][step.y] == 'a') ) step.steps = 0;

    // check if move is authorized
    if ( ((map[step.x][step.y] != 'a') && 
         ((map[step.x][step.y] - map[step.x - moves[step.from].first][step.y - moves[step.from].second]) > 1) )
         || (( map[step.x][step.y] == 'E') && ( (map[step.x][step.y] - map[step.x - moves[step.from].first][step.y - moves[step.from].second]) != -53)) ) 
    {
        return;
    }
    
    // check if end
    if (map[step.x][step.y] == 'E' ) {
        
        if (!isVisited[step.x][step.y].first) {
            isVisited[step.x][step.y].first = true;
            isVisited[step.x][step.y].second = step.steps;
        } else {
            isVisited[step.x][step.y].second = (step.steps <= isVisited[step.x][step.y].second) ? step.steps : isVisited[step.x][step.y].second;
        }
        return;
    }

    if ( isVisited[step.x][step.y].first && (isVisited[step.x][step.y].second <= step.steps) ) {
        // visited and steps is already less
        return;
    }
    
    isVisited[step.x][step.y].first = true;
    isVisited[step.x][step.y].second = step.steps;

    for (int i=0; i<moves.size();i++) {

        if (i == (moves.size() - step.from - 1) ) continue;
        stack.push(Step(step.x+moves[i].first,step.y+moves[i].second,i,step.steps+1));
    }

    return;
}


int solve (std::string filename, int part) {

    std::fstream file(filename);
    std::vector<std::string> map;
    int countLine = 0;
    pii startPos,endPos;

    // get start info
    for (std::string line; std::getline(file,line); ) {
        map.push_back(line);
        if (line.find('S') != -1) {
            startPos.first = countLine;
            startPos.second = line.find('S');
        }
        
        if (line.find('E') != -1) {
            endPos.first = countLine;
            endPos.second = line.find('E');
        }

        countLine++;
    }

    std::vector<std::vector<std::pair<bool,int>>> isVisited(countLine,std::vector<std::pair<bool,int>>(map[0].length(), {false,0}));
    
    std::stack<Step> stack;
    stack.push(Step(startPos.first,startPos.second,-1,0));

    while (!stack.empty()) {
        explore(stack,map,isVisited,part);
    }

    return isVisited[endPos.first][endPos.second].second;
}

int main () {

    auto start = std::chrono::high_resolution_clock::now();

    int part = 2;
    int result = solve("day12.txt",part);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Message p" << part << ": " << result << std::endl;
    std::cout << "Solving took " << duration.count() << "us" << std::endl;
    return 0;
}
