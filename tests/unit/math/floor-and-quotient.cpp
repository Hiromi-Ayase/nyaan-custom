// Verify: math/floor-sum.hpp
// Verify: math/enumerate-quotient.hpp
// 床関数の和と剰余範囲の個数を逐次走査し、商の列挙は区間の被覆・端点・単調順を確認する。
#include <bits/stdc++.h>
using namespace std;
#define NyaanLocal
#include "math/floor-sum.hpp"
#include "math/enumerate-quotient.hpp"

int main() {
  mt19937 rng(702);
  for (int trial = 0; trial < 20000; ++trial) {
    long long n = rng() % 101;
    long long m = 1 + rng() % 101;
    long long a = rng() % 501;
    long long b = rng() % 501;
    long long yr = rng() % (m + 1);
    long long sum = 0;
    long long count = 0;
    for (int i = 0; i < n; ++i) {
      sum += (a * i + b) / m;
      count += (a * i + b) % m < yr;
    }
    // n=0、a=0、aやbが法以上の場合も、各項を直接割った総和と一致する。
    assert(sum_of_floor(n, m, a, b) == sum);
    // 剰余を直接調べた個数と比較し、上端yr=0/mも確認する。
    assert(mod_affine_range_counting(a, b, m, n, yr) == count);
  }
  vector<long long> cases;
  for (int n = 0; n <= 1000; ++n) {
    cases.push_back(n);
  }
  cases.push_back(1000000000000LL);
  cases.push_back(1000000000001LL);
  for (long long n : cases) {
    long long last = 0;
    long long boundary = n;
    enumerate_quotient(n, [&](long long quotient, long long left, long long right) {
      // 区間は左開右閉で連続し、商は厳密昇順になる。
      assert(0 <= left && left < right && right == boundary && quotient > last);
      // 両端で同じ商になるため、単調性により区間内の全整数で商が一定になる。
      assert(n / (left + 1) == quotient && n / right == quotient);
      if (left > 0) {
        // 直前の整数では商が変わり、同じ商の区間が最大まで伸びている。
        assert(n / left != quotient);
      }
      boundary = left;
      last = quotient;
    });
    // 全区間を合わせると1からnまでを過不足なく覆う。n=0ではコールバックを呼ばない。
    assert(boundary == 0);
  }
}
