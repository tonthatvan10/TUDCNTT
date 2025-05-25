#include <iostream>
#include <cmath>
#include <limits>
#include <iomanip>
using namespace std;

// Hàm mục tiêu f(x)
double func(double x) {
    double v = 2*x*x + 1;
    if (fabs(v) < 1e-12) return numeric_limits<double>::infinity();
    double u = log10(v) + exp(8*x) + 14*x*x - 6*x;
    return u/v - 4*x*x;
}

// Đạo hàm f'(x)
double grad(double x) {
    double v = 2*x*x + 1;
    if (fabs(v) < 1e-12) return numeric_limits<double>::infinity();
    double dv = 4*x;
    double du = dv / (v * log(10.0))   // d/dx[log10(v)]
              + 8 * exp(8*x)          // d/dx[e^(8x)]
              + 28*x                  // d/dx[14x^2]
              - 6;                    // d/dx[-6x]
    double u = log10(v) + exp(8*x) + 14*x*x - 6*x;
    return (du * v - u * dv) / (v * v) - 8*x;
}

// Gradient Descent with Momentum
// x0: điểm khởi tạo, gamma: learning rate, alpha: momentum
// max_iter: N, tol: ε
pair<double,double> gradientDescentMomentum(
    double x0, double gamma, double alpha,
    int max_iter, double tol
) {
    double x = x0, v = 0.0;
    for (int k = 0; k < max_iter; ++k) {
        double g = grad(x);
        if (!isfinite(g)) break;
        v = alpha * v - gamma * g;
        double x_new = x + v;
        if (fabs(x_new - x) < tol) {
            x = x_new;
            break;
        }
        x = x_new;
    }
    return { x, func(x) };
}

int main() {
    double x_init = -2.0;    // thay theo yêu cầu
    double gamma  = 0.001;
    double alpha  = 0.01;
    int    N; 
    double eps;
    cout << "Nhap so buoc lap N (>=1000): ";  cin >> N;
    cout << "Nhap sai so dung epsilon: ";      cin >> eps;

    auto [x_min, f_min] = gradientDescentMomentum(
        x_init, gamma, alpha, N, eps
    );
    cout << fixed << setprecision(6);
    cout << "Ket qua sau khi chay:" << endl;
    cout << "  x_min = " << x_min << endl;
    cout << "  f(x_min) = " << f_min << endl;
    return 0;
}
