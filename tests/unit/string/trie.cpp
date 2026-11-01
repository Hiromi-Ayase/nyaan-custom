// Verify: string/trie.hpp
// 挿入済み文字列のID列をmap、存在する接頭辞をsetで管理して比較する。
// 空文字、重複登録、未登録の接頭辞、存在しない遷移を確認する。
#include <bits/stdc++.h>
using namespace std;
#include "string/trie.hpp"

int main() {
  mt19937 rng(819);
  Trie<3> trie;
  map<string, vector<int>> ids;
  set<string> prefixes{string()};
  for (int step = 0; step < 500; ++step) {
    string s(rng() % 9, 'a');
    for (char& c : s) {
      c += rng() % 3;
    }

    trie.add(s, step);
    ids[s].push_back(step);
    for (int i = 0; i <= (int)s.size(); ++i) {
      prefixes.insert(s.substr(0, i));
    }

    // 登録語の全接頭辞をsetで数えた個数とノード数を比較し、重複登録で増えないことを確認する。
    assert(trie.size() == (int)prefixes.size());
    for (int q = 0; q < 20; ++q) {
      string t = q == 0 ? s : string(rng() % 9, 'a');
      if (q) {
        for (char& c : t) {
          c += rng() % 3;
        }
      }

      int node = trie.find(t);
      int walked = 0;
      for (char c : t) {
        walked = trie.move(walked, c);
      }

      // 一括検索したノードと、1文字ずつ遷移して到達したノードが一致する。
      assert(node == walked);

      // 登録語そのものだけでなく、その接頭辞も検索できる。
      assert((node != -1) == bool(prefixes.count(t)));
      auto it = ids.find(t);
      vector<int> expected = it == ids.end() ? vector<int>{} : it->second;

      // 同じ語に登録したIDの列が、登録順を含めて保存される。
      assert(trie.idxs(node) == expected);

      // 代表IDは最後に登録したIDになり、単なる接頭辞にはIDが付かない。
      assert(trie.idx(node) == (expected.empty() ? -1 : expected.back()));
    }
  }
}
