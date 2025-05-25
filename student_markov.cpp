#include <iostream>
#include <iomanip>
using namespace std;

const int N = 4;

double P[N][N] = {
    {0.0,  0.75, 0.2,  0.05},   // Rich
    {0.05, 0.2,  0.3,  0.45},   // Average
    {0.1,  0.4,  0.3,  0.2},    // Poor
    {0.0,  0.15, 0.3,  0.55}    // Indept
};

double temp1[N][N], temp2[N][N];

void matMul(double A[N][N], double B[N][N], double C[N][N]) {
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < N; ++k)
                C[i][j] += A[i][k] * B[k][j];
        }
}

int main() {
    cout << fixed << setprecision(6);
    // Bắt đầu từ trạng thái Average (chỉ số 1)
    int start = 1;
    // Sau 1 bước
    cout << "Xac suat tro thanh Rich sau 1 buoc: " << P[start][0] << endl;
    // Sau 2 bước
    matMul(P, P, temp1);
    cout << "Xac suat tro thanh Rich sau 2 buoc: " << temp1[start][0] << endl;
    // Sau 3 bước
    matMul(temp1, P, temp2);
    cout << "Xac suat tro thanh Rich sau 3 buoc: " << temp2[start][0] << endl;
    return 0;
}
