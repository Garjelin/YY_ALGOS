#include <iostream>
#include <string>

void allocateArray(int*** arr, int rows, int cols);
void deallocateArray(int*** arr, int rows);
void fill_R(int** arr, int rows, int cols, int i, int j);
void fill_B(int** arr, int rows, int cols, int i, int j);
void printArray(int** arr, int rows, int cols);
void initialField(int** arr, int rows, int cols);
int notCovered(int** arr, int rows, int cols);

int main() {
    const int rows = 8, cols = 8;
    int **arr;
    allocateArray(&arr, rows, cols);
    initialField(arr, rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (arr[i][j] == 2) {
                fill_B(arr, rows, cols, i, j);
            }
            if (arr[i][j] == 3) {
                fill_R(arr, rows, cols, i, j);
            }
        }
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (arr[i][j] == 2 || arr[i][j] == 3) arr[i][j] = 0;
        }
    }

    int result = notCovered(arr, rows, cols);
    //printArray(arr, rows, cols);
    std::cout << result;
    deallocateArray(&arr, rows);

    return 0;
}

void allocateArray(int*** arr, int rows, int cols) {
    *arr = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        (*arr)[i] = new int[cols];
    }
}

void deallocateArray(int*** arr, int rows) {
    for (int i = 0; i < rows; ++i) {
        delete[] (*arr)[i];
    }
    delete[] *arr;
}

void printArray(int** arr, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void initialField(int** arr, int rows, int cols) {
    std::string input;
    for (int i = 0; i < rows; ++i) {
        std::getline(std::cin, input);
        for (int j = 0; j < cols; ++j) {
            if (input[j] == 'B') { 
                arr[i][j] = 2;
            } else if (input[j] == 'R'){
                arr[i][j] = 3; 
            } else arr[i][j] = 1; 
        }
    }
}

void fill_R(int** arr, int rows, int cols, int i, int j) {
    int m = i, n = j;
    
    while (m < rows-1) {
        if (arr[m+1][n] == 1) arr[m+1][n] = 0;
        if (arr[m+1][n] > 1) break;
        m++;
    }
    
    m = i, n = j;
    while (m >= 1) {
        if (arr[m-1][n] == 1) arr[m-1][n] = 0;
        if (arr[m-1][n] > 1) break;
        m--;
    }
    m = i, n = j;
    while (n < cols-1) {
        if (arr[m][n+1] == 1) arr[m][n+1] = 0;
        if (arr[m][n+1] > 1) break;
        n++;
    }
    m = i, n = j;
    while (n >= 1) {
        if (arr[m][n-1] == 1) arr[m][n-1] = 0;
        if (arr[m][n-1] > 1) break;
        n--;
    }
    
}

void fill_B(int** arr, int rows, int cols, int i, int j) {
    int m = i, n = j;
    while (m < rows-1 && n < cols-1) {
        if (arr[m+1][n+1] == 1) arr[m+1][n+1] = 0;
        if (arr[m+1][n+1] > 1) break;
        m++;
        n++;
    }
    m = i, n = j;
    while (m >= 1 && n >= 1) {
        if (arr[m-1][n-1] == 1) arr[m-1][n-1] = 0;
        if (arr[m-1][n-1] > 1) break;
        m--;
        n--;
    }
    m = i, n = j;
    while (m >= 1 && n < cols-1) {
        if (arr[m-1][n+1] == 1) arr[m-1][n+1] = 0;
        if (arr[m-1][n+1] > 1) break;
        m--;
        n++;
    }
    m = i, n = j;
    while (m < rows-1 && n >= 1) {
        if (arr[m+1][n-1] == 1) arr[m+1][n-1] = 0;
        if (arr[m+1][n-1] > 1) break;
        m++;
        n--;
    }
}

int notCovered(int** arr, int rows, int cols) {
    int result = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result += arr[i][j];
        }
    }
    return result;
}