/**
 * @file vslam_code_test.cpp
 * @author Gvslam
 * @brief solve the following problems, and finish your unit test of problem 1&2
 * questions:
 * 1.print_matrix
 * 2.solve_function
 * 3.fit_line
 * @version V2.0
 * @date 2020-12-16
 *
 * @copyright Yihang.ai, Copyright (c) 2020
 *
 */

#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string.h>
#include <sys/time.h>
#include <valarray>
#include <vector>

/**
 * @brief print matrix
 * notice:
 * 1.input is a matrix (m × n , m n ∈ Z+|0) made of vectors
 * 2.assume all vectors are equal in length
 * e.g. input a matrix (4 × 3) like this
 * input: [[ 1, 2, 3 ], ->vector1
 *         [ 4, 5, 6 ], ->vector2
 *         [ 7, 8, 9 ], ->vector3
 *         [ 10,11,12]] ->vector4
 * output:[1 4 7 10 11 8 5 2 3 6 9 12] in return
 * @return std::vector<int>
 */
std::vector<int> print_matrix(const std::vector<std::vector<int>>& mtx_) {
    /// todo: your code
}

/**
 * @brief solve : f(x) = (x² - x - 0.75)^0.25,  x ∈ ℝ
 * notice:
 * 1. must be line search or trust region method, e.g. Gauss Newton
 * 2. do not use std math method:  std::sqrt, std::pow, std::abs.
 * 3. you can only use these operators "+ - × ÷"
 * @param input_ is parameter x
 * @param eps_ threshold of error
 * @param ans_ result
 * @return true successful
 * @return false unsuccessful
 */
bool solve_function(double input_, double eps_, double* ans_) {
    /// todo: your code
}

/**
 * @brief coefficients of the straight line(ℝ²)
 * notice:
 * 1.load points in point_list.txt, about 1 million points in it
 * 2.there are about 5‰ outliers(squared error > 10000) in the set
 * 3.data format in txt:
 * x1 y1
 * x2 y2
 * ...
 * xn yn
 * 3.try to get the line's coefficients, and print them out<f(x) = Ax + B>
 * 4.you can use any c/c++ standard method
 */
void fit_line() {
    /// todo: your code
    // printf A B;
}

void unit_test1() {
    /// todo: your test code for print_matrix
}

void unit_test2() {
    /// todo: your test code for solve_function
}

int main(int argc, char** argv) {
    fprintf(stdout, "\n===============problem 1================ \n");
    unit_test1();
    fprintf(stdout, "\n===============problem 2================ \n");
    unit_test2();
    fprintf(stdout, "\n===============problem 3================ \n");
    struct timeval st, ed;
    double timeuse;
    gettimeofday(&st, nullptr);
    fit_line();
    gettimeofday(&ed, nullptr);
    timeuse = ed.tv_sec - st.tv_sec + (ed.tv_usec - st.tv_usec) * 1e-6;
    fprintf(stdout, "solve cost about: %lfms\n", timeuse * 1e3);
    return 0;
}
