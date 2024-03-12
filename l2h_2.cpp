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

class RowCol {
private:
    Element* elements;
    int size;
    int countMaxRowCol;

public:
    RowCol() : elements(nullptr), size(0), countMaxRowCol(0) {}
    RowCol(Element *arr, int size) : elements(arr), size(size), countMaxRowCol(0) {}
    Element* getElements() const {return elements;}
    void printRowCol() const {
        for (int i = 0; i < size; i++) {
            std::cout << elements[i].getValue() << " ";
        }
        std::cout << std::endl;
    }
    void setCountMaxRowCol(int max) {
        countMaxRowCol = 0;
        for (int i = 0; i < size; i++) {
            if (elements[i].getValue() == max) {
                countMaxRowCol++;
            }
        }
    }
    int getCountMaxRowCol() const { 
        return countMaxRowCol; 
        }
};

class Field {
private:
    int m;
    int n;
    Element** arr;
    RowCol *row_i;
    RowCol *col_j;
    int max;
    int countMaxRowCol;
    int res_i;
    int res_j;

public:
    Field(int m, int n) : m(m), n(n), row_i(nullptr), col_j(nullptr), max(0), countMaxRowCol(0), res_i(-1), res_j(-1) {
        arr = new Element*[m];
        for (int i = 0; i < m; ++i) {
            arr[i] = new Element[n];
        }
        row_i = new RowCol[m];
        col_j = new RowCol[n];
    }
    ~Field() {
        for (int i = 0; i < m; ++i) {
            delete[] arr[i];
        }
        delete[] arr;
        delete[] row_i;
        for (int j = 0; j < n; ++j) {
            delete[] col_j[j].getElements();
        }
        delete[] col_j;
    }

    void fillRow() {
        for (int i = 0; i < m; ++i) {
            row_i[i] = RowCol(arr[i], n);
        }
    }

    // void fillCol() {
    //     for (int j = 0; j < n; ++j) {
    //         col_j[j] = RowCol(arr[j], m);
    //     }
    // }
    void fillCol() {
        for (int j = 0; j < n; ++j) {
            Element* colArr = new Element[m];
            for (int i = 0; i < m; ++i) {
                colArr[i] = arr[i][j];
            }
            col_j[j] = RowCol(colArr, m);
        }
    }

    void setCountMaxRow(int i) {
        row_i[i].setCountMaxRowCol(max);
    }
    int getCountMaxRow(int i) const { return row_i[i].getCountMaxRowCol(); }
    void setCountMaxCol(int j) {
        col_j[j].setCountMaxRowCol(max);
    }
    int getCountMaxCol(int j) const { return col_j[j].getCountMaxRowCol(); }

    void setCountMaxRowCol() {
        countMaxRowCol = row_i[0].getCountMaxRowCol();
        for (int i = 0; i < m; i++) {
            if (row_i[i].getCountMaxRowCol() > countMaxRowCol) { countMaxRowCol = row_i[i].getCountMaxRowCol(); }
        }
        for (int j = 0; j < n; j++) {
            if (col_j[j].getCountMaxRowCol() > countMaxRowCol) { countMaxRowCol = col_j[j].getCountMaxRowCol(); }
        }
    }
    int getCountMaxRowCol() const { return countMaxRowCol; }

    void zeroMaxRow(int i) {
        for (int j = 0; j < n; j++) {
            arr[i][j].setValue(0);
        }
    }    
    void zeroMaxCol(int j) {
        for (int i = 0; i < m; i++) {
            arr[i][j].setValue(0);
        }
    }    

    void zeroMaxRowCol() {
        for (int i = 0; i < m; i++) {
            if (row_i[i].getCountMaxRowCol() == countMaxRowCol) { 
                res_i = i;
                zeroMaxRow(res_i);
            }
        }
        if (res_i != -1) {
            for (int j = 0; j < n; j++) {
                if (col_j[j].getCountMaxRowCol() == countMaxRowCol) { 
                    res_j = j;
                    zeroMaxCol(res_j);
                }
            }
        }
    }

    void printRow(int i) {
        row_i[i].printRowCol();
    }
    void printCol(int j) {
        col_j[j].printRowCol();
    }

    int getMax() const { return max; } 
    int getCountMax() const { return countMaxRowCol; } 

    void fillField() {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int val;
                std::cin >> val;
                arr[i][j].setValue(val);
            }
        }
    }

    void setElement(int i, int j, int value) {
        arr[i][j].setValue(value);
    }
    int getElement(int i, int j) const { return arr[i][j].getValue(); }

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

    void printField() {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                std::cout << arr[i][j].getValue() << " ";
            }
            std::cout << std::endl;
        }
    }

};

int main() {
    int m, n;
    std::cin >> m >> n;
    Field arr(m, n);
    arr.fillField();
    arr.fillRow();
    arr.fillCol();

    
    arr.findFieldMax();
    //arr.countFieldMax();
    

    for (int i = 0; i < m; i++) {
        arr.setCountMaxRow(i);
        std::cout << "arr.getCountMaxRow(" << i << "): " << arr.getCountMaxRow(i) << std::endl;
    }

    for (int i = 0; i < n; i++) {
        arr.setCountMaxCol(i);
        std::cout << "arr.getCountMaxCol(" << i << "): " << arr.getCountMaxCol(i) << std::endl;
    }

    arr.setCountMaxRowCol();
    std::cout << "countMaxRowCol " << arr.getCountMaxRowCol() << std::endl;

    arr.zeroMaxRowCol();
    arr.printField();
    //arr.printRow(2);
    // arr.printCol(2);

    return 0;
}
