// Verify: template/template.hpp
// Verify: template/util.hpp
// Verify: template/bitop.hpp
// Verify: template/macro.hpp
// Verify: template/inout.hpp
// Verify: template/debug.hpp
// テンプレートのsolveエントリから各公開補助を実行し、ビット演算・配列操作・入出力・デバッグ表示を確認する。
#include <bits/stdc++.h>
using namespace std;
#include "template/template.hpp"

void Nyaan::solve() {
  mt19937_64 rng(1501);
  for (int trial = 0; trial < 10000; ++trial) {
    u64 value = rng();
    if (trial < 65) {
      value = trial == 64 ? 0 : 1ULL << trial;
    }
    int count = 0;
    int first = 64;
    int last = -1;
    for (int bit = 0; bit < 64; ++bit) {
      bool set = (value / (u64(1) << bit)) % 2;
      if (set) {
        ++count;
        first = min(first, bit);
        last = bit;
      }
      // 1ビットずつの整数除算とgbit/sbitの読書きを比較する。
      assert(gbit(value, bit) == set);
      auto changed = value;
      sbit(changed, bit, !set);
      assert(changed == (value ^ (1ULL << bit)));
    }
    assert(popcnt(value) == count && lsb(value) == first && ctz(value) == first &&
           msb(value) == last);
  }
  for (int k = 0; k < 63; ++k) {
    assert(PW(k) == (1LL << k) && MSK(k) == PW(k) - 1);
  }
  vector<int> a{3, -2, 3, 7};
  // 累積和は各区間を直接足した値と一致し、逆方向の累積和も確認する。
  auto prefix = mkrui(a);
  auto suffix = mkrui(a, true);
  for (int i = 0; i <= sz(a); ++i) {
    assert(prefix[i] == accumulate(a.begin(), a.begin() + i, 0));
    assert(suffix[i] == accumulate(a.begin() + i, a.end(), 0));
  }
  assert(Max(a) == 7 && Min(a) == -2 && Sum(a) == 11);
  assert(mkuni(a) == vector<int>({-2, 3, 7}));
  assert(mkrev(a) == vector<int>({7, 3, -2, 3}) && Rev(a) == mkrev(a));
  int low = 5;
  int high = 5;
  assert(amin(low, 3) && low == 3 && !amin(low, 7));
  assert(amax(high, 7) && high == 7 && !amax(high, 3));
  vector<int> sorted{-2, 3, 3, 7};
  for (int x = -3; x <= 8; ++x) {
    assert(lb(sorted, x) == count_if(sorted.begin(), sorted.end(), [&](int y) { return y < x; }));
    assert(ub(sorted, x) == count_if(sorted.begin(), sorted.end(), [&](int y) { return y <= x; }));
  }
  vector<int> permutation{2, 0, 3, 1};
  auto inverse = mkinv(permutation);
  for (int i = 0; i < 4; ++i) {
    assert(inverse[permutation[i]] == i);
  }
  assert(mkiota(4) == vector<int>({0, 1, 2, 3}));
  assert(mkord(4, [](int i, int j) { return i > j; }) == vector<int>({3, 2, 1, 0}));
  vector<int> p{0, 1, 2};
  int permutations = 1;
  while (nxp(p)) {
    ++permutations;
  }
  assert(permutations == 6);
  auto tuples = product(vector<int>{2, 3, 2});
  vector<vector<int>> expected;
  for (int x = 0; x < 2; ++x) {
    for (int y = 0; y < 3; ++y) {
      for (int z = 0; z < 2; ++z) {
        expected.push_back({x, y, z});
      }
    }
  }
  assert(tuples == expected && product(vector<int>{2, 0}).empty());
  long long ten = 1;
  for (int i = 0; i <= 9; ++i) {
    assert(TEN(i) == ten);
    ten *= 10;
  }
  for (int n = 0; n <= 20; ++n) {
    long long expected_power = 1;
    for (int i = 0; i < n; ++i) {
      expected_power = expected_power * 7 % 101;
    }
    assert(Power(7LL, n, 1LL, function<void(long long&)>{[](long long& x) { x %= 101; }}) ==
           expected_power);
  }
  assert(Power(3LL, 5) == 243);
  P<int, int> pair_a(2, 3);
  P<int, int> pair_b(5, 7);
  auto sum = pair_a + pair_b;
  auto product_pair = pair_a * pair_b;
  assert(sum.first == 7 && sum.second == 10 && product_pair.first == 10 &&
         product_pair.second == 21);
  auto scale = pair_a * 4;
  assert(scale.first == 8 && scale.second == 12);
  vector<vector<int>> matrix{{1, 2, 3}, {4, 5, 6}};
  // 非正方形行列の転置と、APIで定める回転方向を具体例で固定する。
  assert(Transpose(matrix) == vector<vector<int>>({{1, 4}, {2, 5}, {3, 6}}));
  assert(Rotate(matrix) == vector<vector<int>>({{3, 6}, {2, 5}, {1, 4}}));
  assert(Rotate(matrix, false) == vector<vector<int>>({{4, 1}, {5, 2}, {6, 3}}));
  vector<long long> indices;
  rep(i, 4) {
    indices.push_back(i);
  }
  repr(i, 3) {
    indices.push_back(i);
  }
  rep1(i, 2) {
    indices.push_back(i);
  }
  repr1(i, 2) {
    indices.push_back(i);
  }
  reg(i, 2, 4) {
    indices.push_back(i);
  }
  regr(i, 2, 4) {
    indices.push_back(i);
  }
  // 反復マクロの端点・逆順を明示した列と比較する。
  assert(indices == vector<long long>({0, 1, 2, 3, 2, 1, 0, 1, 2, 2, 1, 2, 3, 3, 2}));
  int total = 0;
  each(x, a) {
    total += x;
  }
  assert(total == 11);
  vector<pair<int, int>> pairs{{1, 2}, {3, 4}};
  total = 0;
  each2(x, y, pairs) {
    total += x + y;
  }
  assert(total == 10);
  sort(all(a));
  assert(a == sorted);
  istringstream input("12 -34 5 6 7 1000000000000000000000000000000");
  pair<int, int> pair_value;
  vector<int> list(3);
  __int128_t big = 0;
  input >> pair_value >> list >> big;
  ostringstream output;
  output << pair_value << '|' << list << '|' << big;
  // pair/vector/128ビット整数の演算子が、空白区切りの定められた形式で往復する。
  assert(output.str() == "12 -34|5 6 7|1000000000000000000000000000000");
  istringstream in_stream("8 9");
  ostringstream out_stream;
  auto* old_in = cin.rdbuf(in_stream.rdbuf());
  auto* old_out = cout.rdbuf(out_stream.rdbuf());
  int x = 0;
  int y = 0;
  in(x, y);
  out(x, y);
  cin.rdbuf(old_in);
  cout.rdbuf(old_out);
  assert(x == 8 && y == 9 && out_stream.str() == "8 9\n");
  ostringstream debug;
  auto* old_error = cerr.rdbuf(debug.rdbuf());
  DebugImpl::dump(vector<int>{1, 2});
  cerr << '|';
  DebugImpl::dump(make_pair(true, string("x")));
  cerr.rdbuf(old_error);
  // デバッグ表示もコンテナ・真偽値・pairの内容を保持する。
  assert(debug.str() == "[ 1, 2 ]|( true, x )");
  int effects = 0;
  trc(++effects);
  trc2(++effects);
  // 無効化されたトレースは引数を評価しない。
  assert(effects == 0);
}
