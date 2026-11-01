// Verify: data-structure/w-ary-tree.hpp
// Verify: data-structure/van-emde-boas-tree.hpp
// 整数集合をstd::setで管理し、挿入削除・包含・最小最大・以上/未満の探索を比較する。
// 空集合、0、63/64/65、4095/4096等の階層境界、重複挿入と既存要素の削除を検証する。
#include <bits/stdc++.h>
using namespace std;
#include "data-structure/w-ary-tree.hpp"
#include "data-structure/van-emde-boas-tree.hpp"

int main() {
  w_ary_tree<2> boundary;
  // 空集合でも最大の子番号63を調べられ、64ビットシフトを実行しない。
  assert(boundary.find_next(4095) == -1);
  boundary.insert(4094);
  assert(boundary.find_next(4095) == -1);
  boundary.insert(4095);
  // 最後のバケット内の値も、包含・直前・直後を正しく区別できる。
  assert(boundary.find_next(4095) == 4095 && boundary.find_prev(4095) == 4094);
  boundary.erase(4095);
  assert(boundary.find_next(4095) == -1);
  mt19937 rng(9173);
  auto w = make_unique<w_ary_tree<3>>();
  auto v = make_unique<van_Emde_Boas_tree>();
  set<int> ref;
  vector<int> special{0, 1, 63, 64, 65, 4095, 4096, 4097, 262143};
  for (int step = 0; step < 10000; ++step) {
    int x = step % 4 == 0 ? special[rng() % special.size()] : rng() % 262144;
    if (rng() % 2 || !ref.count(x)) {
      w->insert(x);
      v->insert(x);
      ref.insert(x);
    } else {
      w->erase(x);
      v->erase(x);
      ref.erase(x);
    }

    // 最小値をstd::setと比べ、空集合なら番兵-1になることも確認する。
    assert(w->min() == (ref.empty() ? -1 : *ref.begin()));

    // vEB木でも、同じ操作を受けたw-ary木と両端の値が一致する。
    assert(v->min() == w->min() && v->max() == w->max());

    // 最大値をstd::setと比べ、空集合なら番兵-1になることも確認する。
    assert(w->max() == (ref.empty() ? -1 : *ref.rbegin()));
    for (int q = 0; q < 8; ++q) {
      int key = q == 0 ? x : rng() % 262144;

      // 各キーの有無がstd::setと一致する。ワード境界付近も問い合わせる。
      assert(w->contain(key) == bool(ref.count(key)) && v->contain(key) == bool(ref.count(key)));
      auto it = ref.lower_bound(key);
      int next = it == ref.end() ? -1 : *it;
      int prev = it == ref.begin() ? -1 : *std::prev(it);

      // 指定キー以上で最小の要素を、std::set::lower_boundの結果と比較する。
      assert(w->find_next(key) == next && v->find_next(key) == next);

      // 指定キー未満で最大の要素を、std::setの探索結果と比較する。
      assert(w->find_prev(key) == prev && v->find_prev(key) == prev);
    }
  }

  for (int x : ref) {
    w->erase(x);
    v->erase(x);
  }

  // 全要素を消した後、両実装が空集合に戻る。
  assert(w->min() == -1 && w->max() == -1 && v->empty());
}
