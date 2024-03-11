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
    int flagComplexSort;

public:
    Strawberry(int index, int up, int down) : index(index), up(up), down(down), dayPath(0), nightPath(0), flagComplexSort(0) {
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
    int getUp() const { return up; }
    int getDown() const { return down; }
    int getDistance() const { return distance; }
    int getDayPath() const { return dayPath; }
    int getNightPath() const { return nightPath; }
    void setDayPath(int day) { dayPath = day; } 
    void setNightPath(int night) { nightPath = night; } 
    int getFlagComplexSort() const { return flagComplexSort; }
    void setFlagComplexSort(int flag) { flagComplexSort = flag; } 
};

class Path {
private:
    int n;
    std::vector<Strawberry> pathArray;
    std::vector<Strawberry*> sortPathArray;
    int flagMax;
    int max_res;

public:
    Path() : flagMax(0), max_res(0) {
        int up, down;
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
            int maxDown;
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
        // std::cout << innerFlagComplexSort << std::endl;
        
        std::vector<Strawberry*> copySortPathArray;
        std::vector<Strawberry*> copySortPathArray_final;
        int max = sortPathArray[0]->getDayPath();
        for (int i = 0; i < n; i++) {
            copySortPathArray = sortPathArray;
            Strawberry *tmp = sortPathArray[i];
            copySortPathArray.erase(copySortPathArray.begin() + i);
            if (i < innerFlagComplexSort) copySortPathArray.insert(copySortPathArray.begin() + innerFlagComplexSort-1, tmp);
            else copySortPathArray.insert(copySortPathArray.begin() + innerFlagComplexSort, tmp);

            int day = 0, night = 0;
            int up, down;
            for (int i = 0; i < n; i++) {
                up = copySortPathArray[i]->getUp();
                down = copySortPathArray[i]->getDown();
                day = night + up;
                night = day - down;
                copySortPathArray[i]->setDayPath(day);
                copySortPathArray[i]->setNightPath(night);
            }

            for (int i = 0; i < n; i++) {
                if (copySortPathArray[i]->getDayPath() > max) {
                    max = copySortPathArray[i]->getDayPath();
                    copySortPathArray_final = copySortPathArray;
                }
            }
        }

        max_res = max;
        //std::cout << max_res << std::endl;
        sortPathArray = copySortPathArray_final;

        // for (int i = 0; i < n-1; i++) {
        //     std::cout << copySortPathArray_final[i]->getIndex() << " ";
        // }
        // std::cout << copySortPathArray_final[n-1]->getIndex() << std::endl;
        
        
        
        //sortPathArray = copySortPathArray;
        
        

    }


    void setPath() { 
        int day = 0, night = 0;
        int up, down;
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
        std::cout << max_res << std::endl;
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
    //path.setPath();
    //path.printArraySort();
    path.printResult();

    return 0;
}
