#include "mat.h"
#include <iostream>
int main()
{


    //double test[] = {2.5, 2.4, 0.5, 0.7, 2.2, 2.9, 1.9, 2.2, 3.1, 3.0, 2.3, 2.7, 2, 1.6, 1, 1.1, 1.5, 1.6, 1.1, 0.9};
    //double test[] = {0.69, 0.49, -1.31, -1.21, 0.39, 0.99, 0.09, 0.29, 1.29, 1.09, 0.49, 0.79, 0.19, -0.31, -0.81, -0.81, -0.31, -0.31, -0.71, -1.01};
    double test[] = {101, 103, 107, 109, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
    //double test[] = {1450.24, 458.24, 426.24, 458.24, 1066.24, 1074.24, 426.24, 1074.24, 1083.84};

    Matrix x(5, 3, test, "T");
    x.print("Before");



    Matrix y = x;
    y = y.cov();
    y.print("Correlation");




    double *d;
    y.eigenSystem(d);
    std::cout << d[0] << std::endl;
    Matrix dd(1, 3, d, "D");  // convert double * to matrix

    dd.print("eigen values");

    y.print("eigen vectors");



/*
    double p[] = {0.6779, 0.7352};
    Matrix p1(2, 1, p, "P");
    y = x.dot(p1);
    y.print("LAST");
    */
    //normalize(y);
    //y.print("After normalize.");
/*
    Matrix x(4, 4, m, "M");
//    Matrix h(4, 4, z, "H");
    Matrix emptyMatrix(0, 0, "Empty Matrix");
    Matrix y;
    Matrix B(2, 4, b, "B");

    y = x;
    y.print("before");
    //y.transposeSelf();
    y = y.cov();
    y.print("after");

    double *d;

    y.eigenSystem(d);
    
    Matrix dd(1, 4, d, "D");  // convert double * to matrix
    dd.print("eigen values");

    y.print("eigen vectors");

    x.print();
    B = B.transpose();
    x.solve(B);
    x.print("inverse");
    B.print("ans");

    x.inverse();
    x.print("re-inverse");
//    x.LU();
//    x.print("original");
*/
    return 0;
}


