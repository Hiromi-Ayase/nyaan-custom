## NTT を利用した高速多点評価

`FastMultiEval(f, xs)` は低次順の係数列 `f` を全ての `xs[i]` で評価し、入力と同じ順の配列を返す。評価だけなので点の重複は許される。

この実装は冒頭で `xs.size()-1` の先頭ゼロ数を使って容量を計算する。空配列・1 点の境界処理より先に実行されるため、**点数は 2 以上**にする。0 点や 1 点なら `MultipointEvaluation` または直接の `eval` を使う。

`ntt-friendly-fps.hpp` を読み込み、積の木を変換済みの形で処理する。異なる FPS バックエンドとは併用しない。必要な NTT 長を法の範囲内に収める。

点数と多項式長が同程度の $N$ の場合、時間 $O(N\log^2 N)$、領域 $O(N\log N)$。

#### 実装・検証

- [実装](../../fps/fast-multieval.hpp)
- [検証: multieval.test.cpp](../../verify/verify-unit-test/multieval.test.cpp)
- [検証: multipoint-binomial-sum.test.cpp](../../verify/verify-unit-test/multipoint-binomial-sum.test.cpp)
- [検証: yosupo-multieval-fast.test.cpp](../../verify/verify-yosupo-fps/yosupo-multieval-fast.test.cpp)
