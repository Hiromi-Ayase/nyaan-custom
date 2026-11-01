// Verify: data-structure/erasable-priority-queue.hpp
// Verify: data-structure/radix-heap.hpp
// Verify: data-structure/skew-heap.hpp
// 削除可能ヒープとmeld可能ヒープはmultiset、RadixHeapはmultimapを参照にする。
// 重複値・負値・遅延加算・空ヒープとのmeld・単調キーの大きなビット境界を確認する。
#include <bits/stdc++.h>
using namespace std;
#include <immintrin.h>
#include "data-structure/erasable-priority-queue.hpp"
#include "data-structure/radix-heap.hpp"
#include "data-structure/skew-heap.hpp"

int main() {
  mt19937_64 rng(654);
  ErasablePriorityQueue<long long> lo;
  ErasablePriorityQueue<long long, false> hi;
  multiset<long long> values;
  for (int step = 0; step < 4000; ++step) {
    if (values.empty() || rng() % 2) {
      long long x = (long long)(rng() % 101) - 50;
      lo.push(x);
      hi.push(x);
      values.insert(x);
    } else {
      auto it = values.begin();
      advance(it, rng() % values.size());
      lo.erase(*it);
      hi.erase(*it);
      values.erase(it);
    }

    if (!values.empty()) {
      // 遅延削除後も、最小・最大の各ヒープがmultisetの両端を返す。
      assert(lo.top() == *values.begin() && hi.top() == *values.rbegin());
    }
  }

  while (!values.empty()) {
    // 残りを順に取り出した際も、multisetと同じ昇順になる。
    assert(lo.top() == *values.begin());
    lo.pop();
    values.erase(values.begin());
  }

  RadixHeap<unsigned long long, int> radix;
  multimap<unsigned long long, int> ref;
  unsigned long long last = 0;
  for (int step = 0; step < 5000; ++step) {
    if (ref.empty() || rng() % 3) {
      unsigned long long key = last + (step % 17 == 0 ? (1ULL << 40) : rng() % 100);
      radix.push(key, step);
      ref.emplace(key, step);
    } else {
      auto [key, value] = radix.pop();

      // RadixHeapが取り出すキーは、登録中のキーの最小値になる。
      assert(key == ref.begin()->first);
      last = key;
      auto [l, r] = ref.equal_range(key);
      auto it = find_if(l, r, [&](auto p) { return p.second == value; });

      // 同じキーの要素が複数ある場合も、返された値が登録中のものに対応する。
      assert(it != r);
      ref.erase(it);
    }

    // 挿入・取り出し後のサイズと空判定が、参照用multimapと一致する。
    assert(radix.size() == (int)ref.size() && radix.empty() == ref.empty());
  }

  using Heap = SkewHeap<long long>;
  Heap::Ptr roots[3]{};
  multiset<long long> sets[3];
  vector<Heap::Ptr> allocated;
  for (int step = 0; step < 3000; ++step) {
    int i = rng() % 3;
    int op = rng() % 4;
    if (sets[i].empty() || op == 0) {
      long long x = (long long)(rng() % 101) - 50;
      auto node = Heap::alloc(x);
      allocated.push_back(node);
      roots[i] = Heap::meld(roots[i], node);
      sets[i].insert(x);
    } else if (op == 1) {
      Heap::propagate(roots[i]);

      // SkewHeapの取り出し対象は、そのヒープの最小値になっている。
      assert(roots[i]->key == *sets[i].begin());
      roots[i] = Heap::pop(roots[i]);
      sets[i].erase(sets[i].begin());
    } else if (op == 2) {
      long long x = (long long)(rng() % 21) - 10;
      Heap::apply(roots[i], x);
      multiset<long long> shifted;
      for (auto v : sets[i]) {
        shifted.insert(v + x);
      }

      sets[i] = shifted;
    } else {
      int j = (i + 1) % 3;
      roots[i] = Heap::meld(roots[i], roots[j]);
      roots[j] = nullptr;
      sets[i].insert(sets[j].begin(), sets[j].end());
      sets[j].clear();
    }

    for (int j = 0; j < 3; ++j) {
      // meldや削除後のnull判定が、参照集合の空判定と一致する。
      assert((roots[j] == nullptr) == sets[j].empty());
      if (roots[j]) {
        Heap::propagate(roots[j]);

        // 遅延加算を伝播した根の値が、全要素を直接更新した集合の最小値と一致する。
        assert(roots[j]->key == *sets[j].begin());
      }
    }
  }

  for (auto node : allocated) {
    delete node;
  }
}
