#include <iostream>
#include <string>

int main() {
    int n, k;
    std::cin >> n >> k;
    int prices[n];
    for (int i = 0; i < n; i++) {
        std::cin >> prices[i];
    }
    int benefit[n][k] = {0};
    int max = 0;
    for (int i = 0; i < n; i++) {
        int d = i + 1;
        for (int j = 0; j < k; j++) {
            if (d < n) {
                benefit[i][j] = prices[d] - prices[i];
            }
            d++;
            if (benefit[i][j] > max) max = benefit[i][j];
        }
    }

    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < k; j++) {
    //         std::cout << benefit[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    std::cout << max << std::endl;
    return 0;
}
