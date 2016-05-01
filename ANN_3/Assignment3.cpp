

/** Machine Learning Assignment#3 - ANN 
 *  Author: Chihsiang Wang
 *  Date:   2/22/2016
 */

/**
 * Library
 */
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

/**
 * Preproccsor
 */
#define TEST 0            // Test switch 1 -> on 0 -> off
#define Trainning_Times 230000   // times for training
#define E 2.718             // for the sigmoid function
#define alpha 0.2           // learning rate

/**
 * NameSpace
 */
using namespace std;

/**
 * Global variables
 */
vector <vector<float> > input_vec;
vector <vector<float> > Test_X;
pair <vector <vector<float> >, vector <vector<float> > > Training_pair;
int col_input;
int num_input;
int column_num_input;
int num_test;
int column_num_test;
//vector <vector<float> > v;
//vector <vector<float> > w;
vector <vector<float> > result;
vector <float> Case;
vector <float> y;
vector <float> layer1;
vector <float> Test_Data;
int inSize;
int hiddenSize;
int outSize;

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
void intiWeight(vector <vector<float> > &,vector <vector<float> > &);
void Adjust(vector <vector<float> >&, vector <vector<float> >&, vector<float>, vector <vector<float> > );
vector<vector<float> > Forward(vector<vector<float> >, vector<vector<float> >, vector<vector<float> >);

/**
 * [main]
 */
int main() {

  srand((unsigned)time(NULL));
	vector <vector<float> > w;
  vector <vector<float> > v;
  vector <vector<float> > x;
  vector <float> result;
	vector <vector<float> > res;
  Read_File();
  intiWeight(v, w);
  //w = Initialization(4, 3);

  //cout << "INSize: " << inSize << endl;
  //cout << "HIDDENSize: " << hiddenSize << endl;
  //cout << "OUTSize: " << outSize << endl;
  // Inner testing
  if (TEST == 1) {
    cout << "TEST: Original Weight Matrix W" << endl;
    print_float(w);
    cout << "TEST: Original Weight Matrix V" << endl;
    print_float(v);
  }

  int training_index = 0;

  for (int i = 0; i < Trainning_Times; i++) {

    //int training_index;
    //training_index = rand() % num_input;
    x.push_back(input_vec[training_index]);
    for (int j = 0; j < outSize; j++) {
      x[0].pop_back();
    }

    for (int j = col_input; j < column_num_input; j++) {
      result.push_back(input_vec[training_index][j]);
    }
//print_vector(result);
    //cout << "INDEX: " << training_index << endl;
    //cout << "OUTPUT: "; print_vector(result);  

    Adjust(v, w, result, x);

    training_index++;
    if (training_index == num_input)
      training_index = 0;

    x.clear();
    result.clear();
  }

  if (TEST == 1) {
    cout << "TEST: After Training W" << endl;
    print_float(w);
  }

  vector<float> please;
  vector <vector<float> > please2;
  vector <vector<float> > showtime;
  vector <vector<int> > showtime2;



  cout << "BEGIN TESTING" << endl;
  for (int k = 0; k < num_test; k++) {
    please2.push_back(Test_X[k]);
    please2 = Forward(please2, v, w);
    showtime.push_back(please2[0]);
    
    //print_float(please2);
    please2.clear();
  }

  //print_float(showtime);
  for (int n = 0; n < showtime.size(); n++) {
    for (int o = 0; o < showtime[0].size(); o++) {
      if (showtime[n][o] >= 0.5) 
        showtime[n][o] = 1;
      else 
        showtime[n][o] = 0;
    }
  }
  //print_float(showtime);

  for (int n = 0; n < Test_X.size(); n++) {
    for (int o = 0; o < showtime[0].size(); o++) {
      Test_X[n].push_back(showtime[n][o]);
    }
  }
    for (int n = 0; n < Test_X.size(); n++) {
      for (int o = 0; o < Test_X[0].size(); o++) {
        cout << setiosflags(ios::fixed) << setprecision(2) << (float)Test_X[n][o] << ' ';
      }
      cout << endl;
    }
  
 
	return 0;
}

