// Verify: data-structure/dynamic-binary-indexed-tree.hpp
// Verify: data-structure/hash-map-variable-length.hpp
// 動的Fenwickは更新した座標だけをmapで保持し、範囲内の値を全走査して比較する。
// 疎な大座標と負の更新を含め、可変長HashMap自体の再確保・検索・列挙もmapと比較する。
#include <bits/stdc++.h>
using namespace std;
#include "data-structure/dynamic-binary-indexed-tree.hpp"
#include "data-structure/hash-map-variable-length.hpp"

int main() {
  mt19937 rng(772);
  const long long n = 1000000007LL;
  DynamicFenwickTree<long long, long long> bit(n);
  map<long long, long long> a;
  for (int step = 0; step < 2000; ++step) {
    long long i = rng() % n;
    long long x = int(rng() % 201) - 100;
    if (step % 5 == 0) {
      i = 0;
    }

    if (step % 5 == 1) {
      i = n - 1;
    }

    bit.add(i, x);
    a[i] += x;

    // 点加算後の値が、疎な添字を保持したmapの値と一致する。
    assert(bit[i] == a[i]);
    long long l = rng() % (n + 1);
    long long r = rng() % (n + 1);
    if (l > r) {
      swap(l, r);
    }

    long long expected = 0;
    for (auto [k, v] : a) {
      if (l <= k && k < r) {
        expected += v;
      }
    }

    // 指定区間に入るmapの全要素を走査して足した和と比較する。
    assert(bit.sum(l, r) == expected);
  }

  HashMap<long long, long long> hm;
  map<long long, long long> ref;
  hm.set_default(-9);
  for (int i = 0; i < 3000; ++i) {
    long long k = (long long)(rng() % 1000) * 1000000007LL;
    if (!ref.count(k)) {
      ref[k] = -9;

      // 未登録キーへのアクセスでは、設定した初期値-9が返る。
      assert(hm[k] == -9);
    }

    hm[k] += i;
    ref[k] += i;

    // 同じキーの上書きで要素数が増えず、mapと同じ個数になる。
    assert(hm.size() == (int)ref.size());

    // 登録済みキーの検索で、最新の値を参照できる。
    assert(hm.find(k) && *hm.find(k) == ref[k]);

    // 一度も登録していないキーの検索はnullを返す。
    assert(hm.find(-1) == nullptr);
  }

  auto entries = hm.enumerate();
  sort(entries.begin(), entries.end());
  vector<pair<long long, long long>> expected(ref.begin(), ref.end());

  // 全要素の列挙結果をソートしてmapと比較し、欠落や重複がないことを確認する。
  assert(entries == expected);
}
