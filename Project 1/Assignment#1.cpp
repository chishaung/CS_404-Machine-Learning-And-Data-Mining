

/** Machine Learning Assignment#1 - ANN Part1 
 *  Author: Chihsiang Wang
 *  Date:   1/31/2016
 */

/**
 * Library
 */
#include <iostream>
#include <vector>
#include <math.h>

/**
 * Preproccsor
 */
#define TEST 1
#define Trainning_Times 1000
#define E 2.718
#define alpha 0.1

/**
 * NameSpace
 */
using namespace std;

/**
 * Global variables
 */
vector <vector<float> > Training_box;
vector <vector<float> > Testing_box;
float col_input;
float row_training;
float col_training;
float row_testing;
float col_testing;

/**
 * Prototype
 */
void Read_File();
void Initialization(int, int , vector <vector<float> >);
void print( vector <vector<float> >);
float Sigmoid(float);
vector <vector<float> > Mutiply(vector <vector<float> >, vector <vector<float> >);
vector <vector<float> > Transpose(vector <vector<float> >);


/**
 * [main]
 */
int main() {
	
	Read_File();



	return 0;
}

/**
 * [Read from stdin and store into training and testing matrix]
 */
void Read_File() {

  vector<float> line;
  float get;
  int num = 1;
  int tmp, tmp2;
  tmp2 = 1000;
  while (cin >> get) {

    if (get == EOF) 
      break;

    if (num == 1)
      col_input = get;

    if (num == 2)
      row_training = get;

    if (num == 3) {
      col_training = get;
      tmp = row_training * col_training + 3;
    }

    // Box of Training Data
    if (num >=4 && num < tmp+1) {


      line.push_back(get);
      if ((num - 3) % (int)col_training == 0) {
        Training_box.push_back(line);
        line.clear(); 
      }

      tmp2 = tmp;
    }

    if (num == tmp2 + 1) {
      row_testing = get;
    }


    if (num == tmp2 + 2) {
      col_testing = get;
    }

    // Box of Testimg Data
    
    if (num >= tmp2 + 3) {
      line.push_back(get);
      if ((num - tmp2 - 2) % (int)col_testing == 0) {
        Testing_box.push_back(line);
        line.clear(); 
      }
    } 

    num++;
  }

  /* Testing Block */
  if (TEST == 1) {
    cout << "TEST: TRAINING MATRIX " << endl; 
    print(Training_box); 
    cout << "TEST: TESTING MATRIX " << endl;
    print(Testing_box);
    vector <vector<float> > T;
    T = Transpose(Training_box);
    cout << "TEST: Transpose Trainging box " << endl;
    print(T);
  }
}

/**
 * [Randomly fill random float number and fill in matrix w]
 * @param inSize  [Size of Input Nodes]
 * @param OutSize [Size of Output Nodes]
 * @param w       [Matrix with random weight]
 */
void Initialization(int inSize, int OutSize, vector <vector<float> > &w) {


}


/**
 * [Sigmoid description]
 * @param  x [any float value from Matrix]
 * @return   [New Value applied Sigmoid Function]
 */
float Sigmoid(float x) {

  float value;
  value = 1 / (1 + pow(E, (-4 * x)));
  return value;
}


/**
 * [Matrix Mutiply Function]
 * Input: Matrix A and Matrix B
 * Return: A * B
 */
vector <vector<float> > Mutiply(vector <vector<float> > A, vector <vector<float> > B) {
  vector <vector<float> > Result;
	
	int A_Row, A_Column, B_Row, B_Column;
	A_Row    = A.size();
	A_Column = A[0].size();
	B_Row    = B.size();
	B_Column = B[0].size();
	vector<float> temp;


  if(A_Column != B_Row) {
    cout << "Warning!!!!! Mutiply Error!!!" << endl;
  }

  // Result is a A_Row x B_Column Matrix
  for (int i = 0; i < A_Row; i++) {
    for (int j = 0; j < B_Column; j++) {
      temp.push_back(0);
    }
    Result.push_back(temp);
    temp.clear();
  }
  // x denotes number rows in matrix A
  // y denotes number columns in matrix A
  // m denotes number rows in matrix B
  // n denotes number columns in matrix B
  int x, y, m, n, i, j;
  x = A_Row;
  y = A_Column;
  m = B_Row;
  n = B_Column;

  for(i = 0; i < x; i++)
        {
            for(j = 0; j < n; j++)
            {
                Result[i][j]=0;
                for(int k=0;k<m;k++)
                {
                    Result[i][j] = Result[i][j] + A[i][k] * B[k][j];
                }
            }
        }
  return Result;
}

/**
 * [Print Matrix]
 * @param M [vector of vector Matrix]
 */
void print( vector <vector<float> > M)
{
	for (int i = 0; i < M.size(); i++) {
    	for (int j = 0; j < M[0].size(); j++) {
      	cout << M[i][j] << "  ";
    	}
    cout << endl;
	}
}

/**
 * [Transpose the matrix]
 */
vector <vector<float> > Transpose(vector <vector<float> > M) {

	vector <vector<float> > New;

  	int height = M.size();
  	int width = M[0].size();

 
  	vector<float> Temp;

  	for (int j = 0; j < width; j++) {
    	for (int i = 0; i < height; i ++) {
      	Temp.push_back(M[i][j]);
    	}
    New.push_back(Temp);
    Temp.clear();
  	}


  	return New;
}
