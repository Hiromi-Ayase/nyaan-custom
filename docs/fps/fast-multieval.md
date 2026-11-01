## NTT を利用した高速多点評価

`FastMultiEval(f, xs)` は低次順の係数列 `f` を全ての `xs[i]` で評価し、入力と同じ順の配列を返す。評価だけなので点の重複は許される。

点の配列は空でもよく、その場合は空配列を返す。1点なら直接評価する。係数列が空なら全ての評価値は0になる。

`ntt-friendly-fps.hpp` を読み込み、積の木を変換済みの形で処理する。異なる FPS バックエンドとは併用しない。必要な NTT 長を法の範囲内に収める。

点数と多項式長が同程度の $N$ の場合、時間 $O(N\log^2 N)$、領域 $O(N\log N)$。

#### 実装・検証

- [実装](../../fps/fast-multieval.hpp)
- [Verify: evaluation.cpp](../../tests/unit/fps/evaluation.cpp)
