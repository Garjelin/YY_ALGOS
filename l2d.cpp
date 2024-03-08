#include <iostream>
#include <vector>

class Point {
private:
    int x;
    int y;
    int value;
    int neighbors;

public:
    Point() : x(0), y(0), value(0), neighbors(0) {}
    int getX() const { return x; }
    int getY() const { return y; }
    int getValue() const { return value; }
    void setValue(int v) { value = v; }
    int getNeighbors() const { return neighbors; }
    void setNeighbors(int v) { neighbors = v; }
};

class Field {
private:
    static const int size = 8;
    Point field[size][size];
    int n;
    std::vector<Point*> userArray;


public:
    Field() {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                field[i][j] = Point();
            }
        }
    }

    void fillField() {
        int sizeArray, x, y;
        std::cin >> sizeArray;
        setSizeArray(sizeArray);
        for (int i = 0; i < n; ++i) {
            std::cin >> x >> y;
            field[x-1][y-1].setValue(1);
            userArray.push_back(&field[x-1][y-1]);
        }
    }

    void setSizeArray(int size) { n = size; }
    int getSizeArray() const { return n; }

    void printArray() const {
        for (int i = 0; i < n; i++) {
            std::cout << userArray[i]->getNeighbors() << " ";
        }
    }

    void reNewNeighbors() {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                int sum_neighbors = 0;
                if (field[i][j].getValue()) {
                    sum_neighbors = sumNeighbors(i+1, j, sum_neighbors);
                    sum_neighbors = sumNeighbors(i-1, j, sum_neighbors);
                    sum_neighbors = sumNeighbors(i, j+1, sum_neighbors);
                    sum_neighbors = sumNeighbors(i, j-1, sum_neighbors);
                }
                field[i][j].setNeighbors(sum_neighbors);
            }
        }
    }

    int sumNeighbors(int m, int n, int sum_neighbors) {
        if (checkIndex(m, n)) {
            if (field[m][n].getValue()) sum_neighbors++;
        }
        return sum_neighbors;
    }

    int checkIndex(int i, int j) {
        if ((i < 0) || (i >= size) || (j < 0) || (j >= size)) return 0;
        else return 1;
    }

    void printPoints() const {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                std::cout << field[i][j].getNeighbors();
            }
            std::cout << std::endl;
        }
    }

    int perimetr() const {
        int perimetr = 0;
        for (int i = 0; i < n; ++i) {
            perimetr += 4 - userArray[i]->getNeighbors();
        }
        return perimetr;
    }
};

int main() {
    Field field;
    
    field.fillField();
    field.reNewNeighbors();
    //field.printArray();
    std::cout << field.perimetr() << std::endl;

    return 0;
}
