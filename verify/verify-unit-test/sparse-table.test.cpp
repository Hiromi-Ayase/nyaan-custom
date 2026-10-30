#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
//
#include "../../template/template.hpp"
//
#include "../../data-structure/sparse-table.hpp"
#include "../../segment-tree/segment-tree-utility.hpp"
//
#include "../../misc/rng.hpp"
//
using namespace Nyaan;

template <typename T>
void test(int N) {
  vector<T> v(N);
  T INF = numeric_limits<T>::max() / 2;
  each(x, v) x = rng(-INF, INF);

  SparseTable<T> s{v};
  typename SegmentTree_RangeMin<T, numeric_limits<T>::max() / 2>::Tree seg(v);
  rep(i, N) reg(j, i, N + 1) {
    ll a1 = s.query(i, j);
    ll a2 = seg.prod(i, j);
    assert(a1 == a2);
  }
}

using namespace Nyaan;

void Nyaan::solve() {
  rep(t, 100) {
    rep(N, 100) {
      test<int>(N);
      test<ll>(N);
    }
  }
  cerr << "OK" << endl;

  int a, b;
  cin >> a >> b;
  cout << a + b << endl;
}