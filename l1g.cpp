#include <iostream>
#include <limits>

int scenario_destroy_building(int x, int y, int p);
int scenario_kill_soldiers(int x, int y, int p);
int scenario_first_kill_then_destroy_1(int x, int y, int p, int n);
int scenario_first_kill_then_destroy_2(int x, int y, int p);
void first_hit(int *x, int *y, int *p, int *enemy_soldiers);
void atack(int *target, int *second_target, int x);

int main(void) {
    int x, y, p;
    std::cin >> x >> y >> p;
    
    // int result_1 = scenario_destroy_building(x, y, p);
    // int result_3 = scenario_first_kill_then_destroy_2(x, y, p);
    int result = std::numeric_limits<int>::max();
    int flag_loose = 1;
    for (int n = 2; n < 5000; n++) {
        int result_tmp = scenario_first_kill_then_destroy_1(x, y, p, n);
        if (result_tmp != -1) {
            result = std::min(result, result_tmp);
            flag_loose = 0;
        }
    }
    if (flag_loose) result = -1;
    
    // 
    // if ((result_1 == -1) && (result_2 == -1) && (result_3 == -1)) {
    //     result = -1;
    // } else {
        
    //     if (result_1 != -1) result = std::min(result, result_1);
    //     if (result_2 != -1) result = std::min(result, result_2);
    //     if (result_3 != -1) result = std::min(result, result_3);
    // }
    // // std::cout << "result_1: " << result_1 << std::endl;
    // // std::cout << "result_2: " << result_2 << std::endl;
    // // std::cout << "result_3: " << result_3 << std::endl;
    
    std::cout << result;

}

int scenario_destroy_building(int x, int y, int p) {
    int enemy_soldiers = 0;
    int i = 1;
    first_hit(&x, &y, &p, &enemy_soldiers);
    while (y > 0 || enemy_soldiers > 0) {
        i++;
        // std::cout << std::endl;
        // std::cout << "------------------------------" << std::endl;
        // std::cout << "i: " << i << std::endl;
        // std::cout << "our_soldiers_before_atack: " << x << std::endl;
        atack(&y, &enemy_soldiers, x);
        // std::cout << "y: " << y << std::endl;
        // std::cout << "enemy_soldiers_before_atack: " << enemy_soldiers << std::endl;
        x = x - enemy_soldiers;
        if (x < 0) {
            x = 0;
            i = -1;
            break;
        }
        // std::cout << "our_soldiers_after_enemy_atack: " << x << std::endl;
        if (y>0) enemy_soldiers = enemy_soldiers + p;
        // std::cout << "enemy_soldiers_after_recruiting: " << enemy_soldiers << std::endl;
    }
    return i;
}

int scenario_kill_soldiers(int x, int y, int p) {
    if (x<=p) return -1;
    int enemy_soldiers = 0;
    int i = 1;
    first_hit(&x, &y, &p, &enemy_soldiers);
    while (y > 0 || enemy_soldiers > 0) {
        i++;
        // std::cout << std::endl;
        // std::cout << "------------------------------" << std::endl;
        // std::cout << "i: " << i << std::endl;
        // std::cout << "our_soldiers_before_atack: " << x << std::endl;
        atack(&enemy_soldiers, &y, x);
        // std::cout << "y: " << y << std::endl;
        // std::cout << "enemy_soldiers_before_atack: " << enemy_soldiers << std::endl;
        x = x - enemy_soldiers;
        if (x < 0) {
            x = 0;
            i = -1;
            break;
        }
        // std::cout << "our_soldiers_after_enemy_atack: " << x << std::endl;
        if (y>0) enemy_soldiers = enemy_soldiers + p;
        // std::cout << "enemy_soldiers_after_recruiting: " << enemy_soldiers << std::endl;
    }
    return i;
}

int scenario_first_kill_then_destroy_1(int x, int y, int p, int n) {
    //if (x<=p) return -1;
    int enemy_soldiers = 0;
    int i = 1;
    first_hit(&x, &y, &p, &enemy_soldiers);
    while (y > 0 || enemy_soldiers > 0) {
        i++;
        // std::cout << std::endl;
        // std::cout << "------------------------------" << std::endl;
        // std::cout << "i: " << i << std::endl;
        // std::cout << "our_soldiers_before_atack: " << x << std::endl;
        if (i>=n) atack(&y, &enemy_soldiers, x); 
        else atack(&enemy_soldiers, &y, x);
        // std::cout << "y: " << y << std::endl;
        // std::cout << "enemy_soldiers_before_atack: " << enemy_soldiers << std::endl;
        x = x - enemy_soldiers;
        if (x < 0) {
            x = 0;
            i = -1;
            break;
        }
        // std::cout << "our_soldiers_after_enemy_atack: " << x << std::endl;
        if (y>0) enemy_soldiers = enemy_soldiers + p;
        // std::cout << "enemy_soldiers_after_recruiting: " << enemy_soldiers << std::endl;
    }
    return i;
}

int scenario_first_kill_then_destroy_2(int x, int y, int p) {
    if (x<=p) return -1;
    int enemy_soldiers = 0;
    int i = 1;
    first_hit(&x, &y, &p, &enemy_soldiers);
    while (y > 0 || enemy_soldiers > 0) {
        i++;
        // std::cout << std::endl;
        // std::cout << "------------------------------" << std::endl;
        // std::cout << "i: " << i << std::endl;
        // std::cout << "our_soldiers_before_atack: " << x << std::endl;
        if (y<p) atack(&y, &enemy_soldiers, x); 
        else atack(&enemy_soldiers, &y, x);
        // std::cout << "y: " << y << std::endl;
        // std::cout << "enemy_soldiers_before_atack: " << enemy_soldiers << std::endl;
        x = x - enemy_soldiers;
        if (x < 0) {
            x = 0;
            i = -1;
            break;
        }
        // std::cout << "our_soldiers_after_enemy_atack: " << x << std::endl;
        if (y>0) enemy_soldiers = enemy_soldiers + p;
        // std::cout << "enemy_soldiers_after_recruiting: " << enemy_soldiers << std::endl;
    }
    return i;
}

void first_hit(int *x, int *y, int *p, int *enemy_soldiers) {
    // std::cout << std::endl;
    // std::cout << "------------------------------" << std::endl;
    // std::cout << "i: " << 1 << std::endl;
    // std::cout << "our_soldiers_before_atack: " << *x << std::endl;
    *y = *y - *x;
    if (*y<=0) {
        *enemy_soldiers = *enemy_soldiers + *y; 
        if (*enemy_soldiers < 0) *enemy_soldiers = 0;
        *y = 0;
    } else *enemy_soldiers = *p;
    // std::cout << "y: " << *y << std::endl;
}

void atack(int *target, int *second_target, int x) {
    *target -= x;
    if (*target<0) {
        *second_target += *target; 
        if (*second_target < 0) *second_target = 0;
        *target = 0;
    }
}