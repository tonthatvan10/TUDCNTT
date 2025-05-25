#include <iostream>
#include <iomanip>
using namespace std;

const int N = 4;

double P[N][N] = {
    {0.23, 0.17, 0.33, 0.27},
    {0.21, 0.35, 0.23, 0.21},
    {0.18, 0.22, 0.28, 0.32},
    {0.19, 0.37, 0.09, 0.35}
};

double result[N][N];
double temp[N][N];

void matMul(double A[N][N], double B[N][N], double C[N][N]) {
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < N; ++k)
                C[i][j] += A[i][k] * B[k][j];
        }
}

void matCopy(double src[N][N], double dest[N][N]) {
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            dest[i][j] = src[i][j];
}

int main() {
    int initState = 1; // 0: trạng thái 1, 1: trạng thái 2, 2: trạng thái 3, 3: trạng thái 4
    matMul(P, P, result);
    cout << fixed << setprecision(6);
    cout << "Xac suat o cac trang thai sau 2 buoc (bat dau tu trang thai " << (initState+1) << "):\n";
    for (int j = 0; j < N; ++j) {
        cout << "Trang thai " << (j+1) << ": " << result[initState][j] << endl;
    }
    matMul(result, result, temp);
    cout << "\nXac suat o cac trang thai sau 4 buoc (bat dau tu trang thai " << (initState+1) << "):\n";
    for (int j = 0; j < N; ++j) {
        cout << "Trang thai " << (j+1) << ": " << temp[initState][j] << endl;
    }
    return 0;
}
