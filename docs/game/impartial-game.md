## 不偏ゲームの Grundy 数

`ImpartialGameSolver<Board,Move=void,splittable=false>(f)` は遷移が DAG となる有限不偏ゲームをメモ化する。`get(board)` は Grundy 数、`get(vector<Board>)` は独立なゲームの XOR。

通常の f は局面から次の局面列を返す。`splittable=true` なら一手の遷移先を独立な盤面の列で表す。Move を指定すると各遷移は `(次のゲーム,着手)` の pair となり、勝ち局面で `get_best_move` を使える。

Board は map のキーとして比較可能であること。循環を検出する機能はない。計算量は到達局面数・遷移数と map/各局面の mex 用ソートに依存し、局面数が指数的なら高速化は保証しない。

#### 実装・検証

- [実装](../../game/impartial-game.hpp)
- [Verify: impartial.cpp](../../tests/unit/game/impartial.cpp)
