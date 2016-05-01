#include "mat.h"
#include <iostream>
#define K 10

int main()
{
    int R, C;
    //R = 5;
    //C = 3;
    
    std::cin >> R;
    std::cin >> C;
    int data_number = R*C;
    double data[data_number];
    //double test[] = {101, 103, 107, 109, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
    for (int i = 0; i < data_number; i++) {
        std::cin >> data[i];
    }

    //Matrix x(R, C, test, "Pic");
    Matrix x(R, C, data, "Pic");

    //x.print("Read in a picture");



    Matrix M = x;
    M = M.cov();
    //M.print("Correlation");

    double mean[C];
    for (int i = 0; i < C; i++) {
        mean[i] = x.meanCol(i);    
    }
    Matrix Mean(1, C, mean, "Mean Vector");
    //Mean.print("Mean vector");

    Matrix W;
    W = M.eigenSystem();



    //W.print("eigen values");

    //M.print("eigen vectors");




    x.subRowVector(Mean);
    

    Matrix V = M;



    Matrix final;
    final = x.dotT(M);
    //final.print("X''");

    Matrix encode;
    encode = final.extract(0, 0, R, K);
    encode.print("Encoded");




    return 0;
}


