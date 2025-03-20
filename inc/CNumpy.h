#ifndef _CNUMPY_H_
#define _CNUMPY_H_

#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

class CNumpy{
    private:
        int **matrix;
        int row;
        int col;

    public:
        // Part 1 [constructor/destructor, getter]
        // Constructor & Destructor
        CNumpy(string input_filename);
        ~CNumpy();

        // Getter
        int **getMatrix()const;
        int getRow()const;
        int getCol()const;


        // Part 2 [min/max, argmin/max]
        // Find the min/max value in the matrix
        int min()const;
        int max()const;

        // return the indexes where the min max first found
        void argmin(int *idx1, int *idx2);
        void argmax(int *idx1, int *idx2);

        // Part 3 [concatenate, render]
        // Concatenate the 2 matrix in place with row/col
        void quantize(int levels);
        void conv(int** kernel, int k_row, int k_col);

        // Display the matrix info in ASCII
        void render(ofstream &outfile);
};

#endif