vector<vector<float> > Forward(vector<vector<float> > x, vector<vector<float> > v, vector<vector<float> > w) {



  vector <vector<float> > delta1;
  vector <vector<float> > delta2;
  vector<float> t;
  vector <vector<float> > layer1;
  vector <vector<float> > layer2;
  vector <vector<float> > y;
  x[0].insert(x[0].begin(), -1);
  //print(x);
  layer1 = Mutiply(x, v);
  //print_float(layer1);
  layer1[0].insert(layer1[0].begin(), -1);

  for (int i = 0; i < layer1.size(); i++) {
    for (int j = 0; j < layer1[0].size(); j++) {
      layer1[i][j] = Sigmoid(layer1[i][j]); 
    }
  }
  //layer1[0].insert(layer1[0].begin(), -1);


  layer2 = Mutiply(layer1, w);

  for (int i = 0; i < layer2.size(); i++) {
    for (int j = 0; j < layer2[0].size(); j++) {
      layer2[i][j] = Sigmoid(layer2[i][j]); 
    }
  }
  

  return layer2;
}


void Adjust(vector <vector<float> > &v, vector <vector<float> > &w, vector<float> result, vector <vector<float> > x) {

  vector <vector<float> > delta1;
  vector <vector<float> > delta2;
  vector<float> t;
  vector <vector<float> > layer1;
  vector <vector<float> > layer2;
  vector <vector<float> > y;
  x[0].insert(x[0].begin(), -1);
  
  layer1 = Mutiply(x, v);
  //print_float(layer1);
  layer1[0].insert(layer1[0].begin(), -1);

  for (int i = 0; i < layer1.size(); i++) {
    for (int j = 0; j < layer1[0].size(); j++) {
      layer1[i][j] = Sigmoid(layer1[i][j]); 
    }
  }
  //layer1[0].insert(layer1[0].begin(), -1);


  layer2 = Mutiply(layer1, w);
  
  for (int i = 0; i < layer2.size(); i++) {
    for (int j = 0; j < layer2[0].size(); j++) {
      layer2[i][j] = Sigmoid(layer2[i][j]); 
    }
  }

  t = result;
  y = layer2;



  // To get Dealta 2:
  // Delta2 is 1 x outSize
  vector<float> delta_temp;
  float value;
  for (int i = 0; i < outSize; i++) {
    value = (t[i] - y[0][i]) * y[0][i] * (1 - y[0][i]);
    delta_temp.push_back(value);
  }
  delta2.push_back(delta_temp);
  delta_temp.clear();

  vector <vector<float> > trans_w;
  trans_w = Transpose(w);



  // To get Delta 1:
  // delta1 =( layer1 (1 - layer1)) ( delta2 . Transpose[w]);
  // w is 4 x 3, trans(w) is 3 x 4
  // delta2 . trans(w) is 1 x 4 
  
  vector <vector<float> > delta1_part;

  delta1_part = Mutiply(delta2, Transpose(w));

//////////////////////////////////////////////////////////////
  vector<float> temp_delta1;
  for (int i = 0; i < layer1[0].size(); i++) {
    temp_delta1.push_back((layer1[0][i] * (1 - layer1[0][i])) * delta1_part[0][i]);
  }
  delta1.push_back(temp_delta1);
  temp_delta1.clear();


  ///////////////////////////////////^^^^^^^


  // delta1 and delta2

  vector <vector<float> > temp_v_weight; // 5 x 3
  vector <vector<float> > temp_w_weight; // 4 x 3
  vector <vector<float> > t_layer1; // 4 x 1
  vector<float> temp_w;
  t_layer1 = Transpose(layer1);

    for (int k = 0; k < hiddenSize+1; k++) {

      for (int j = 0; j < delta2[0].size(); j++) {
      temp_w.push_back(t_layer1[k][0] * delta2[0][j]);
      }
      temp_w_weight.push_back(temp_w);
      temp_w.clear();

    }

    /////////////////////////////////////
    
    for (int i = 0; i < w.size(); i++) {
      for (int j = 0; j < w[0].size(); j++) {
        w[i][j] = w[i][j] + alpha * temp_w_weight[i][j];
      }
    }



    // Gte new w


    vector<vector<float> > new_delta1;
    vector<float> n_d1_t;
    vector <vector<float> > t_x;
    t_x = Transpose(x);

    for (int i = 1; i < delta1[0].size(); i++) {
      n_d1_t.push_back(delta1[0][i]);
    }
    new_delta1.push_back(n_d1_t);



    for (int k = 0; k < inSize+1; k++) {


      for (int j = 0; j < new_delta1[0].size(); j++) {
        temp_w.push_back(t_x[k][0] * new_delta1[0][j]);
      }
      temp_v_weight.push_back(temp_w);
      temp_w.clear();
    }

    //cout << "v" << endl;
    //print_float(v);
    //cout << "And" << endl;
    //print_float(temp_v_weight);

    for (int i = 0; i < v.size(); i++) {
      for (int j = 0; j < v[0].size(); j++) {
        //cout << "problems?" << endl;
        v[i][j] = v[i][j] + alpha * temp_v_weight[i][j];
      }
    }

//cout << "END2?" << endl;

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
    output.push_back(input_vec[index][i]);
  }


  return output;
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
      hiddenSize = get;

    if (num == 3)
      num_input = get;

    if (num == 4) {
      column_num_input = get;
      tmp = num_input * column_num_input + 4;
    }

    // Box of Training Data
    if (num >=5 && num < tmp+1) {


      line.push_back(get);
      if ((num - 4) % (int)column_num_input == 0) {
        input_vec.push_back(line);
        line.clear(); 
      }

      tmp2 = tmp;
    }

    if (num == tmp2 + 1) {
      num_test = get;
    }


    if (num == tmp2 + 2) {
      column_num_test = get;
    }

    // Box of Testimg Data
    
    if (num >= tmp2 + 3) {
      line.push_back(get);
      if ((num - tmp2 - 2) % (int)column_num_test == 0) {
        Test_X.push_back(line);
        line.clear(); 
      }
    } 

    num++;
  }

    inSize = col_input;
    hiddenSize = 3;
    outSize = 3;
