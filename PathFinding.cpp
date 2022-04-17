#include <SFML/Graphics.hpp>
#include <cmath>
#include <array>
#include <cstring>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <tuple>
#include <sstream>
using namespace std;
using namespace sf;

class Tail {
    public:
        Tail(IntRect rect,int cost):rect(rect),cost(cost){};
        Tail(){};
        Tail(IntRect rect, int cost, int x, int y, Tail* previous):rect(rect),cost(cost),x(x),y(y),previous(previous){};
        IntRect rect;
        int cost;;
        int x;
        int y;
        Tail* previous;

        bool operator==(const Tail &a) const {
            return this->x == a.x && this->y == a.y;
        }

};

bool operator<(const Tail &a, const Tail &b) {
        return a.cost < b.cost;
}
const int HEIGHT_MAP = 25;//ðàçìåð êàðòû âûñîòà
const int WIDTH_MAP = 40;//ðàçìåð êàðòû øèðèíà
String TileMap[HEIGHT_MAP] = {
        "[--------------------------------------]",
        "|_     _     _     __     _     _     _|",
        "|_     _     _     __     _     _     _|",
        "|_     _     _     __     _     _     _|",
        "|_     _     _     __     _     _     _|",
        "|_     _     _     __     _     _     _|",
        "|_     !     !     __     _     _     _|",
        "|_     _     !     __     _     _     _|",
        "|_     _     !     __     _     _     _|",
        "|_     _     !     __     _     _     _|",
        "|_     _     !     __     _     _     _|",
        "|_     _     !     __     _     _     _|",
        "|__   ___   ___   ____   ___   ___   __|",
        "|_     _     _     __     _     _     _|",
        "|_     _     _     __     _     _     _|",
        "|_     _     _     __     _     _     _|",
        "|_     _     _     __     _     _     _|",
        "|_     _     _     __     _     _     _|",
        "|_     _     _     __     _     _     _|",
        "|_     _     _     __     _     _     _|",
        "|_     _     _     __     _     _     _|",
        "|_     _     _     __     _     _     _|",
        "|_     _     _     __     _     _     _|",
        "|_     _     _     __     _     _     _|",
        "<-------------------------------------->",
};
Tail tileMap[HEIGHT_MAP][WIDTH_MAP];

int EstimateDistance(Tail& a, Tail& b){
    return abs(a.x - b.x) + abs(a.y - b.y);
}
vector<Tail> GetNeighborsInd(Tail& a){
    vector<Tail> neighbors = {tileMap[a.x-1][a.y], tileMap[a.x+1][a.y],tileMap[a.x][a.y-1],tileMap[a.x][a.y+1]};
    return neighbors;
}
vector<Tail> BuiltPath(Tail& start, Tail& dest){
    vector<Tail> result;
    for(Tail i = dest;i !=start;){
        result.push_back(i);
        i = *i.previous;
    }
    return result;
}
vector<Tail> BuiltPath(map<Tail,Tail>& a){
    vector<Tail> result;
    for(auto i:a){
        result.push_back(i.first);
    }
    return result;
}
vector<Tail> aStarSearch(Tail& start, Tail& dest){
    try {
        priority_queue<Tail> frontier;

        frontier.push(start);
        map<Tail, Tail> came_from;
        map<Tail, int> cost_so_far;
        start.previous = &start;
        came_from[start] = start;
        cost_so_far[start] = 9999999;
        while (!frontier.empty()) {
            Tail current = frontier.top();
            if (current == dest) {
                cout << "path found, built ->";
            //    return came_from;
                return BuiltPath(start,dest);

            }
            for (auto i: GetNeighborsInd(current)) {
                int new_cost = cost_so_far[current] + i.cost;
                if (!(cost_so_far.find(i) == cost_so_far.end()) || new_cost < cost_so_far[i]) {
                    cost_so_far[i] = new_cost;
                    i.cost = new_cost + EstimateDistance(i, dest);
                    frontier.pop();
                    frontier.push(i);
                    i.previous = &current;
                    came_from[i] = current;
                    //cout << " {" <<i.x  << ";"<< i.y << "} ";
                }
            }

        }
        throw runtime_error(":(");
    }catch (const runtime_error& e){
        cout << e.what();
    }
}






int main() {

    Tail tail1 = {IntRect(0, 0, 32, 32),1};       // Много костылей, я пытался тестить алгоритм
    Tail tail2 = {IntRect(32 * 1, 0, 32, 32),2};
    Tail tail3 = {IntRect(32 * 2, 0, 32, 32),2};
    Tail tail4 = {IntRect(32 * 3, 0, 32, 32),100};
    Tail tail5 = {IntRect(32 * 4, 0, 32, 32),100};
    Tail tail6 = {IntRect(32 * 5, 0, 32, 32),100};
    Tail tail7 = {IntRect(32 * 6, 0, 32, 32),100};
    Tail tail8 = {IntRect(32 * 7, 0, 32, 32),100};
    Tail tail9 = {IntRect(32 * 1, 32 * 1, 32, 32),100};
    Tail tail10 = {IntRect(32 * 2, 32 * 1, 32, 32),100};
    Tail tail11 = {IntRect(32 * 4, 32 * 1, 32, 32),100};
    Tail tail12 = {IntRect(32 * 3, 32 * 1, 32, 32),100};
    map<char,Tail> tailKeys = {{' ',tail1},
                               {'_',tail2},
                               {'-',tail3},
                               {'|',tail4},
                               {'[',tail5},
                               {']',tail6},
                               {'<',tail7},
                               {'>',tail8},
                               {'p',tail9},
                               {'s',tail10},
                               {'+',tail11},
                               {'!',tail12}};


    for (int i = 0; i < HEIGHT_MAP; i++){
        for (int j = 0; j < WIDTH_MAP; j++)
        {
            tileMap[i][j].cost = tailKeys[TileMap[i][j]].cost;
            tileMap[i][j].x = j;
            tileMap[i][j].y = i;
        }

        }

    vector<Tail> a = aStarSearch(tileMap[3][3], tileMap[5][5]);
    for(auto i: a){
        cout << " {" << i.x << ";" << i.y << "}";
    }
    return 0;
}
