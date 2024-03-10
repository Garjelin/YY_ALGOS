#include <iostream>
#include <vector>

class Strawberry {
private:
    int index;
    long long up;
    long long down;
    long long distance;
    long long dayPath;
    long long nightPath;
    int flagComplexSort;

public:
    Strawberry(int index, long long up, long long down) : index(index), up(up), down(down), dayPath(0), nightPath(0), flagComplexSort(0) {
        distance = up - down;
    }
    Strawberry(const Strawberry &other) {
        index = other.getIndex();
        up = other.getUp();
        down = other.getDown();
        distance = other.getDistance();
        dayPath = other.getDayPath();
        nightPath = other.getNightPath();
        flagComplexSort = other.getFlagComplexSort();
    }

    int getIndex() const { return index; }
    long long getUp() const { return up; }
    long long getDown() const { return down; }
    long long getDistance() const { return distance; }
    long long getDayPath() const { return dayPath; }
    long long getNightPath() const { return nightPath; }
    void setDayPath(long long day) { dayPath = day; } 
    void setNightPath(long long night) { nightPath = night; } 
    int getFlagComplexSort() const { return flagComplexSort; }
    void setFlagComplexSort(int flag) { flagComplexSort = flag; } 
};

class Path {
private:
    int n;
    std::vector<Strawberry> pathArray;
    std::vector<Strawberry*> sortPathArray;
    int flagMax;

public:
    Path() : flagMax(0) {
        long long up, down;
        std::cin >> n;
        for (int i = 0; i < n; ++i) {
            std::cin >> up >> down;
            Strawberry strowb(i+1, up, down);
            pathArray.push_back(strowb);
        }
    }

    void fillSortArray() {
        for (int i = 0; i < n; i++) {
            sortPathArray.push_back(&pathArray[i]);
        }
    }

    void bubbleSortDescending(int size) {
        for (int i = 0; i < size - 1; i++) {
            for (int j = size-1; j > i; j--) {
                if (sortPathArray[j-1]->getDistance() < sortPathArray[j]->getDistance()) {
                    std::swap(sortPathArray[j], sortPathArray[j-1]);
                }
            }
        }
    }

    void complexSort() {
        int j = 0;
        for (int i = 0; i < n; i++) {
            if (pathArray[i].getDistance() > 0) {
                sortPathArray[j] = &pathArray[i];
                sortPathArray[j]->setFlagComplexSort(1);
                j++;
                
            }
        } 
        if (j == n) bubbleSortDescending(j);
        else {
            long long maxDown;
            for (int i = 0; i < n; i++) {
                if (pathArray[i].getFlagComplexSort() == 0) {
                    maxDown = pathArray[i].getUp();
                    flagMax = 1;
                    break;
                } 
            }
            if (flagMax) {
                for (int i = 0; i < n; i++) {
                    if ((pathArray[i].getFlagComplexSort() == 0) && (pathArray[i].getUp() > maxDown)) {
                        maxDown = pathArray[i].getUp(); 
                    }
                }
                for (int i = 0; i < n; i++) {
                    if ((pathArray[i].getFlagComplexSort() == 0) && (pathArray[i].getUp() == maxDown)) {
                        sortPathArray[j] = &pathArray[i];
                        sortPathArray[j]->setFlagComplexSort(1);
                        j++;
                    }
                }
                for (int i = 0; i < n; i++) {
                    if ((pathArray[i].getFlagComplexSort() == 0)) {
                        sortPathArray[j] = &pathArray[i];
                        sortPathArray[j]->setFlagComplexSort(1);
                        j++;
                    }
                }
            }
        }

    }

    void complexSort_2() {
        int j = 0;
        int innerFlagComplexSort = 0;
        for (int i = 0; i < n; i++) {
            if (pathArray[i].getDistance() > 0) {
                sortPathArray[j] = &pathArray[i];
                sortPathArray[j]->setFlagComplexSort(1);
                j++;
                
            }
        } 
        for (int i = 0; i < n; i++) {
            if ((pathArray[i].getFlagComplexSort() == 0)) {
                sortPathArray[j] = &pathArray[i];
                j++;
            }
        }
        for (int i = 0; i < n; i++) {
            if ((sortPathArray[i]->getFlagComplexSort() == 0)) {
                innerFlagComplexSort = i;
                break;
            }
        }
        std::cout << innerFlagComplexSort << std::endl;
        
        std::vector<Strawberry*> copySortPathArray;
        long long max = sortPathArray[0]->getDayPath();
        for (int i = 0; i < n; i++) {
            copySortPathArray = sortPathArray;
            Strawberry *tmp = sortPathArray[i];
            copySortPathArray.erase(copySortPathArray.begin() + i);
            if (i < innerFlagComplexSort) copySortPathArray.insert(copySortPathArray.begin() + innerFlagComplexSort-1, tmp);
            else copySortPathArray.insert(copySortPathArray.begin() + innerFlagComplexSort, tmp);

            long long day = 0, night = 0;
            long long up, down;
            for (int i = 0; i < n; i++) {
                up = copySortPathArray[i]->getUp();
                down = copySortPathArray[i]->getDown();
                day = night + up;
                night = day - down;
                copySortPathArray[i]->setDayPath(day);
                copySortPathArray[i]->setNightPath(night);
            }

            for (int i = 0; i < n; i++) {
                if (copySortPathArray[i]->getDayPath() > max) max = copySortPathArray[i]->getDayPath();
            }
        }
        std::cout << max << std::endl;
        sortPathArray = copySortPathArray;
        
        

    }


    void setPath() { 
        long long day = 0, night = 0;
        long long up, down;
        for (int i = 0; i < n; i++) {
            up = sortPathArray[i]->getUp();
            down = sortPathArray[i]->getDown();
            day = night + up;
            night = day - down;
            sortPathArray[i]->setDayPath(day);
            sortPathArray[i]->setNightPath(night);
        }
    }

    void printArray() const {
        for (int i = 0; i < n; i++) {
            std::cout << "index: " << pathArray[i].getIndex() << " " << "up: " << pathArray[i].getUp() << " " << "down: " << pathArray[i].getDown() << " " << "distance: " << pathArray[i].getDistance() << " " << "dayPath: " << pathArray[i].getDayPath() << " " << "nightPath: " << pathArray[i].getNightPath() << std::endl;
        }
    }
    void printArraySort() const {
        for (int i = 0; i < n; i++) {
            std::cout << "index: " << sortPathArray[i]->getIndex() << " " << "up: " << sortPathArray[i]->getUp() << " " << "down: " << sortPathArray[i]->getDown() << " " << "distance: " << sortPathArray[i]->getDistance() << " " << "dayPath: " << sortPathArray[i]->getDayPath() << " " << "nightPath: " << sortPathArray[i]->getNightPath() << std::endl;
        }
    }

    void printResult() const {
        long long max = sortPathArray[0]->getDayPath();
        for (int i = 0; i < n; i++) {
            if (sortPathArray[i]->getDayPath() > max) max = sortPathArray[i]->getDayPath();
        }
        std::cout << max << std::endl;
        for (int i = 0; i < n-1; i++) {
            std::cout << sortPathArray[i]->getIndex() << " ";
        }
        std::cout << sortPathArray[n-1]->getIndex() << std::endl;
    }

};

int main() {
    Path path;
    
    //path.printArray();
    path.fillSortArray();
    //path.bubbleSortDescending();
    path.complexSort_2();
    path.setPath();
    //path.printArraySort();
    path.printResult();

    return 0;
}
