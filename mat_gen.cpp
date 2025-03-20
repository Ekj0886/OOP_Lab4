#include <bits/stdc++.h>

#define F first 
#define S second

using namespace std;

int main(int argc, char *argv[]) {

    srand(time(NULL));

    for(int i = 1; i < 10; i++) {
        string file_name = "testcase/matrix" + to_string(i) + ".m";
        ofstream outfile(file_name);
        int row = rand() % 100 + 1;
        int col = rand() % 100 + 1;
        outfile << row << " " << col << endl;
        for(int r = 0; r < row; r++) {
            for(int c = 0; c < col; c++) {
                outfile << rand() % 256 << " ";
            }
            outfile << endl;
        }
    } 

    return 0;

}