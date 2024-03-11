#include <iostream>
#include <string>
#include <vector>

class Element {
private:
    int value;
    int isMax;

public:
    Element() : value(0), isMax(0) {}
    int getValue() const { return value; } 
    void setValue(int value) { this->value = value; }
    void setIsMax(int isMax) { this->isMax = isMax; }
};

class Row {
private:
    Element* elements;
    int size;

public:
    Row() : elements(nullptr), size(0) {}
    Row(Element *arr, int size) : elements(arr), size(size) {}
    void printRow() const {
        for (int i = 0; i < size; i++) {
            std::cout << elements[i].getValue() << " ";
        }
        std::cout << std::endl;
    }
};

class Field {
private:
    int m;
    int n;
    Element** arr;
    Row *row_i;
    int max;
    int countMax;
    int res_i;
    int res_j;

public:
    Field(int m, int n) : m(m), n(n), row_i(nullptr), max(0), countMax(0), res_i(-1), res_j(-1) {
        arr = new Element*[m];
        for (int i = 0; i < m; ++i) {
            arr[i] = new Element[n];
        }
        row_i = new Row[m];
    }
    ~Field() {
        for (int i = 0; i < m; ++i) {
            delete[] arr[i];
        }
        delete[] arr;
        delete[] row_i;
    }

    void fillRow() {
        row_i[1] = Row(arr[1], n);
        row_i[2] = Row(arr[2], n);
    }

    void printRow() {
        row_i[2].printRow();
    }

    int getMax() const { return max; } 
    int getCountMax() const { return countMax; } 

    void fillField() {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int val;
                std::cin >> val;
                arr[i][j].setValue(val);
            }
        }
    }

    void findFieldMax() {
        max = arr[0][0].getValue();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (arr[i][j].getValue() > max) {
                    max = arr[i][j].getValue();
                }
            }
        }
    }

    void countFieldMax() {
        countMax = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (arr[i][j].getValue() == max) {
                    countMax++;
                }
            }
        }
    }

    void printField() {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                std::cout << arr[i][j].getValue() << " ";
            }
            std::cout << std::endl;
        }
    }
    // void printRow(int i) {
    //     rows[i]->printRow();
    // }

};

int main() {
    int m, n;
    std::cin >> m >> n;
    Field arr(m, n);
    arr.fillField();
    arr.printField();
    arr.findFieldMax();
    arr.countFieldMax();

    std::cout << "counMax " << arr.getCountMax() << std::endl;
    arr.fillRow();
    arr.printRow();

    return 0;
}
