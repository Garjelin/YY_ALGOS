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
    for (int i = 0; i < n-k; i++) {
        for (int j = 0; j < k; j++) {
            benefit[i][j] = prices[i+1] - prices[i];
        }
    }


    return 0;
}
