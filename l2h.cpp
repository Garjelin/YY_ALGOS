#include <iostream>
#include <string>
#include <vector>

int main() {
    int m, n;
    std::cin >> m >> n;

    int** arr = new int*[m];
    for (int i = 0; i < m; ++i) {
        arr[i] = new int[n];
    }

    int max = 0;
    int max_i = 0;
    int max_j = 0;
    // int max_in_row = 0;
    // int max_in_col = 0;
    // int res_i = -1, res_j = -1;
    // std::vector<int> count_max_in_row = {0};
    // std::vector<int> count_max_in_col = {0};
    std::vector<double> weight_in_row(n, 0.0);
    std::vector<double> weight_in_col(m, 0.0);
    // int max_count_in_row = 0;
    // int max_count_in_col = 0;
    // int max_count_i = 0;
    // int max_count_j = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> arr[i][j];
            if (arr[i][j] > max) {
                max = arr[i][j];
                max_i = i;
                max_j = j;
            }
        }
    }
    for (int j = 0; j < n; j++) {
        weight_in_row[j] = (double)arr[max_i][j] / (double)max;
    }
    for (int i = 0; i < m; i++) {
        weight_in_col[i] = (double)arr[i][max_j] / (double)max;
    }

    for (int i = 0; i < m; i++) {
        std::cout << weight_in_col[i] << " ";
        // if (count_max_in_row[i] > max_count_in_row) {
        //     max_count_in_row = count_max_in_row[i];
        //     max_count_i = i;
        // }
    }
    std::cout << std::endl;
    for (int j = 0; j < n; j++) {
        std::cout << weight_in_row[j] << " ";
        // if (count_max_in_col[j] > max_count_in_col) {
        //     max_count_in_col = count_max_in_col[j];
        //     max_count_j = j;
        // }
    }
    std::cout << std::endl;
    // if ((max_count_in_row == 1) && (max_count_in_col == 1)) {
    //     for (int j = 0; j < n; j++) {
    //         weight_in_row[j] = (double)arr[max_i][j] / (double)max;
    //         // std::cout <<  weight_in_row[j] << " ";
    //     }
    //     for (int i = 0; i < m; i++) {
    //         weight_in_col[i] = (double)arr[i][max_j] / (double)max;
    //     }
    // } else {
    //     if (max_count_in_row > max_count_in_col) {
    //         res_i = max_count_i;
    //         for (int j = 0; j < n; j++) {
    //             arr[res_i][j] = 0;
    //         }
    //     } else {
    //         res_j = max_count_j;
    //         for (int i = 0; i < m; i++) {
    //             arr[i][res_j] = 0;
    //         }
    //     }
    // }
    // std::cout <<  "HERE!" << std::endl;
    // max = 0;
    // for (int i = 0; i < m; i++) {
    //     count_max_in_row[i] = 0;
    //     weight_in_col[i] = 0;
    // }
    // for (int j = 0; j < n; j++) {
    //     count_max_in_col[j] = 0;
    //     weight_in_row[j] = 0;
    // }
    // for (int i = 0; i < m; i++) {
    //     for (int j = 0; j < n; j++) {
    //         if (arr[i][j] > max) {
    //             max = arr[i][j];
    //         }
    //     }
    // }
    // for (int i = 0; i < m; i++) {
    //     for (int j = 0; j < n; j++) {
    //         if (arr[i][j] == max) {
    //             count_max_in_row[i]++;
    //             count_max_in_col[j]++;
    //         }
    //     }
    // }
    
    // max_count_in_row = 0;
    // max_count_in_col = 0;
    // max_count_i = 0;
    // max_count_j = 0;
    // for (int i = 0; i < m; i++) {
    //     // std::cout << count_max_in_row[i] << " ";
    //     if (count_max_in_row[i] > max_count_in_row) {
    //         max_count_in_row = count_max_in_row[i];
    //         max_count_i = i;
    //     }
    // }
    // for (int j = 0; j < n; j++) {
    //     // std::cout << count_max_in_col[i] << " ";
    //     if (count_max_in_col[j] > max_count_in_col) {
    //         max_count_in_col = count_max_in_col[j];
    //         max_count_j = j;
    //     }
    // }
    // if ((max_count_in_row == 1) && (max_count_in_col == 1)) {
    //     for (int j = 0; j < n; j++) {
    //         weight_in_row[j] = (double)arr[max_i][j] / (double)max;
    //         // std::cout <<  weight_in_row[j] << " ";
    //     }
    //     for (int i = 0; i < m; i++) {
    //         weight_in_col[i] = (double)arr[i][max_j] / (double)max;
    //     }
    // } else {
    //     if (res_i >= 0) {
    //         res_j = max_count_j;
    //         for (int i = 0; i < m; i++) {
    //             arr[i][res_j] = 0;
    //         }
    //     } else {
    //         res_i = max_count_i;
    //         for (int j = 0; j < n; j++) {
    //             arr[res_i][j] = 0;
    //         }
    //     }
    // }


    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < m; ++i) {
        delete[] arr[i];
    }
    delete[] arr;

    // std::cout << res_i+1 << " " << res_j+1 << std::endl;
    return 0;
}
