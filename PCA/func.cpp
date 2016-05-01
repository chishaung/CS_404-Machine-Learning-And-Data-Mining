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
#define SIGN(a, b) ((b) >= 0.0 ? fabs(a) : -fabs(a))
using namespace std;


void householder(double **a, int n, double d[], double e[])
{
    int l, k, j, i;
    double scale, hh, h, g, f;

    for (i=n-1; i>=1; i--) {
        l=i-1;
        h=scale=0.0;
        if (l > 0) {
            for (k=0; k<=l; k++) {
                scale += fabs(a[i][k]);
            }

            if (scale == 0.0) {             // Skip transformation.
                e[i]=a[i][l];
            }
            else {
                for (k=0; k<=l; k++) {
                    a[i][k] /= scale;       // Use scaled a's for transformation.
                    h += a[i][k]*a[i][k];   // Form sigma in h.
                }
                f=a[i][l];
                g=(f >= 0.0 ? -sqrt(h) : sqrt(h));
                e[i]=scale*g;
                h -= f*g;                   // Now h is equation (11.2.4).
                a[i][l]=f-g;                // Store u in the ith row of a.
                f=0.0;
                for (j=0; j<=l; j++) {
                    // Next statement can be omitted if eigenvectors not wanted
                    a[j][i]=a[i][j]/h;      // Store u/H in ith column of a.

                    g=0.0;                  // Form an element of A.u in g.
                    for (k=0; k<=j; k++) {
                        g += a[j][k]*a[i][k];
                    }
                    for (k=j+1; k<=l; k++) {
                        g += a[k][j]*a[i][k];
                    }

                    e[j]=g/h;               // Form element of p in temporarily unused element of e.
                    f += e[j]*a[i][j];
                }
                hh=f/(h+h);                 // Form K, equation (11.2.11).

                // Form q and store in e overwriting p.
                for (j=0; j<=l; j++) {
                    f=a[i][j];
                    e[j]=g=e[j]-hh*f;

                    // Reduce a, equation (11.2.13).
                    for (k=0; k<=j; k++) {
                        a[j][k] -= (f*e[k] + g*a[i][k]);
                    }
                }
            }
        }
        else {
            e[i]=a[i][l];
        }
        d[i]=h;
    }

    // Next statement can be omitted if eigenvectors not wanted
    d[0]=0.0;
    e[0]=0.0;

    // Contents of this loop can be omitted if eigenvectors not
    //   wanted except for statement d[i]=a[i][i];

    // Begin accumulation of transformation matrices.
    for (i=0; i<n; i++) {
        l=i-1;
        if (d[i]) {                        // This block skipped when i=0.
            for (j=0; j<=l; j++) {
                // Use u and u/H stored in a to form P.Q.
                g=0.0;
                for (k=0; k<=l; k++) {
                    g += a[i][k]*a[k][j];
                }
                for (k=0; k<=l; k++) {
                    a[k][j] -= g*a[k][i];
                }
            }
        }
        d[i]=a[i][i];                       // This statement remains.
        a[i][i]=1.0;                        // Reset row and column of a to identity matrix for next iteration.
        for (j=0; j<=l; j++) {
            a[j][i]=a[i][j]=0.0;
        }
    }
}

// tri-diagonalize a symmetric matrix.  The matrix will be destroyed and
// the diagonal will be returned in d and off diagonal in e.   It uses
// the Householder transformation
void tridiagonalize(double *&d, double *&e, int maxc, double** m)
{
    
    d = new double [maxc];  // the diagonal elements
    e = new double [maxc];  // the off-diagonal elements

    householder(m, maxc, d, e);
}


void eigenSystem(double *&d, int maxc, double** m)
{
    double *e;


    tridiagonalize(d, e, maxc, m);
    eigen(d, e, maxc, m);

    delete e;
}


double pythag(double a, double b)
{
    double absa, absb;
    absa=fabs(a);
    absb=fabs(b);
    if (absa > absb) return absa*sqrt(1.0+(absb/absa)*(absb/absa));
    else return (absb == 0.0 ? 0.0 : absb*sqrt(1.0+(absa/absb)*(absa/absb)));
}


