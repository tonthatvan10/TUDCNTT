#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
using namespace std;

// Hàm sàng Eratosthenes: đánh dấu is_prime[i] = true nếu i là nguyên tố
vector<bool> sieve(int n) {
    vector<bool> is_prime(n + 1, true);
    if (n >= 0) is_prime[0] = false;
    if (n >= 1) is_prime[1] = false;
    int limit = static_cast<int>(sqrt(n));
    for (int p = 2; p <= limit; ++p) {
        if (is_prime[p]) {
            for (int multiple = p * p; multiple <= n; multiple += p) {
                is_prime[multiple] = false;
            }
        }
    }
    return is_prime;
}

int main() {
    long long m, n, x;
    cout << "Nhap gia tri m, n (m <= n) va x: ";
    cin >> m >> n >> x;
    if (m > n || m < 0) {
        cerr << "Nhap khong hop le: can thoa man 0 <= m <= n\n";
        return 1;
    }

    // 1) Sàng các số ≤ n
    vector<bool> is_prime = sieve((int)n);

    // 2) Lọc và in các số nguyên tố trong [m,n]
    vector<long long> primes;
    long long sum = 0;
    cout << "Cac so nguyen to trong khoang [" << m << ", " << n << "]:\n";
    for (long long i = max(2LL, m); i <= n; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
            sum += i;
            cout << i << " ";
        }
    }
    cout << "\n";

    // 3) In tổng
    cout << "Tong cac so nguyen to tren: " << sum << "\n";

    // 4) Tìm số nguyên tố gần x nhất
    if (primes.empty()) {
        cout << "Khong co so nguyen to nao trong khoang de tim gan x.\n";
    } else {
        long long best = primes[0];
        long long bestDist = llabs(primes[0] - x);
        for (long long p : primes) {
            long long d = llabs(p - x);
            if (d < bestDist) {
                bestDist = d;
                best = p;
            }
        }
        cout << "So nguyen to trong [" << m << "," << n
             << "] gan nhat voi x = " << x << " la: " << best << "\n";
    }

    return 0;
}
