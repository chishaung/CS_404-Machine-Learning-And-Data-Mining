

/** Machine Learning Assignment#1 - ANN Part1 
 *  Author: Chihsiang Wang
 *  Date:   1/31/2016
 */

/**
 * Library
 */
#include <iostream>
#include <vector>   // vector
#include <math.h>   
#include <iomanip>  // setw
#include <utility>  // pair

/**
 * Preproccsor
 */
#define TEST 1              // Test switch 1 -> on 0 -> off
#define Trainning_Times 1   // times for training
#define E 2.718             // for the sigmoid function
#define alpha 0.1           // learning rate

/**
 * NameSpace
 */
using namespace std;

/**
 * Global variables
 */
vector <vector<float> > Training_box;
vector <vector<float> > Testing_box;
pair <vector <vector<float> >, vector <vector<float> > > Training_pair;
float col_input;
float row_training;
float col_training;
float row_testing;
float col_testing;

/**
 * Prototype
 */
void Read_File();
vector <vector<float> > Initialization(int, int);
void print( vector <vector<float> >);
void print_float( vector <vector<float> >);
float Sigmoid(float);
float RandomFloat(float, float);
vector <vector<float> > Mutiply(vector <vector<float> >, vector <vector<float> >);
vector <vector<float> > Transpose(vector <vector<float> >);
void Training(vector <vector<float> > &);
vector <float> Step_Function(int);
void print_vector( vector<float> );


/**
 * [main]
 */
int main() {

  srand((unsigned)time(NULL));
	vector <vector<float> > w;
	vector <vector<float> > res;
  Read_File();
  w = Initialization(4, 3);

  // Inner testing
  if (TEST == 1) {
    cout << "TEST: Original Weight Matrix " << endl;
    print_float(w);
  }

  Training(w);


/*
vector <vector<float> > test;
vector<float> ok;
ok.push_back(0);
ok.push_back(1);
ok.push_back(1);
ok.push_back(1);
test.push_back(ok);
  res = Mutiply(test, w);

cout << "Well: " << endl;
print_float(res);
*/
	return 0;
}

void print_vector( vector<float> vec) {
  for (vector<float>::iterator it = vec.begin(); it < vec.end(); ++it) {
    cout << *it << ' ';
  }
  cout << endl;
}

/**
 * [Simple step function]
 * @param index [the index from training box]
 */
vector <float> Step_Function(int index) {
  vector <float> output;

  for (int i = 3; i < 6; i++) {
    output.push_back(Training_box[index][i]);
  }


  return output;
}

/**
 * [Training]
 * @param w [return a new weight]
 */

void Training(vector <vector<float> > &w) {

  int training_index;
  vector<float> train_in;
  vector<float> train_out;
  vector<float> error_rate;
  vector <vector<float> > temp;
  vector <vector<float> > delta;
  vector <vector<float> > layer1;
  // Start Training
  for (int i = 0; i < Trainning_Times; i++) {

    // Randomly pick a index from training box
    training_index = rand() % (int)row_training;
    for (int i = 0; i < col_input; i++) {
      train_in.push_back(Training_box[training_index][i]);
    }
    // Adding bias node
    train_in.push_back(-1);
    // Get the target outpt
    train_out = Step_Function(training_index);


    layer1.push_back(train_in);
    layer1 = Mutiply(layer1, w);
    // now layer1 = 1 x 3 target output

    for (int i = 0; i < layer1[0].size(); i++) {
      layer1[0][i] = Sigmoid(layer1[0][i]);
    }

    cout << "TEST: Layer1" << endl;
    print_float(layer1);
    Part;

    part = train_out[0~2] 

    alpha * (layer1[] - train_out[]) * 
/*
    error_rate.push_back(
    (train_out[0] - Sigmoid(temp[0][0])) * Sigmoid(temp[0][0]) * (1 - Sigmoid(temp[0][0]))
    );
    error_rate.push_back(
    (train_out[1] - Sigmoid(temp[0][1])) * Sigmoid(temp[0][1]) * (1 - Sigmoid(temp[0][1]))
    );
    error_rate.push_back(
    (train_out[2] - Sigmoid(temp[0][2])) * Sigmoid(temp[0][2]) * (1 - Sigmoid(temp[0][2]))
    );
  */
    //delta.push_back(error_rate);

    //temp = Mutiply(); 

    // here we are starting to adjust the weight
    //error_rate.push_back(Sigmoid(temp[0][0]) - train_out[0]);
    //error_rate.push_back(Sigmoid(temp[0][1]) - train_out[1]);
    //error_rate.push_back(Sigmoid(temp[0][2]) - train_out[2]);
    //print_vector(error_rate);    

    // Problem: how to get back for new weight ?

  }

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

/*
  for (int i = 0; i < row_training; i++) {
    for (int j = 0; j < col_training/2; j++) {
      Training_pair = make_pair(Training_box[j], Training_box[j+3]);
    }

  }
*/
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
vector <vector<float> > Initialization(int inSize, int OutSize) {
  vector <vector<float> > w;
  vector<float> temp;

  // Set up the Weight Range
  float weightRange = 1 / sqrt(2);
  RandomFloat(-weightRange, weightRange); 

  // 4 x 3 Weight Matrix
  for (int i = 0; i < inSize; i++) {
    for (int j = 0; j < OutSize; j++) {
      temp.push_back(RandomFloat(-weightRange, weightRange));
    }
    w.push_back(temp);
    temp.clear();
  }

  return w;
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
 * [Randomly pick 0.1~0.7 or -0.1~-0.7]
 * @param  lower [Low Bound]
 * @param  upper [High Bound]
 * @return       [random float]
 */
float RandomFloat(float lower, float upper)
{ 

  float temp;
  temp = rand() * (upper-lower) / RAND_MAX + lower;

  return temp;
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
 * [Print Matrix with float using setw]
 * @param M [vector of vector Matrix]
 */
void print_float( vector <vector<float> > M)
{
  for (int i = 0; i < M.size(); i++) {
      for (int j = 0; j < M[0].size(); j++) {
        cout << setw(10) << M[i][j] << "  ";
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
