#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Hàm tính Extended GCD
tuple<ll, ll, ll> ext_gcd(ll a, ll b) {
    if (b == 0) return {a, 1, 0};
    auto [g, x1, y1] = ext_gcd(b, a % b);
    ll x = y1;
    ll y = x1 - (a / b) * y1;
    return {g, x, y};
}

// Hàm giải hệ đồng dư: x ≡ a[i] (mod m[i])
ll chinese_remainder(const vector<ll> &m, const vector<ll> &a) {
    ll x = 0, mod = 1;
    int k = m.size();
    for (int i = 0; i < k; i++) {
        ll mi = m[i];
        ll ai = ((a[i] % mi) + mi) % mi;
        auto [g, x1, y1] = ext_gcd(mod, mi);
        if ((ai - x) % g != 0) return -1;
        ll t = ((ai - x) / g % (mi/g) * x1 % (mi/g) + (mi/g)) % (mi/g);
        x = x + mod * t;
        mod = mod / g * mi;
        x = (x % mod + mod) % mod;
    }
    return x;
}

int main() {
    cout << "Nhap so cap (a_i, m_i): ";
    int k;
    cin >> k;
    if (k <= 0) return 0;
    cout << "Nhap cac cap (a_i, m_i):\n";

    vector<ll> a(k), m(k);
    // Nhập từng cặp a và m trên mỗi dòng
    for (int i = 0; i < k; i++) {
        cin >> a[i] >> m[i];
    }

    // In lại các cặp đã nhập
    cout << "Cac cap (a_i, m_i):\n";
    for (int i = 0; i < k; i++) {
        cout << "(" << a[i] << ", " << m[i] << ")\n";
    }

    ll res = chinese_remainder(m, a);
    cout << "Ket qua: ";
    if (res == -1) cout << "-1";
    else cout << res;
    cout << "\n";

    return 0;
}
