#include <iostream>
#include <string>

void allocateArray(long long** arr, int n);
void deallocateArray(long long* arr);
void printArray(long long* arr, int n);
void initialField(long long* arr, int n);

int main() {
    int n;
    std::cin >> n;
    long long *arr;
    std::string output = "";
    allocateArray(&arr, n);
    initialField(arr, n);
    long long res = arr[0];
    for (int i = 1; i < n; i++) {
        if ((res%2 != 0) && (arr[i]%2 != 0)) {
            res = res * arr[i];
            output = output + 'x';
        } else {
            res = res + arr[i];
            output = output + '+';
        }
    }
    
    //std::cout << res << std::endl;
    std::cout << output << std::endl;

    //printArray(arr, n);
    deallocateArray(arr);

    return 0;
}

void allocateArray(long long** arr, int n) {
    *arr = new long long[n];
}

void deallocateArray(long long* arr) {
    delete[] arr;
}

void printArray(long long* arr, int n) {
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " ";
    }
}

void initialField(long long* arr, int n) {
    for (int i = 0; i < n; ++i) {

        std::cin >> arr[i];
    }
}
