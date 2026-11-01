// Verify: math/bigint.hpp
// 十進1桁ずつの筆算で加減乗除を独立に計算し、9桁ブロック・FFT・Newton除算の切替をまたいで比較する。
#include <bits/stdc++.h>
using namespace std;
#include "math/bigint.hpp"

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

string decimal128(__int128 value) {
  bool negative = value < 0;
  if (negative) {
    value = -value;
  }
  string s;
  do {
    s.push_back('0' + value % 10);
    value /= 10;
  } while (value);
  reverse(s.begin(), s.end());
  return signed_value(s, negative);
}

int main() {
  vector<long long> values{0, 1, -1, 999999999, 1000000000, 1000000001, LLONG_MIN, LLONG_MAX};
  mt19937_64 rng(741);
  for (int i = 0; i < 100; ++i) {
    values.push_back((long long)(rng() % 2000000000001ULL) - 1000000000000LL);
  }
  for (long long a : values) {
    bigint x(a);
    // 固定幅の最小値も含め、整数コンストラクタの符号と十進文字列が一致する。
    assert(x.to_string() == std::to_string(a));
    for (long long b : values) {
      bigint y(b);
      // 小さい値の四則演算は、桁あふれしない128bit整数の計算と一致する。
      assert((x + y).to_string() == decimal128((__int128)a + b));
      assert((x - y).to_string() == decimal128((__int128)a - b));
      assert((x * y).to_string() == decimal128((__int128)a * b));
      assert((x < y) == (a < b));
      if (b != 0) {
        auto [q, r] = divmod(x, y);
        // 商は0方向への丸め、余りの符号は被除数と同じになる。
        assert(q.to_string() == decimal128((__int128)a / b));
        assert(r.to_string() == decimal128((__int128)a % b));
      }
    }
  }
  for (auto [n, m] : vector<pair<int, int>>{{1, 1},
                                            {9, 9},
                                            {10, 9},
                                            {18, 19},
                                            {575, 33},
                                            {576, 577},
                                            {577, 575},
                                            {1152, 1153},
                                            {1153, 1153},
                                            {2307, 1153},
                                            {5000, 1800}}) {
    string a(n, '9');
    string b(m, '9');
    for (int i = 1; i < n; ++i) {
      a[i] = '0' + rng() % 10;
    }
    for (int i = 1; i < m; ++i) {
      b[i] = '0' + rng() % 10;
    }
    bigint x(a);
    bigint y(b);
    string sum = add_unsigned(a, b);
    bool negative = less_unsigned(a, b);
    string difference = negative ? subtract_unsigned(b, a) : subtract_unsigned(a, b);
    string product = multiply_unsigned(a, b);
    auto [quotient, remainder] = divide_unsigned(a, b);
    // 内部の10^9進表現やNTTに依存せず、十進1桁ずつの筆算と比較する。
    assert((x + y).to_string() == sum);
    assert((x - y).to_string() == signed_value(difference, negative));
    assert((x * y).to_string() == product);
    for (bool sign_a : {false, true}) {
      for (bool sign_b : {false, true}) {
        auto [q, r] = divmod(sign_a ? -x : x, sign_b ? -y : y);
        // Newton除算を使う大きさでも、正負4通りの商・余りを同じ筆算の答えと照合する。
        assert(q.to_string() == signed_value(quotient, sign_a != sign_b));
        assert(r.to_string() == signed_value(remainder, sign_a));
      }
    }
  }
}
