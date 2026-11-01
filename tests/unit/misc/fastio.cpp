// Verify: misc/fastio.hpp
// Verify: misc/all.hpp
// 標準ライブラリの一時FILEを入力/出力にし、境界整数とバッファサイズを超える文字列・数列を照合する。
#include <bits/stdc++.h>
using namespace std;
#include "misc/all.hpp"

string decimal(__uint128_t value) {
  string result;
  do {
    result += char('0' + value % 10);
    value /= 10;
  } while (value);
  reverse(result.begin(), result.end());
  return result;
}

int main() {
  FILE* input = tmpfile();
  FILE* output = tmpfile();
  // 一時ファイルの作成に成功したことを確認してから標準入出力を差し替える。
  assert(input && output);
  vector<long long> signed_values{LLONG_MIN, LLONG_MAX, -1, 0, 1, 9999, 10000, 10001, -10001};
  vector<unsigned long long> unsigned_values{0, 1, ULLONG_MAX, 1ULL << 63};
  string input_text = " \n\tZ ";
  string expected = "Z\n";
  for (auto x : signed_values) {
    input_text += to_string(x) + " \n";
    expected += to_string(x) + "\n";
  }
  for (auto x : unsigned_values) {
    input_text += to_string(x) + " \n";
    expected += to_string(x) + "\n";
  }
  __uint128_t huge = (__uint128_t(1) << 127) + 12345;
  input_text += decimal(huge) + " ";
  expected += decimal(huge) + "\n";
  // 文字列を入力バッファより長くし、複数回のload/flushが必要になるようにする。
  string long_word(fastio::SZ * 2 + 13, 'x');
  input_text += long_word + " \n";
  expected += long_word + "\n";
  for (int i = 0; i < 40000; ++i) {
    input_text += to_string(i) + " ";
    expected += to_string(i) + " ";
  }
  input_text += '\n';
  fwrite(input_text.data(), 1, input_text.size(), input);
  rewind(input);
  FILE* saved_in = stdin;
  FILE* saved_out = stdout;
  stdin = input;
  stdout = output;
  char letter = 0;
  rd(letter);
  assert(letter == 'Z');
  wtn(letter);
  for (auto expected_value : signed_values) {
    long long x = 0;
    rd(x);
    // 符号付き最小値を含む全境界値が、10進入力から型の値へ正しく復元される。
    assert(x == expected_value);
    wtn(x);
  }
  for (auto expected_value : unsigned_values) {
    unsigned long long x = 0;
    rd(x);
    assert(x == expected_value);
    wtn(x);
  }
  __uint128_t parsed = 0;
  rd(parsed);
  assert(parsed == huge);
  wtn(parsed);
  string word;
  rd(word);
  assert(word == long_word);
  wtn(word);
  for (int i = 0; i < 40000; ++i) {
    int x = -1;
    rd(x);
    assert(x == i);
    wt(x, ' ');
  }
  fastio::flush();
  fflush(stdout);
  stdin = saved_in;
  stdout = saved_out;
  rewind(output);
  string actual;
  array<char, 4096> buffer;
  while (size_t length = fread(buffer.data(), 1, buffer.size(), output)) {
    actual.append(buffer.data(), length);
  }
  // 出力側も全バイト比較し、数値境界・改行・文字列の途中で失われるデータがないか調べる。
  assert(actual == expected);
  fclose(input);
  fclose(output);
  Timer timer;
  // all.hppの集約インポートから、タイマーと乱数の公開APIも使用できる。
  assert(timer.elapsed() >= 0 && randint(5, 6) == 5);
  for (int length : {1, 3, fastio::SZ - 1, fastio::SZ, fastio::SZ + 1, 2 * fastio::SZ + 13}) {
    FILE* eof_input = tmpfile();
    // 改行のない最終単語を入れるための入力ファイルを用意する。
    assert(eof_input);
    string last_word(length, 'a');
    for (int i = 0; i < length; ++i) {
      last_word[i] += i % 26;
    }
    string text = " \t" + last_word;
    fwrite(text.data(), 1, text.size(), eof_input);
    rewind(eof_input);
    stdin = eof_input;
    fastio::in_left = 0;
    fastio::in_right = 0;
    string parsed_word = "prefix:";
    rd(parsed_word);
    // EOFで終わる単語も、バッファ境界をまたぐ長さも、既存文字列へ一度だけ追記する。
    assert(parsed_word == "prefix:" + last_word);
    stdin = saved_in;
    fclose(eof_input);
  }
}