// input: d - diagonal of symmetric tridiagonal matrix
//        e - offdiagonal of symmetric tridiagonal matrix
//        z - identity if you want eigensystem of symmetric tridiagonal matrix
//          - OR the householder reduction of a symmetric matrix
// output: d - eigenvalues
//         z - the corresponding eigen vectors in the COLUMNS
void eigen(double *d, double *e, int n, double **z)
{
    double pythag(double a, double b);
    int m, l, iter, i, k;
    double s, r, p, g, f, dd, c, b;

      // Convenient to renumber the elements of e.
    for (i=1; i<n; i++) e[i-1]=e[i];
    e[n-1]=0.0;

    for (l=0; l<n; l++) {
        iter=0;
        do {
            // Look for a single small subdiagonal element to split the matrix.
            for (m=l; m<n-1; m++) {
                dd=fabs(d[m])+fabs(d[m+1]);
                if ((double)(fabs(e[m])+dd) == dd) break;
            }

            if (m != l) {
                if (iter++ == 30) printf("Too many iterations in tqli");
                g=(d[l+1]-d[l])/(2.0*e[l]);       // Form shift.
                r=pythag(g, 1.0);
                g=d[m]-d[l]+e[l]/(g+SIGN(r, g));       // This is dm - ks.
                s=c=1.0;
                p=0.0;
                for (i=m-1; i>=l; i--) {      // A plane rotation as in the original QL, followed by Givens
                    f=s*e[i];                // rotations to restore tridiagonal form.
                    b=c*e[i];
                    e[i+1]=(r=pythag(f, g));
                    if (r == 0.0) {      // Recover from underflow.
                        d[i+1] -= p;
                        e[m]=0.0;
                        break;
                    }
                    s=f/r;
                    c=g/r;
                    g=d[i+1]-p;
                    r=(d[i]-g)*s+2.0*c*b;
                    d[i+1]=g+(p=s*r);
                    g=c*r-b;
                    // Next loop can be omitted if eigenvectors not wanted
                    // Form eigenvectors.
                    for (k=0; k<n; k++) {
                        f=z[k][i+1];
                        z[k][i+1]=s*z[k][i]+c*f;
                        z[k][i]=c*z[k][i]-s*f;
                    }
                }
                if (r == 0.0 && i >= l) continue;
                d[l] -= p;
                e[l]=g;
                e[m]=0.0;
            }
        } while (m != l);
    }
}




void Vec_to_Array(vector<vector<double> > vals, int N, int M, double** temp)
{

    for( int i = 0; i < N; i++) {
        for( int j = 0; j < M; j++) {
            temp[i][j] = vals[i][j];
        } 
    }

}


vector <vector<double> > Mutiply(vector <vector<double> > A, vector <vector<double> > B) {
  vector <vector<double> > Result;
	
	int A_Row, A_Column, B_Row, B_Column;
	A_Row    = A.size();
	A_Column = A[0].size();
	B_Row    = B.size();
	B_Column = B[0].size();
	vector<double> temp;


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


vector <vector<double> > Transpose(vector <vector<double> > M) {

	vector <vector<double> > New;

  	int height = M.size();
  	int width = M[0].size();

 
  	vector<double> Temp;

  	for (int j = 0; j < width; j++) {
    	for (int i = 0; i < height; i ++) {
      	Temp.push_back(M[i][j]);
    	}
    New.push_back(Temp);
    Temp.clear();
  	}


  	return New;
}



void print( vector <vector<double> > M)
{
	for (int i = 0; i < M.size(); i++) {
    	for (int j = 0; j < M[0].size(); j++) {
      	cout << setprecision(18) << setw(23) << M[i][j] << "  ";
    	}
    cout << endl;
	}
}

void print( vector<double> vec) {

	for (vector<double>::iterator it = vec.begin(); it < vec.end(); ++it) {
    	cout << *it << ' ';
  	}
  	cout << endl;
}

void Read_File(vector <vector<double> > &input) {

  	vector<double> line;
  	double get;
  	int R_L;
  	int C_L;
  	cin >> R_L;
  	cin >> C_L;
  	int num_a = 0;
  	int num_b = 0;
  
  	for (int i = 0; i < R_L; i++) {
  		for (int j = 0; j < C_L; j++) {
  			cin >> get;
  			line.push_back(get);	
  		}
  		input.push_back(line);
  		line.clear();

  	}

}