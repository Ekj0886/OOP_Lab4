#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include "CNumpy.h"

using namespace std;

CNumpy::CNumpy(string input_filename) {
    ifstream file(input_filename);
    if (!file) {
        cerr << "Error: Cannot open file " << input_filename << endl;
        exit(1);
    }

    file >> row >> col;
    matrix = new int*[row];
    for (int i = 0; i < row; i++) {
        matrix[i] = new int[col];
        for (int j = 0; j < col; j++) {
            file >> matrix[i][j];
        }
    }
    file.close();
}

CNumpy::~CNumpy() {
    if (matrix) {
        for (int i = 0; i < row; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
}

int **CNumpy::getMatrix() const {
    return matrix;
}

int CNumpy::getRow() const {
    return row;
}

int CNumpy::getCol() const {
    return col;
}

int CNumpy::min() const {
    int minValue = numeric_limits<int>::max();
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (matrix[i][j] < minValue) {
                minValue = matrix[i][j];
            }
        }
    }
    return minValue;
}

// Find the max value in the matrix
int CNumpy::max() const {
    int maxValue = numeric_limits<int>::min();
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (matrix[i][j] > maxValue) {
                maxValue = matrix[i][j];
            }
        }
    }
    return maxValue;
}

// Find index of first occurrence of min value
void CNumpy::argmin(int *idx1, int *idx2) {
    int minValue = min();
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (matrix[i][j] == minValue) {
                *idx1 = i;
                *idx2 = j;
                return;
            }
        }
    }
}

// Find index of first occurrence of max value
void CNumpy::argmax(int *idx1, int *idx2) {
    int maxValue = max();
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (matrix[i][j] == maxValue) {
                *idx1 = i;
                *idx2 = j;
                return;
            }
        }
    }
}

// quantize the matrices
void CNumpy::quantize(int levels){
    if (levels <= 1) {
        cerr << "Error: Quantization levels must be greater than 1." << endl;
        return;
    }
    int minValue = min();
    int maxValue = max();
    
    double step = (double)(maxValue - minValue) / (levels - 1);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            int quantizedValue = round((matrix[i][j] - minValue) / step);
            matrix[i][j] = quantizedValue;
        }
    }
}

void CNumpy::conv(int** kernel, int k_row, int k_col){
    int tmp_row = row - k_row + 1;
    int tmp_col = col - k_col + 1;
    int **result = new int*[tmp_row];
    for (int i = 0; i < tmp_row; i++) {
        result[i] = new int[tmp_col]();
    }
    
    for (int i = 0; i < tmp_row; i++) {
        for (int j = 0; j < tmp_col; j++) {
            int sum = 0;
            for (int ki = 0; ki < k_row; ki++) {
                for (int kj = 0; kj < k_col; kj++) {
                    sum += matrix[i + ki][j + kj] * kernel[ki][kj];
                }
            }
            result[i][j] = sum;
        }
    }
    
    for (int i = 0; i < row; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    matrix = result;
    row = tmp_row;
    col = tmp_col;
    
}

// Display matrix in ASCII format
void CNumpy::render(ofstream &outfile) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            outfile << matrix[i][j];
        }
        outfile << endl;
    }
}