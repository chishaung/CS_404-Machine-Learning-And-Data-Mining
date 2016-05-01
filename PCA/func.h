#ifndef FUNC_H
#define FUNC_H

#include <vector>
using namespace std;

void Vec_to_Array(vector<vector<double> >, int , int , double**);
vector <vector<double> > Mutiply(vector <vector<double> > , vector <vector<double> > );
vector <vector<double> > Transpose(vector <vector<double> >);
void Read_File( vector <vector<double> > &);
void print( vector <vector<double> > );
void print( vector<double> );
double pythag(double a, double b);
void eigen(double *d, double *e, int n, double **z);
void eigenSystem(double *&d, int , double** );
void tridiagonalize(double *&d, double *&e, int, double**);
void householder(double **a, int n, double d[], double e[]);



#endif