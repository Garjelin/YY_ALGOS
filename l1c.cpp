#include <iostream>

int main(void) {
    int n;
    std::cin >> n;
    int a[n];
    for (int i = 0; i < n; i++) std::cin >> a[i];
    long long count_press = 0;
    for (int i = 0; i < n; i++) {
        count_press += a[i]/4;
        int remain = a[i] % 4;
        if (remain == 3) count_press += 2;
        else count_press += remain;
    }
    std::cout << count_press;
}