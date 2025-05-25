#include <iostream>
#include "eigen/Eigen/Dense"
#include <iomanip>
#include <cmath>
using namespace std;
using namespace Eigen;

const double EPS = 1e-5;
int count = 0;

void swap(double& a, double& b);
void display(double A[][10], int row, int col);
void transpose(double A[][10], double At[][10], int rows, int cols);
void multiplyMatrices(MatrixXd& S, double A[][10], double B[][10], int row1, int col1, int col2);
void getEigenValuesAndVectors(MatrixXd S, MatrixXd& lambda, MatrixXd& vector);
void calculateMatrixS(MatrixXd lambda, double sigma[][10], int rows, int cols);
void calculateMatrixU(MatrixXd lambda, MatrixXd vector, double U[][10], double A[][10], int rows, int cols);
void calculateMatrixV(MatrixXd vector, double V[][10]);
void gramSchmidt(double U[][10], int rows, int cols);
void rref(MatrixXd& U_matrix);
int main()
{
   int rows, cols;
   double A[10][10], At[10][10];

   cout << "Enter Matrix Dimensions:" << endl;
   cout << "Rows: ";
   cin >> rows;
   cout << "Columns: ";
   cin >> cols;

   cout << "Enter Matrix Elements:" << endl;
   for (int i = 0; i < rows; i++)
   {
       for (int j = 0; j < cols; j++)
       {
           cout << "A[" << i + 1 << "][" << j + 1 << "] = ";
           cin >> A[i][j];
       }
   }

   MatrixXd S(cols, cols), lambda(cols, 1), vector(cols, cols);

   transpose(A, At, rows, cols);

   multiplyMatrices(S, At, A, cols, rows, cols);
   MatrixXd S_copy = S;
   rref(S_copy);
   getEigenValuesAndVectors(S, lambda, vector);

   double sigma[10][10], U[10][10], V[10][10];

   calculateMatrixU(lambda, vector, U, A, rows, cols);
   cout << "Completed Gram-Schmidt Process..." << endl;
   MatrixXd null_space(cols, 1);
   for (int i = 0; i < cols; i++)
   {
       null_space(i, 0) = S_copy(i, cols - 1);
   }
   cout << "Matrix U:" << endl;
   display(U, rows, rows);

   calculateMatrixS(lambda, sigma, rows, cols);
   cout << "Matrix Sigma:" << endl;
   display(sigma, rows, cols);

   calculateMatrixV(vector, V);
   cout << "Matrix V^T:" << endl;
   double VT[10][10];
   transpose(V, VT, cols, cols);
   display(VT, cols, cols);

   MatrixXd U_matrix(rows, rows), V_matrix(cols, cols), S_matrix(rows, cols);
   for (int i = 0; i < rows; i++)
       for (int j = 0; j < rows; j++)
           U_matrix(i, j) = U[i][j];

   for (int i = 0; i < cols; i++)
       for (int j = 0; j < cols; j++)
           V_matrix(i, j) = V[i][j];

   for (int i = 0; i < rows; i++)
       for (int j = 0; j < cols; j++)
           S_matrix(i, j) = sigma[i][j];

   MatrixXd A_matrix = U_matrix * S_matrix * V_matrix;

   cout << "Reconstructed Matrix A:" << endl;
   display(A, rows, cols);

   return 0;
}

void rref(MatrixXd& U_matrix)
{
   int rows = U_matrix.rows();
   int cols = U_matrix.cols();
   int lead = 0;

   for (int r = 0; r < rows; ++r)
   {
       if (lead >= cols)
           return;
       int i = r;
       while (U_matrix(i, lead) == 0)
       {
           ++i;
           if (i == rows)
           {
               i = r;
               ++lead;
               if (lead == cols)
                   return;
           }
       }

       U_matrix.row(i).swap(U_matrix.row(r));
       U_matrix.row(r) /= U_matrix(r, lead);
       for (int i = 0; i < rows; ++i)
       {
           if (i != r)
           {
               U_matrix.row(i) -= U_matrix.row(r) * U_matrix(i, lead);
           }
       }
       ++lead;
   }
}

