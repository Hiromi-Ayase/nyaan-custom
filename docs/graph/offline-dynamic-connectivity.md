## オフライン動的連結性

辺の追加・削除がすべて事前に分かる無向グラフについて、各時刻の連結性を Rollback Union Find で管理する。

1. `OffLineDynamicConnectivity dc(n, q)` を構築する。
2. `add_edge(t, u, v)` / `del_edge(t, u, v)` で時刻 `0 <= t < q` の操作を登録する。
3. `build()` を一度呼び、有効期間をセグメント木へ配置する。
4. `run(add, del, query)` を呼ぶ。`query(t)` 内で `dc.uf.same(u,v)` などを使用する。

同一辺の追加回数を数え、残数が正の期間だけ辺を有効にする。削除には対応する追加が必要。同一時刻では追加の後に削除を処理する。端点の順序は自動でそろわないため、登録時に常に `u <= v` とする。

`add(u,v)` は異なる成分を実際に併合したときだけ呼ばれる。`del(u,v)` はその探索区間を抜ける際、Union Find を戻す前に呼ばれる。全入力辺の追加削除通知ではなく、`del` の順序も `add` の厳密な逆順ではない。連結性だけなら両者に空のラムダを渡せる。

有効期間数を $K$ とすると、構築領域は $O(n+q+K\log q)$、探索はコールバックを除き $O(q+K\log q\log n)$。

#### 実装・検証

- [実装](../../graph/offline-dynamic-connectivity.hpp)
- [検証: yosupo-offline-dynamic-connectivity.test.cpp](../../verify/verify-yosupo-ds/yosupo-offline-dynamic-connectivity.test.cpp)
