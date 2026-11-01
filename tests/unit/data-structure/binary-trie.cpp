// Verify: data-structure/binary-trie.hpp
// 多重集合をvectorで保持し、挿入・一個削除・全要素XOR後のソート結果と比較する。
// 重複、0、最大値、最小値・最大値、1始まりのk番目と出現数を確認する。
#include <bits/stdc++.h>
using namespace std;
#include "data-structure/binary-trie.hpp"

int main() {
  mt19937 rng(462);
  BinaryTrie<unsigned, 7, 100000> trie;
  vector<unsigned> a;
  for (int step = 0; step < 3000; ++step) {
    int op = rng() % 3;
    if (a.empty() || op == 0) {
      unsigned x = rng() % 256;
      trie.add(x);
      a.push_back(x);
    } else if (op == 1) {
      int i = rng() % a.size();
      trie.del(a[i]);
      a.erase(a.begin() + i);
    } else {
      unsigned x = rng() % 256;
      trie.operate_xor(x);
      for (auto& v : a) {
        v ^= x;
      }
    }

    for (unsigned x = 0; x < 256; ++x) {
      // 挿入・削除・全要素XOR後の多重度を、配列に実際に残った値の個数と照合する。
      assert(trie.find(x).first == count(a.begin(), a.end(), x));
    }

    if (!a.empty()) {
      sort(a.begin(), a.end());

      // 最小値が、更新済みの配列をソートした先頭と一致する。
      assert(trie.min_element().first == a.front());

      // 最大値が、更新済みの配列をソートした末尾と一致する。
      assert(trie.max_element().first == a.back());
      for (int i = 0; i < (int)a.size(); ++i) {
        // k番目は1始まりで、同じ値が複数ある場合も別要素として数える。
        assert(trie.get_kth(i + 1).first == a[i]);
      }
    }
  }

  delete[] trie.pool;
}
