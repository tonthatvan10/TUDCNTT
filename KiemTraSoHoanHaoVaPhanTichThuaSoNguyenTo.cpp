#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

// Hàm phân tích thừa số nguyên tố, trả về vector chứa tất cả các thừa số (có thể lặp)
vector<int> primeFactors(int n) {
    vector<int> factors;
    int num = n;
    // Lấy hết các thừa số 2
    while (num % 2 == 0) {
        factors.push_back(2);
        num /= 2;
    }
    // Lấy các thừa số lẻ từ 3 trở đi
    for (int i = 3; i <= sqrt(num); i += 2) {
        while (num % i == 0) {
            factors.push_back(i);
            num /= i;
        }
    }
    // Nếu sau cùng num > 1 thì nó là một số nguyên tố
    if (num > 1) {
        factors.push_back(num);
    }
    return factors;
}

// Hàm kiểm tra số hoàn hảo
bool isPerfect(int n) {
    if (n <= 1) return false; // 1 không phải số hoàn hảo
    int sum = 1; // 1 luôn là ước tố riêng của n (n>1)
    // Tính tổng các ước tố (ngoại trừ chính nó)
    for (int i = 2; i <= sqrt(n); ++i) {
        if (n % i == 0) {
            sum += i;
            if (i != n / i) {
                sum += n / i;
            }
        }
    }
    return sum == n;
}

int main() {
    int a;
    cout << "Nhap so nguyen a: ";
    cin >> a;

    if (a <= 1) {
        cout << "Vui long nhap mot so nguyen > 1.\n";
        return 0;
    }

    // 1. Phân tích thừa số nguyên tố
    vector<int> factors = primeFactors(a);

    // 2. In ra các thừa số nguyên tố
    cout << "Cac thua so nguyen to cua " << a << " la: ";
    for (int p : factors) {
        cout << p << " ";
    }
    cout << "\n";

    // 3. In ra thừa số nhỏ nhất và lớn nhất
    int minP = *min_element(factors.begin(), factors.end());
    int maxP = *max_element(factors.begin(), factors.end());
    cout << "Thua so nguyen to nho nhat: " << minP << "\n";
    cout << "Thua so nguyen to lon nhat: "  << maxP << "\n";

    // 4. Kiểm tra số hoàn hảo
    if (isPerfect(a)) {
        cout << a << " la so hoan hao.\n";
    } else {
        cout << a << " khong phai la so hoan hao.\n";
    }

    return 0;
}
