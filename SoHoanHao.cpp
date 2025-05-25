#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
using namespace std;

// Hàm kiểm tra số hoàn hảo
bool isPerfect(int n) {
    if (n <= 1) return false;
    int sum = 1;
    int limit = sqrt(n);
    for (int i = 2; i <= limit; ++i) {
        if (n % i == 0) {
            sum += i;
            int j = n / i;
            if (j != i) sum += j;
        }
    }
    return sum == n;
}

// Hàm tìm và in số hoàn hảo trong khoảng [u, v],
// trả về vector các số hoàn hảo tìm được
vector<int> collectPerfects(int u, int v) {
    vector<int> perfects;
    for (int i = max(u, 2); i <= v; ++i) {
        if (isPerfect(i)) {
            perfects.push_back(i);
        }
    }
    return perfects;
}

// Hàm in ra các số hoàn hảo, tính tổng, và in số hoàn hảo gần x nhất
void perfectInRange(int u, int v, int x) {
    vector<int> pfs = collectPerfects(u, v);

    if (pfs.empty()) {
        cout << "Khong co so hoan hao trong khoang [" << u << ", " << v << "].\n";
        return;
    }

    // 1. In danh sách số hoàn hảo
    cout << "Cac so hoan hao trong [" << u << ", " << v << "]: ";
    for (int p : pfs) cout << p << " ";
    cout << "\n";

    // 2. Tính và in tổng
    long long sum = 0;
    for (int p : pfs) sum += p;
    cout << "Tong cac so hoan hao: " << sum << "\n";

    // 3. Tìm số hoàn hảo gần x nhất
    int closest = pfs[0];
    int bestDist = abs(x - closest);
    for (int p : pfs) {
        int d = abs(x - p);
        if (d < bestDist) {
            bestDist = d;
            closest = p;
        }
    }
    cout << "So hoan hao gan voi " << x << " nhat la: " << closest << "\n";
}

int main() {
    int u, v, x;
    cout << "Nhap gioi han u, v: ";
    cin >> u >> v;
    cout << "Nhap gia tri x de tim so hoan hao gan nhat: ";
    cin >> x;

    perfectInRange(u, v, x);

    return 0;
}