/*
  for (int i = 0; i < num_input; i++) {
    for (int j = 0; j < column_num_input/2; j++) {
      Training_pair = make_pair(input_vec[j], input_vec[j+3]);
    }

  }
*/
  /* Testing Block */
  if (TEST == 1) {
    cout << "TEST: TRAINING MATRIX " << endl; 
    print(input_vec); 
    cout << "TEST: TESTING MATRIX " << endl;
    print(Test_X);
    vector <vector<float> > T;
    //T = Transpose(input_vec);
    //cout << "TEST: Transpose Trainging box " << endl;
    //print(T);
  }
}

/**
 * [Randomly fill random float number and fill in matrix w]
 * @param inSize  [Size of Input Nodes]
 * @param OutSize [Size of Output Nodes]
 * @param w       [Matrix with random weight]
 */
void intiWeight(vector <vector<float> > &v,vector <vector<float> > &w) {


  vector<float> temp;

  // Set up the Weight Range
  float weightRange = 1 / sqrt(2);
  RandomFloat(-weightRange, weightRange); 
  // Fill up 5 x 3 matrix 'v'
  for (int i = 0; i < inSize+1; i++) {
    for (int j = 0; j < hiddenSize; j++) {
      temp.push_back(RandomFloat(-weightRange, weightRange));
    }
    v.push_back(temp);
    temp.clear();
  }

  // Fill up 4 x 3 matrix 'w'
  for (int i = 0; i < hiddenSize + 1; i++) {
    for (int j = 0; j < outSize; j++) {
      temp.push_back(RandomFloat(-weightRange, weightRange));
    }
    w.push_back(temp);
    temp.clear();
  }

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
