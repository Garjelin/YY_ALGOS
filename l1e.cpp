#include <iostream>

int main(void) {
    long long n, k, d;
    std::cin >> n >> k >> d;
    long long x = n; 
    int cycle_0 = 0;
    for (int i = 0; i < d; i++) {
        //std::cout << "x: " << x  << std::endl;
        if (x*10 % k == 0) {
            cycle_0 = i+1;
            break;
        }
        x *= 10;
        int not_found = 1;
        for (int j = 1; j < 10; j++) {
            if (!((x+j) % k)) {
                x += j;
                not_found = 0;
                break;
            }
        }
        if (not_found) {
            //std::cout << "x: " << x  << std::endl;
            x = -1; 
            break;
        }
    }
    std::string output = "";
    char zero = '0';
    if (cycle_0) {
        // std::cout << "x: " << x  << std::endl;
        // std::cout << "cycle_0: " << cycle_0  << std::endl;
        for (int i = 0; i < d - (cycle_0-1); i++) {
            output = output + zero;
        }
        std::cout << x << output;
    } else std::cout << x;
}