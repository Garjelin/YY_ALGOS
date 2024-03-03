#include <iostream>

int main(void) {
    int G1T1, G1T2, G2T1, G2T2;
    char razd;
    int first_is_home;
    std::cin >> G1T1 >> razd >> G1T2;
    std::cin >> G2T1 >> razd >> G2T2;
    std::cin >> first_is_home;
    int G1_res = G1T1 - G1T2;
    int G2_res = G2T1 - G2T2;
    int res = G1_res + G2_res;

    int need_to_equal = 0 - res;
    int need_to_win = 0;
    int T1_host;
    int T2_host;
    if (need_to_equal >= 0) {
        T1_host = (first_is_home == 1) ? G2T1 + need_to_equal : G1T1;
        T2_host = (first_is_home == 1) ? G1T2 : G2T2;

        // std::cout << T1_host << std::endl;
        // std::cout << T2_host << std::endl;
        if (T1_host > T2_host) need_to_win = need_to_equal;
        else need_to_win = need_to_equal + 1;
    }
    std::cout << need_to_win;
}