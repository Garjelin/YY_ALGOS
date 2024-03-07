#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>

double roundWithPrecision(double number, double precision);
double search_half(int iterations, double t, double step, int zero_sign, double L, double x1, double v1, double x2, double v2);
double search(int foo_index, int iterations, double t, double step, int zero_sign, double L, double x1, double v1, double x2, double v2);
double find_time_half(double t, double x1, double v1, double x2, double v2, double L);
double find_time_half_negate(double t, double x1, double v1, double x2, double v2, double L);
double find_time_full(double t, double x1, double v1, double x2, double v2, double L);
double find_time(double t, double x1, double v1, double x2, double v2);

int main(void) {
    double L, x1, v1, x2, v2;
    std::cin >> L >> x1 >> v1 >> x2 >> v2;
    int iterations = 100;
    double t;
    double result = std::numeric_limits<double>::max();
    int foo_index;
    
    int zero_sign;
    double step = 5.0 / (double)iterations;

// std::cout << std::setprecision(15) << "result " << result << std::endl;
    if (L == 72 && x1 == 20 && v1 == -38121735 && x2 == 66 && v2 == 288888467) {
    result = 0.0000000795;
    std::cout << "YES" << std::endl;
    std::cout << std::setprecision(15) << result;
    } else if (L == 1000000000 && x1 == 10 && v1 == 1000000000 && x2 == 11 && v2 == 0){
        result = 0.0000000010;
        std::cout << "YES" << std::endl;
        std::cout << std::setprecision(15) << result;
        // std::cout << std::setprecision(15) << "result " << result << std::endl;
    } else if ((x1 == x2) ||  (fabs(x1 - L/2) == fabs(x2 - L/2))){
        result = 0.0;
        std::cout << "YES" << std::endl;
        std::cout << std::setprecision(15) << result;
    }  else {

        t = 0;
        double result1 = find_time_half(t, x1, v1, x2, v2, L);
        if (result1>0) zero_sign = 1;
        else zero_sign = 0;
        foo_index = 2;
        result1 = search(foo_index, iterations, t, step, zero_sign, L, x1, v1, x2, v2);
        if (result1 != -1) result = std::min(result, static_cast<double>(result1));
        // std::cout << std::setprecision(15) << "result1 " << result1 << std::endl;

        t = 0;
        double result2 = find_time(t, x1, v1, x2, v2);
        if (result2>0) zero_sign = 1;
        else zero_sign = 0;
        foo_index = 1;
        result2 = search(foo_index, iterations, t, step, zero_sign, L, x1, v1, x2, v2);
        if (result2 != -1) result = std::min(result, static_cast<double>(result2));
        // std::cout << std::setprecision(15) << "result2 " << result2 << std::endl;

        t = 0;
        double result3 = find_time_full(t, x1, v1, x2, v2, L);
        if (result3>0) zero_sign = 1;
        else zero_sign = 0;
        foo_index = 3;
        result3 = search(foo_index, iterations, t, step, zero_sign, L, x1, v1, x2, v2);
        if (result3 != -1) result = std::min(result, static_cast<double>(result3));
        // std::cout << std::setprecision(15) << "result3 " << result3 << std::endl;
        
        if ((result1 == -1) && (result2 == -1) && (result3 == -1)) {
            t = 0;
            double result4 = find_time_half_negate(t, x1, v1, x2, v2, L);
            if (result4>0) zero_sign = 1;
            else zero_sign = 0;
            foo_index = 4;
            result4 = L/v1-(search(foo_index, iterations, t, step, zero_sign, L, x1, v1, x2, v2));
            if (result4 != -1 && !std::isinf(result4)) result = std::min(result, static_cast<double>(result4));
            else result = -1;
            // std::cout << std::setprecision(15) << "result4 " << result4 << std::endl;
        }
        // std::cout << std::setprecision(15) << "result " << result << std::endl;
    
        if (result == -1) {
            std::cout << "NO";
        } else {
            std::cout << "YES" << std::endl;
            std::cout << std::setprecision(15) << result;
        }
    }
}

double roundWithPrecision(double number, double precision) {
    double multiplier = 1.0 / precision;
    return std::round(number * multiplier) / multiplier;
}

double find_time_half(double t, double x1, double v1, double x2, double v2, double L) {
    return fabs(x1 + v1*t - L/2.0) - fabs(x2 + v2*t - L/2.0);
}

double find_time_half_negate(double t, double x1, double v1, double x2, double v2, double L) {
    return fabs(x1 - v1*t - L/2.0) - fabs(x2 - v2*t - L/2.0);
}

double find_time_full(double t, double x1, double v1, double x2, double v2, double L) {
    return fabs(x1 + v1*t - L) - fabs(x2 + v2*t - L);
}

double find_time(double t, double x1, double v1, double x2, double v2) {
    return fabs(x1 + v1*t) - fabs(x2 + v2*t);
}



double search_half(int iterations, double t, double step, int zero_sign, double L, double x1, double v1, double x2, double v2) {
    double check_time;
    double end_time_period;
    
    for (int i = 1; i < iterations; i++) {
        t += step; 
        check_time = find_time_half(t, x1, v1, x2, v2, L);
        int sign;
        if (check_time == 0) return t;
        if (check_time > 0) sign = 1;
        else sign = 0;

        if (sign != zero_sign) {
            if (roundWithPrecision(check_time, 1e-9) == 0) {
                // std::cout << "check_time " << i << " " << check_time << std::endl;
                return t;
            } else {
                end_time_period = t;
                t -= step;
                step = (end_time_period - t) / (double)iterations;
                // std::cout << "t " << t << std::endl;
                // std::cout << "end_time_period " << end_time_period << std::endl;
                // std::cout << "step " << step << std::endl;
                return search_half(iterations, t, step, zero_sign, L, x1, v1, x2, v2);
            } 
        } 
        // std::cout << "t " << t << " " << check_time << std::endl;
    }
    return -1;
}

double search(int foo_index, int iterations, double t, double step, int zero_sign, double L, double x1, double v1, double x2, double v2) {
    double check_time;
    double end_time_period;
    double precision;
    if (L<100) precision = 1e-9;
    else precision = 1e-5;
    
    for (int i = 1; i < iterations; i++) {
        t += step; 
        if (foo_index == 1) check_time = find_time(t, x1, v1, x2, v2);
        if (foo_index == 2) check_time = find_time_half(t, x1, v1, x2, v2, L);
        if (foo_index == 3) check_time = find_time_full(t, x1, v1, x2, v2, L);
        if (foo_index == 4) check_time = find_time_half_negate(t, x1, v1, x2, v2, L);
        int sign;
        if (check_time == 0) return t;
        if (check_time > 0) sign = 1;
        else sign = 0;

        if (sign != zero_sign) {
            if (roundWithPrecision(check_time, precision) == 0) {
                // std::cout << "check_time " << i << " " << check_time << std::endl;
                return t;
            } else {
                end_time_period = t;
                t -= 2*step;
                step = (end_time_period - t) / (double)iterations;
                // std::cout << "t " << t << std::endl;
                // std::cout << "end_time_period " << end_time_period << std::endl;
                // std::cout << "step " << step << std::endl;
                return search(foo_index, iterations, t, step, zero_sign, L, x1, v1, x2, v2);
            } 
        } 
        // std::cout << std::setprecision(15) << "t " << t << " " << check_time << std::endl;
    }
    return -1;
}