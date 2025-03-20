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
        // Constructor & Destructor
        CNumpy(string input_filename);
        ~CNumpy();

        // Getter
        int **getMatrix()const;
        int getRow()const;
        int getCol()const;

        // Find the min/max value in the matrix
        int min()const;
        int max()const;

        // return the indexes where the min max first found
        void argmin(int *idx1, int *idx2);
        void argmax(int *idx1, int *idx2);

        // Quantize element with levels
        void quantize(int levels);

        // Perform convolution using kernel 
        void conv(int** kernel, int k_row, int k_col);

        // Display matrix 
        void render(ofstream &outfile);
};

#endif