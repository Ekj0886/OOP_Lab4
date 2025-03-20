#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime> 

using namespace std;

const int SIZE_c= 111;
const int SIZE_r = 51;

int dequantize(int value) {
    return value * (256 / 10);
}
int randomizeAndDequantize(int value) {
    int dequantizedValue = dequantize(value);
    //int randomChange = rand() % 10 - 5;
    //dequantizedValue += dequantizedValue;
    if (dequantizedValue < 0) dequantizedValue = 0;
    if (dequantizedValue > 255) dequantizedValue = 255;
    return dequantizedValue;
}

int main() {
    srand(time(0));

    ifstream infile("ascii-art.txt");
    if (!infile) {
        cerr << "Error: Cannot open file." << endl;
        return 1;
    }

    ofstream outfile("output.txt");
    if (!outfile) {
        cerr << "Error: Cannot create output file 'output.txt'." << endl;
        return 1;
    }

    vector<vector<int> > matrix(SIZE_r, vector<int>(SIZE_c));

    for (int i = 0; i < SIZE_r; i++) {
        for (int j = 0; j < SIZE_c; j++) {
            char ch;
            infile >> ch;
            if (ch >= '0' && ch <= '9') {
                matrix[i][j] = ch - '0';
            } else {
                matrix[i][j] = 0;
            }
        }
    }
    infile.close();

    cout << "Writing to 'output.txt'..." << endl;
    for (int i = 0; i < SIZE_r; i++) {
        for (int j = 0; j < SIZE_c; j++) {
            matrix[i][j] = randomizeAndDequantize(matrix[i][j]);
            outfile << matrix[i][j] << " ";
        }
        outfile << endl;
    }
    outfile.close();

    cout << "Finished! Output saved to 'output.txt'." << endl;
    return 0;


}