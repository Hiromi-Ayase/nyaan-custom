## 数として評価できる非不偏ゲーム

`PartisanGameSolver<Game,F>(f)` の f は、局面から `(左プレイヤーの遷移先列, 右プレイヤーの遷移先列)` を返す。`get(game)` は SurrealNumber による値をメモ化して返す。

一般の非不偏ゲームすべてを扱うものではない。各局面で左の値の最大が右の値の最小より小さく、数として定義できる有限・非循環ゲームが前提。満たさなければ assert に失敗する。

Game は map のキーとして比較可能であること。時間・領域は到達状態数、遷移数、数の reduce に必要な探索長に依存する。

#### 実装・検証

- [実装](../../game/partisan-game.hpp)
- [検証: aoj-1377.test.cpp](../../verify/verify-aoj-other/aoj-1377.test.cpp)
