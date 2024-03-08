#include <iostream>
#include <string>

int main() {
    int n;
    std::cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    int max = 0;
    //int ind_max;
    int sum = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
            //ind_max = i;
            
        }
        sum += arr[i];
    }
    int result;
    if ((sum-max)<max) {
        result = 2*max - sum;
    } else result = sum;


    std::cout << result << std::endl;
    return 0;
}
