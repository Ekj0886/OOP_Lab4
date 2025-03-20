#include <bits/stdc++.h>
#include "checker.h"

#define F first 
#define S second

using namespace std;

// functions defined in header file
checker::checker(string file) {
    
    ifstream infile(file);
    infile >> row >> col;
    matrix = new int*[row];
    for(int i = 0; i < row; i++) {
        matrix[i] = new int[col];
        for(int j = 0; j < col; j++) {
            infile >> matrix[i][j]; 
        }
    }

}

checker::~checker() {
    if (matrix) {
        for (int i = 0; i < row; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
}

bool checker::check_getter(int** test_m, int test_r, int test_c) {   
    if(test_c != col || test_r != row) return false;
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            if(matrix[i][j] != test_m[i][j]) return false;
        }
    }
    return true;
}

bool checker::check_minmax(int test_min, int test_max, int min1, int min2, int max1, int max2) {
    int gold_min = INT_MAX, gold_max = INT_MIN;
    int gmin1, gmin2, gmax1, gmax2;

    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            if(matrix[i][j] > gold_max) {
                gold_max = matrix[i][j];
                gmax1 = i;
                gmax2 = j;
            }
            if(matrix[i][j] < gold_min) {
                gold_min = matrix[i][j];
                gmin1 = i;
                gmin2 = j;
            }
        }
    }

    if(gold_min != test_min || gold_max != test_max || gmin1 != min1 || gmin2 != min2 || gmax1 != max1 || gmax2 != max2) return false;
    else return true;

}

bool checker::check_quantize(int** test_m, int test_r, int test_c, int levels) {

    if(row != test_r || col != test_c) return false;

    int gmin = INT_MAX, gmax = INT_MIN;
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            gmin = min(gmin, matrix[i][j]);
            gmax = max(gmax, matrix[i][j]);
        }
    }

    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            matrix[i][j] = round( (double) matrix[i][j] * (levels - 1) / (gmax - gmin) );
            if(test_m[i][j] != matrix[i][j]) return false;
        }
    }
    return true;

}

bool checker::check_conv(int** test_m, int test_r, int test_c, int** kernel, int k_r, int k_c) {
    
    // compute golden 
    int new_r = row - k_r + 1;
    int new_c = col - k_c + 1;

    int** result;

    result = new int*[new_r];
    for(int i = 0; i < new_r; i++) {
        result[i] = new int[new_c];
        for(int j = 0; j < new_c; j++) {
            
            int sum = 0;
            for(int y = 0; y < k_r; y++) {
                for(int x = 0; x < k_c; x++) {
                    sum += matrix[i+y][j+x] * kernel[y][x];
                }
            }
            result[i][j] = sum;

        }
    }

    // Safely delete old matrix
    if (matrix) {
        for (int i = 0; i < row; i++) {
            if (matrix[i]) delete[] matrix[i];
        }
        delete[] matrix;
        matrix = nullptr;  // Prevent accidental reuse
    }

    matrix = result;
    row = new_r;
    col = new_c;

    // check
    if(row != test_r || col != test_c) return false;

    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            if(matrix[i][j] != test_m[i][j]) return false;
        }
    }
    return true;

}