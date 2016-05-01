#include "func.h"
#include <iostream>
#include <vector>   // vector
#include <math.h>   
#include <iomanip>  // setw
#include <utility>  // pair
#include <stdlib.h> 
#include <math.h> 
#include <cstdlib>
#include <stdio.h>
#include <iomanip>
#include <algorithm>

#define TEST 0
using namespace std;

static bool sort_using_greater_than(double u, double v)
{
   return u > v;
}

int main() {

	// parse input file and split it into data 2D vector
	vector <vector< double> > input;
	Read_File(input);


	// Step 1. Calc the mean and substract for each col
	int R, C;
	R = input.size();
	C = input[0].size();
	double sum = 0;
	double mean;
	vector<double> mean_for_each_col;


	for (int i = 0; i < C; i++) {

		for (int j = 0; j < R; j++) {
			sum = sum + input[j][i];
		}
		mean = sum / R;
		mean_for_each_col.push_back(mean);
		sum = 0;
	}


	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			input[i][j] -= mean_for_each_col[j];
		}
	}



	// Step 2. Comptute the Covariance matrix
	// C = 1/N (Ttranspose(B) * B)	
	vector <vector< double> > B = input;
	vector <vector< double> > Matrix_C;
	vector <vector< double> > B_T;
	B_T = Transpose(B);
	Matrix_C = Mutiply(B_T, B);
	//print(Matrix_C);



/*
	// Step extra. Convert from vector to array
	double** Array_C = new double*[Matrix_C.size()];
	for (int i = 0; i < Matrix_C[0].size(); i++) {
		Array_C[i] = new double[Matrix_C[0].size()];
	}

	Vec_to_Array(Matrix_C, Matrix_C.size(), Matrix_C[0].size(), Array_C);
*/

/*

	// Step 3. Compute eigenvalues of C as D
	//				   eigenvector of C as Array_C
	// So, Reverse(V) * C * V = D
	double *D;
	eigenSystem(D, Matrix_C[0].size(), Array_C);
	
	//vector<double> eigenvalues;
	//for (int i = 0; i < Matrix_C[0].size(); i++) {
	//	eigenvalues.push_back(D[i]);
	//}

	// Sort and Get the 10 Biggest from eigenvalues
	//sort(eigenvalues.begin(), eigenvalues.end(), sort_using_greater_than);
	
	for (int i = 0; i < Matrix_C.size(); i++) {
		for (int j = 0; j < Matrix_C[0].size(); j++) {
			cout << Array_C[i][j] << " ";
		}
		cout << endl;
	}
	
*/
	/*
	for (int i = 0; i < Matrix_C[0].size(); i++)
		cout << d[0] << ' ';
	cout << endl;
	*/
        
        
    



/*
	if (TEST == 1) {
		// Test Section
		
		cout << "MEAN: \n";
		print(mean_for_each_col);
		cout << "AFTER: \n";
		print(input);
	}
*/
	return 0;

}