void swap(double& a, double& b) 
{
   double temp = a;
   a = b;
   b = temp;
}

void display(double A[][10], int row, int col)  
{
   for (int i = 0; i < row; i++)
   {
       for (int j = 0; j < col; j++)
           cout << setw(12) << setprecision(4) << A[i][j];
       cout << endl;
   }
}

void transpose(double A[][10], double At[][10], int rows, int cols)
{
   for (int i = 0; i < rows; i++)
       for (int j = 0; j < cols; j++)
           At[j][i] = A[i][j];
}

void multiplyMatrices(MatrixXd& S, double A[][10], double B[][10], int row1, int col1, int col2)
{
   for (int i = 0; i < row1; i++)
   {
       for (int j = 0; j < col2; j++)
       {
           S(i, j) = 0;
           for (int k = 0; k < col1; k++)
           {
               S(i, j) += A[i][k] * B[k][j];
           }
       }
   }
}

void getEigenValuesAndVectors(MatrixXd S, MatrixXd& lambda, MatrixXd& vector)
{
   SelfAdjointEigenSolver<Eigen::MatrixXd> eigensolver(S);
   vector = eigensolver.eigenvectors();
   lambda = eigensolver.eigenvalues();

   int k = lambda.rows();
   int l = vector.rows();

   for (int i = 0; i < k; i++)
   {
       if (lambda(i, 0) < EPS )
       {
           lambda(i, 0) = 0;
           ::count++;
       }
   }

   for (int i = 0; i < k; i++)
   {
       for (int j = i + 1; j < k; j++)
       {
           if (lambda(j, 0) > lambda(i, 0))
           {
               swap(lambda(j, 0), lambda(i, 0));
               for (int h = 0; h < l; h++)
                   swap(vector(h, i), vector(h, j));
           }
       }
   }
}

void calculateMatrixU(MatrixXd lambda, MatrixXd vector, double U[][10], double A[][10], int rows, int cols)
{
   MatrixXd ui(rows, 1);
   double Vi[10][10];

   for (int i = 0; i < cols; i++)
   {
       for (int j = 0; j < cols; j++)
       {
           Vi[j][0] = vector(j, i);
       }
       multiplyMatrices(ui, A, Vi, rows, cols, 1);

       for (int k = 0; k < rows; k++)
       {
           if (lambda(i, 0) != 0)
           {
               U[k][i] = (1 / sqrt(lambda(i, 0))) * ui(k, 0);
           }
           else
           {
               U[k][i] = 0;
           }
       }
   }
}

void gramSchmidt(double U[][10], int rows, int cols)
{
   for (int i = cols; i < rows; i++)
   {
       for (int j = 0; j < rows; j++)
       {
           U[j][i] = (i == j) ? 1 : 0;
       }

       for (int k = 0; k < i; k++)
       {
           double dot_product = 0;
           for (int j = 0; j < rows; j++)
           {
               dot_product += U[j][i] * U[j][k];
           }
           for (int j = 0; j < rows; j++)
           {
               U[j][i] -= dot_product * U[j][k];
           }
       }

       double norm = 0;
       for (int j = 0; j < rows; j++)
       {
           norm += U[j][i] * U[j][i];
       }
       norm = sqrt(norm);
       for (int j = 0; j < rows; j++)
       {
           U[j][i] /= norm;
       }
   }
}

void calculateMatrixV(MatrixXd vector, double V[][10])
{
   int row = vector.rows(), col = vector.cols();
   for (int i = 0; i < row; i++)
   {
       for (int j = 0; j < col; j++)
       {
           V[i][j] = vector(i, j);
       }
   }
}

void calculateMatrixS(MatrixXd lambda, double sigma[][10], int rows, int cols)
{
   int k = 0;
   for (int i = 0; i < rows; i++)
   {
       for (int j = 0; j < cols; j++)
       {
           if (i == j && lambda(k, 0) != 0)
           {
               sigma[i][j] = sqrt(lambda(k, 0));
               k++;
           }
           else
           {
               sigma[i][j] = 0;
           }
       }
   }
}
