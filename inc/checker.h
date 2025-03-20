#ifndef CHECKER_H
#define CHECKER_H
#include <bits/stdc++.h>

#define F first 
#define S second

using namespace std;

class checker {

private:
    int **matrix;
    int row;
    int col;
    
public:
    checker(string file);
    ~checker();

    bool check_getter(int** test_m, int test_r, int test_c);
    bool check_minmax(int test_min, int test_max, int min1, int min2, int max1, int max2);
    bool check_quantize(int** test_m, int test_r, int test_c, int levels);
    bool check_conv(int** test_m, int test_r, int test_c, int** kernel, int k_r, int k_c);
};

#endif