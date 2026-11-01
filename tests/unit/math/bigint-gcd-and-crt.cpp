// Verify: math/bigint-gcd.hpp
// Verify: math/bigint-garner.hpp
// 既知の共通因子を持つ大整数のGCDを照合し、CRTは十進筆算で作った法の積と既知の解を使う。
#include <bits/stdc++.h>
using namespace std;
#include "math/bigint-gcd.hpp"
#include "math/bigint-garner.hpp"

string trim(string s) {
  size_t first = s.find_first_not_of('0');
  return first == string::npos ? "0" : s.substr(first);
}

bool less_unsigned(const string& a, const string& b) {
  return a.size() != b.size() ? a.size() < b.size() : a < b;
}

string add_unsigned(string a, string b) {
  reverse(a.begin(), a.end());
  reverse(b.begin(), b.end());
  string c;
  int carry = 0;
  for (int i = 0; i < (int)max(a.size(), b.size()) || carry; ++i) {
    if (i < (int)a.size()) {
      carry += a[i] - '0';
    }
    if (i < (int)b.size()) {
      carry += b[i] - '0';
    }
    c.push_back('0' + carry % 10);
    carry /= 10;
  }
  reverse(c.begin(), c.end());
  return trim(c);
}

string subtract_unsigned(string a, string b) {
  reverse(a.begin(), a.end());
  reverse(b.begin(), b.end());
  int borrow = 0;
  for (int i = 0; i < (int)a.size(); ++i) {
    int digit = a[i] - '0' - borrow - (i < (int)b.size() ? b[i] - '0' : 0);
    borrow = digit < 0;
    a[i] = '0' + digit + (borrow ? 10 : 0);
  }
  reverse(a.begin(), a.end());
  return trim(a);
}

string multiply_unsigned(const string& a, const string& b) {
  vector<int> digits(a.size() + b.size() + 1);
  for (int i = 0; i < (int)a.size(); ++i) {
    for (int j = 0; j < (int)b.size(); ++j) {
      digits[i + j] += (a[a.size() - 1 - i] - '0') * (b[b.size() - 1 - j] - '0');
    }
  }
  for (int i = 0; i + 1 < (int)digits.size(); ++i) {
    digits[i + 1] += digits[i] / 10;
    digits[i] %= 10;
  }
  string result;
  for (int i = digits.size() - 1; i >= 0; --i) {
    result.push_back('0' + digits[i]);
  }
  return trim(result);
}

pair<string, string> divide_unsigned(const string& a, const string& b) {
  string quotient;
  string remainder = "0";
  for (char digit : a) {
    remainder = trim(remainder + digit);
    int q = 0;
    while (!less_unsigned(remainder, b)) {
      remainder = subtract_unsigned(remainder, b);
      ++q;
    }
    quotient.push_back('0' + q);
  }
  return {trim(quotient), remainder};
}

string signed_value(const string& magnitude, bool negative) {
  return negative && magnitude != "0" ? "-" + magnitude : magnitude;
}

int main() {
  mt19937 rng(742);
  for (int length : {1, 9, 10, 36, 37, 100, 1000}) {
    string common(length, '0');
    common[0] = '7';
    for (int i = 1; i < length; ++i) {
      common[i] = '0' + rng() % 10;
    }
    for (int u : {1, 2, 5, 17, 1000000000}) {
      int v = u + 1;
      bigint a(multiply_unsigned(common, std::to_string(u)));
      bigint b(multiply_unsigned(common, std::to_string(v)));
      // 隣接整数u,vは互いに素なので、common*uとcommon*vのGCDは正確にcommonになる。
      assert(gcd(a, b).to_string() == common);
      assert(gcd(-a, b).to_string() == common);
      // 正の入力のLCMはcommon*u*vで、独立した十進筆算の値と一致する。
      assert(lcm(a, b).to_string() ==
             multiply_unsigned(multiply_unsigned(common, std::to_string(u)), std::to_string(v)));
    }
  }
  // 片方または両方が0のGCDは、通常の非負GCDの定義に従う。
  assert(gcd(bigint(0), bigint(0)) == bigint(0));
  assert(gcd(bigint(0), bigint(-42)) == bigint(42));

  vector<int> primes;
  for (int p = 2; primes.size() <= 3001; ++p) {
    bool prime = true;
    for (int d = 2; d * d <= p; ++d) {
      if (p % d == 0) {
        prime = false;
        break;
      }
    }
    if (prime) {
      primes.push_back(p);
    }
  }
  for (int n : {0, 1, 2, 20, 3000, 3001}) {
    vector<int> mod(primes.begin(), primes.begin() + n);
    string product = "1";
    for (int p : mod) {
      product = multiply_unsigned(product, std::to_string(p));
    }
    string expected = divide_unsigned(product, "2").first;
    vector<int> residues(n);
    for (int i = 0; i < n; ++i) {
      for (char digit : expected) {
        residues[i] = (10LL * residues[i] + digit - '0') % mod[i];
      }
    }
    auto [answer, period] = garner_bigint(residues, mod);
    // 法の積の半分を既知の解にする。3000/3001件で素朴版と分割統治の切替を確認する。
    assert(answer.to_string() == expected && period.to_string() == product);
    if (n <= 20) {
      // 別名のcrt_bigintも同じ合同式の解と周期を返す。
      assert(crt_bigint(residues, mod) == make_pair(answer, period));
    }
  }
}
