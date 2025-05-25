#include <iostream>
#include <vector>
using namespace std;

int extendedGCD(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int gcd = extendedGCD(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

int modInverse(int a, int m) {
    int x, y;
    int g = extendedGCD(a, m, x, y);
    if (g != 1) {
        throw "Nghich dao khong ton tai";
    } else {
        return (x % m + m) % m;
    }
}

void Input(vector<int> &a, vector<int> &m, const int &n) {
    a.resize(n);
    m.resize(n);
    for (int i = 0; i < n; i++) {
        cout << "Nhap a" << i + 1 << " = ";
        cin >> a[i];
        cout << "Nhap m" << i + 1 << " = ";
        cin >> m[i];
    }
}

int Ans(const vector<int> &a, const vector<int> &M, const vector<int> &y) {
    int ans = 0;
    for (int i = 0; i < a.size(); i++) {
        ans += a[i] * M[i] * y[i];
    }
    return ans;
}

int main() {
    int n;
    
    cout << "Nhap so phuong trinh: ";
    cin >> n;
    
    vector<int> a, m;
    Input(a, m, n);
    
    int M_total = 1;
    for(int i = 0; i < m.size(); i++) {
        M_total *= m[i];
    }
    
    vector<int> M(n);
    for(int i = 0; i < m.size(); i++) {
        M[i] = M_total / m[i];
    }
    
    vector<int> y(n);
    for (int i = 0; i < m.size(); i++) {
        y[i] = modInverse(M[i], m[i]);
    }
    
    int result = Ans(a, M, y) % M_total;
    cout << "Ket qua: " << result << endl;
    
    return 0;
}