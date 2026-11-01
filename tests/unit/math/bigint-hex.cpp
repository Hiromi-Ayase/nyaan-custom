// Verify: math/bigint-to-hex.hpp
// Verify: math/bigint-binary.hpp
// 十六進1桁の筆算で大整数の積を求め、基数変換は十進での逐次16倍と比較する。シフト境界も試す。
#include <bits/stdc++.h>
using namespace std;
#include "math/bigint-to-hex.hpp"
#include "math/bigint-binary.hpp"

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

string hex128(__int128 value) {
  bool negative = value < 0;
  if (negative) {
    value = -value;
  }
  string result;
  do {
    result.push_back("0123456789ABCDEF"[value % 16]);
    value /= 16;
  } while (value);
  reverse(result.begin(), result.end());
  return signed_value(result, negative);
}

int main() {
  mt19937 rng(743);
  for (int length : {1, 7, 8, 9, 31, 32, 33, 511, 512, 513, 1500}) {
    string hex(length, '0');
    hex[0] = 'F';
    string decimal_value = "0";
    for (int i = 0; i < length; ++i) {
      int digit = i == 0 ? 15 : rng() % 16;
      hex[i] = "0123456789ABCDEF"[digit];
      decimal_value = add_unsigned(multiply_unsigned(decimal_value, "16"), std::to_string(digit));
    }
    bigint value(decimal_value);
    // 十進1桁の筆算で逐次16倍した期待値と、分割統治で変換した値を比較する。
    assert(HtoB(hex) == value);
    // 逆向きの変換でも、大きな数の全桁と大文字表記が保存される。
    assert(BtoH(value) == hex);
    string lower = hex;
    for (char& c : lower) {
      c = tolower(c);
    }
    // 小文字の入力と負号も同じ値として認識できる。
    assert(HtoB("-" + lower) == -value);

    BinaryBigInt binary(hex, 16);
    vector<int> digits(2 * length + 1);
    for (int i = 0; i < length; ++i) {
      for (int j = 0; j < length; ++j) {
        int a = string("0123456789ABCDEF").find(hex[length - 1 - i]);
        int b = string("0123456789ABCDEF").find(hex[length - 1 - j]);
        digits[i + j] += a * b;
      }
    }
    for (int i = 0; i + 1 < (int)digits.size(); ++i) {
      digits[i + 1] += digits[i] / 16;
      digits[i] %= 16;
    }
    while (digits.size() > 1 && digits.back() == 0) {
      digits.pop_back();
    }
    string squared;
    for (int i = digits.size() - 1; i >= 0; --i) {
      squared.push_back("0123456789ABCDEF"[digits[i]]);
    }
    // 二進多倍長のNTT乗算を、十六進1桁ずつの学校式の積と比較する。
    assert((binary * binary).to_hex() == squared);
    for (int shift : {0, 1, 31, 32, 33, 63, 64, 65, 129}) {
      auto shifted = binary;
      shifted <<= shift;
      shifted >>= shift;
      // 先頭の0ワードも正規化され、シフトを往復すると比較演算でも元の数に戻る。
      assert(shifted == binary);
      auto same = binary;
      same <<= 0;
      // 0bitシフトは文字列表現だけでなく、正規形も含めた恒等操作になる。
      assert(same == binary);
    }
  }
  for (int trial = 0; trial < 10000; ++trial) {
    long long a = int(rng());
    long long b = int(rng());
    BinaryBigInt x(hex128(a), 16);
    BinaryBigInt y(hex128(b), 16);
    // 正負の小さい値は、128bit整数による加減乗算・比較と一致する。
    assert((x + y).to_hex() == hex128((__int128)a + b));
    assert((x - y).to_hex() == hex128((__int128)a - b));
    assert((x * y).to_hex() == hex128((__int128)a * b));
    assert((x < y) == (a < b));
    // 二進GCDを標準gcdで照合し、返された大整数の正規化も確認する。
    assert(gcd(x, y) == BinaryBigInt(hex128(std::gcd(a, b)), 16));
    auto zero = x;
    zero >>= 100;
    // 全桁を失う右シフトでは、負数からでも正規形の0になる。
    assert(zero == BinaryBigInt("0", 16));
  }
}
