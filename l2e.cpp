#include <iostream>
#include <vector>

class Strawberry {
private:
    int index;
    int up;
    int down;
    int distance;
    int dayPath;
    int nightPath;

public:
    Strawberry(int index, int up, int down) : index(index), up(up), down(down), dayPath(0), nightPath(0) {
        distance = up - down;
    }
    int getIndex() const { return index; }
    int getUp() const { return up; }
    int getDown() const { return down; }
    int getDistance() const { return distance; }
    int getDayPath() const { return dayPath; }
    int getNightPath() const { return nightPath; }
};

class Path {
private:
    int n;
    std::vector<Strawberry> path;

public:
    Path() {
        int up, down;
        std::cin >> n;
        for (int i = 0; i < n; ++i) {
            std::cin >> up >> down;
            Strawberry strowb(i+1, up, down);
            path.push_back(strowb);
        }
    }

    void printArray() const {
        for (int i = 0; i < n; i++) {
            std::cout << "index: " << path[i].getIndex() << " " << "up: " << path[i].getUp() << " " << "down: " << path[i].getDown() << " " << "distance: " << path[i].getDistance() << " " << "dayPath: " << path[i].getDayPath() << " " << "nightPath: " << path[i].getNightPath() << std::endl;
        }
    }

};

int main() {
    Path path;
    
    path.printArray();

    return 0;
}
