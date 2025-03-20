#include <bits/stdc++.h>
#include"CNumpy.h"
#include "checker.h"

#define F first 
#define S second

using namespace std;

int main(int argc, char *argv[]) {

    srand(time(NULL));

    ifstream infile (argv[1]);
    ofstream outfile(argv[2]);

    for(int i = 0; i <= 10; i++) {

        string file = "testcase/matrix" + to_string(i) + ".m";
        CNumpy test(file);
        checker gold(file);

    // Check Getter
        int **test_m = test.getMatrix();
        int test_r = test.getRow();
        int test_c = test.getCol();

        if(!gold.check_getter(test_m, test_r, test_c)) {
            cout << endl;
            cout << "==============================" << endl;
            cout << "=            Fail            =" << endl;
            cout << "=        Getter Error        =" << endl;
            cout << "==============================" << endl;
            return 0;
        }

    // Check Min/Max
        int test_min = test.min(), test_max = test.max();
        int min1, min2, max1, max2;
        test.argmin(&min1, &min2);
        test.argmax(&max1, &max2);
        
        if(!gold.check_minmax(test_min, test_max, min1, min2, max1, max2)) {
            cout << endl;
            cout << "==============================" << endl;
            cout << "=            Fail            =" << endl;
            cout << "=        MinMax Error        =" << endl;
            cout << "==============================" << endl;
            return 0;
        }

    // Check Quantize
        int levels;

        if(i == 10) levels = 10;
        else levels = rand() % 25 + 8;

        test.quantize(levels);
        test_m = test.getMatrix();
        test_r = test.getRow();
        test_c = test.getCol();

        if(!gold.check_quantize(test_m, test_r, test_c, levels)) {
            cout << endl;
            cout << "==============================" << endl;
            cout << "=            Fail            =" << endl;
            cout << "=       Quantize Error       =" << endl;
            cout << "==============================" << endl;
            return 0;
        }
      
    // Check Conv
        
        if(i != 10) {

            int** kernel;
            int k_r = 3, k_c = 3;
        
            kernel = new int*[k_r];
            for(int y = 0; y < k_r; y++) {
                kernel[y] = new int[k_c];
                for(int x = 0; x < k_c; x++) {
                    kernel[y][x] = rand() % 256;
                }
            }
       
            test.conv(kernel, k_r, k_c);
            test_m = test.getMatrix();
            test_r = test.getRow();
            test_c = test.getCol();

            if(!gold.check_conv(test_m, test_r, test_c, kernel, k_r, k_c)) {
                cout << endl;
                cout << "==============================" << endl;
                cout << "=            Fail            =" << endl;
                cout << "=         Conv Error         =" << endl;
                cout << "==============================" << endl;
                for(int j = 0; j < k_r; j++) delete[] kernel[j];
                delete[] kernel;
                return 0;
            }

            for(int j = 0; j < k_r; j++) delete[] kernel[j];
            delete[] kernel;

        }
        else {
            ofstream outfile("secret_pic.txt");
            test.render(outfile);
        }
        

        cout << "Case " << i << " pass!" << endl;

    }

    cout << "==============================" << endl;
    cout << "=            Pass            =" << endl;
    cout << "=       Congratulations      =" << endl;
    cout << "==============================" << endl;

    return 0;

}

