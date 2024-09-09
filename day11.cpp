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

int lcm = 1;

struct Monkey {
    std::queue<int> mItems;
    int mMember;
    char mOp;
    int mDivisible;
    std::pair<int,int> mThrow;
    int mInspected;

    Monkey(std::vector<int> items, int member, char op, int divisible, int throw1, int throw2) :
        mMember(member),
        mOp(op),
        mDivisible(divisible),
        mThrow(throw1,throw2),
        mInspected(0)
    {
        for (int item : items) {
            mItems.push(item);
        }
    }

    std::pair<int,int> throwTo(int part) {
        int tmp = (mMember == -1) ? mItems.front() : mMember;
        long long res = (mOp == '*') ? (long long) mItems.front() * (long long) tmp : mItems.front() + tmp;
        mItems.pop();
        mInspected++;
        res = (part == 1) ? res/3 : res%lcm;
        if (res % mDivisible == 0) {
            return std::pair<int,int> (mThrow.first,res);
        } else {
            return std::pair<int,int> (mThrow.second,res);
        }
    }
};

long long solve (std::string filename, int part) {

    std::fstream file(filename);
    long long count = 0;
    std::vector<struct Monkey> monkeys;
    
    std::vector<int> items;
    int member;
    char op;
    int divisible;
    int throw1, throw2;

    for (std::string line; getline(file,line); ) {

        if (count%7 == 1) {
            int index = 18;
            while (index <= line.length()) {
                items.push_back(std::stoi(line.substr(index)));
                index = line.find(',',index) != -1 ? line.find(',',index)+2 : line.length()+1;
            }

        } else if (count%7 == 2) {
            // member and op
            op = line[23];
            member = (line[25] == 'o') ? -1 : std::stoi(line.substr(25));;

        } else if (count%7 == 3) {
            // test mDivisible
            divisible = std::stoi(line.substr(21));

        } else if (count%7 == 4) {
            // mThrow.first
            throw1 = std::stoi(line.substr(29));
        } else if (count%7 == 5) {
            // mThrow.second
            throw2 = std::stoi(line.substr(30));

            // create new monkey with everything
            struct Monkey monkey(items,member,op,divisible,throw1,throw2);
            monkeys.push_back(monkey);
            items.clear();
        }
        count++;
    }

    // lcm
    for (struct Monkey monkey : monkeys) {
        lcm *= monkey.mDivisible;
    }

    // solve actions
    int loop = (part == 1) ? 20 : 10000;
    for (int i=0; i<loop; i++) {

        count = 0;

        for (struct Monkey& monkey : monkeys) {

            while (monkey.mItems.size() > 0) {
                std::pair<int,int> res = monkey.throwTo(part);
                monkeys[res.first].mItems.push(res.second);
            }
            count++;
        }
    }

    // monkey business
    count = 0;
    long long result = 0;
    for (struct Monkey monkey : monkeys) {
        if (monkey.mInspected > count)  {
            result = count;
            count = monkey.mInspected;
        } else if (monkey.mInspected > result) {
            result = monkey.mInspected;
        }
    }

    return result*count;
}

int main () {

    auto start = std::chrono::high_resolution_clock::now();

    int part = 2;
    long long result = solve("day11.txt",part);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Message p" << part << ": " << result << std::endl;
    std::cout << "Solving took " << duration.count() << "us" << std::endl;
    return 0;
}
